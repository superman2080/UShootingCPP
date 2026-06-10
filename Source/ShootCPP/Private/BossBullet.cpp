#include "BossBullet.h"
#include "CPlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ABossBullet::ABossBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(12.f));
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = BoxComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(
		TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Mesh.Succeeded())
		MeshComp->SetStaticMesh(Mesh.Object);

	ConstructorHelpers::FObjectFinder<UMaterial> mat(TEXT("/Game/Materials/M_Bullet.M_Bullet"));
	if (mat.Succeeded())
		MeshComp->SetMaterial(0, mat.Object);

	SetActorScale3D(FVector(0.25f));
}

void ABossBullet::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABossBullet::OnHit);
}

void ABossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime);

	LifeTime += DeltaTime;
	if (LifeTime >= MaxLifeTime)
		Destroy();
}

void ABossBullet::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	if (!Player) return;

	Player->TakeDamage(10.f);
	Destroy();
}
