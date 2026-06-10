#include "Boss.h"
#include "BossBullet.h"
#include "BossState_Move.h"
#include "BossState_Pattern1.h"
#include "BossState_Pattern2.h"
#include "BossState_Pattern3.h"
#include "Components/BoxComponent.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = BoxComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
		TEXT("/Game/Fab/DROPSHIP_R35/dropship_r35/StaticMeshes/dropship_r35.dropship_r35"));
	if (Mesh.Succeeded())
		MeshComp->SetStaticMesh(Mesh.Object);
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	// 상태 생성
	auto MoveState = MakeUnique<BossState_Move>(this);
	auto P1State   = MakeUnique<BossState_Pattern1>(this);
	auto P2State   = MakeUnique<BossState_Pattern2>(this);
	auto P3State   = MakeUnique<BossState_Pattern3>(this);

	// 전환 조건 체크용 raw 포인터 (소유권은 StateMachine이 가짐)
	BossState_Move*     MovePtr = MoveState.Get();
	BossState_Pattern1* P1Ptr   = P1State.Get();
	BossState_Pattern2* P2Ptr   = P2State.Get();
	BossState_Pattern3* P3Ptr   = P3State.Get();

	StateMachine.RegisterState(EBossState::Move,     MoveTemp(MoveState));
	StateMachine.RegisterState(EBossState::Pattern1, MoveTemp(P1State));
	StateMachine.RegisterState(EBossState::Pattern2, MoveTemp(P2State));
	StateMachine.RegisterState(EBossState::Pattern3, MoveTemp(P3State));

	// 전환 조건 등록
	StateMachine.RegisterCondition(EBossState::Move,     EBossState::Pattern1,
		[MovePtr]() { return MovePtr->bReachedTarget; });
	StateMachine.RegisterCondition(EBossState::Pattern1, EBossState::Pattern2,
		[P1Ptr]() { return P1Ptr->IsDone(); });
	StateMachine.RegisterCondition(EBossState::Pattern2, EBossState::Pattern3,
		[P2Ptr]() { return P2Ptr->IsDone(); });
	StateMachine.RegisterCondition(EBossState::Pattern3, EBossState::Pattern1,
		[P3Ptr]() { return P3Ptr->IsDone(); });

	StateMachine.ChangeState(EBossState::Move);
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StateMachine.Execute(DeltaTime);
}

void ABoss::SpawnBullet(FVector Direction)
{
	if (!BulletFactory) return;

	ABossBullet* Bullet = GetWorld()->SpawnActor<ABossBullet>(
		BulletFactory, GetActorLocation(), FRotator::ZeroRotator);
	if (Bullet)
		Bullet->Direction = Direction.GetSafeNormal();
}

void ABoss::TakeDamage(float damage)
{
	hp -= damage;
	if (hp <= 0.f)
		Destroy();
}
