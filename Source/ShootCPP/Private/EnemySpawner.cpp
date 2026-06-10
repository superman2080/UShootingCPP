#include "EnemySpawner.h"
#include "UE5Coro.h"
using namespace UE5Coro;
using namespace UE5Coro::Latent;

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));
	SpawnLoop();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TCoroutine<> AEnemySpawner::SpawnLoop()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	while (true)
	{
		// ── 적 스폰 페이즈 ──────────────────────────────
		float Elapsed = 0.f;
		while (Elapsed < enemySpawnDuration)
		{
			co_await Seconds(enemyGenInterval);
			Elapsed += enemyGenInterval;

			if (!IsValid(this) || !IsValid(player) || !enemyFactory) co_return;

			FVector SpawnPos = FVector(0.f, FMath::FRandRange(-540.f, 540.f), 960.f);
			GetWorld()->SpawnActor<AEnemy>(enemyFactory, SpawnPos, FRotator::ZeroRotator, SpawnParams);
		}

		// ── 보스 스폰 페이즈 ────────────────────────────
		if (!IsValid(this) || !bossFactory) co_return;

		ABoss* Boss = GetWorld()->SpawnActor<ABoss>(
			bossFactory, bossSpawnPos, FRotator::ZeroRotator, SpawnParams);

		if (IsValid(Boss))
			Boss->TargetPosition = bossTargetPos;

		// 보스가 살아있는 동안 대기 (0.5초 간격으로 체크)
		while (IsValid(Boss))
		{
			co_await Seconds(0.5f);
			if (!IsValid(this)) co_return;
		}

		// 보스 사망 후 잠시 대기 후 적 루틴 재시작
		co_await Seconds(3.f);
	}
}
