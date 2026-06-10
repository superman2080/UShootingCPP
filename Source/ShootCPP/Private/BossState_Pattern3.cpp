#include "BossState_Pattern3.h"
#include "Boss.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"

void BossState_Pattern3::Enter()
{
	BossStateBase::Enter();
	FireTimer = 0.f;
}

void BossState_Pattern3::Execute(float DeltaTime)
{
	ElapsedTime += DeltaTime;
	if (ElapsedTime >= PatternDuration)
	{
		bDone = true;
		return;
	}

	if (!IsWarmedUp()) return;

	FireTimer += DeltaTime;
	if (FireTimer < FireInterval) return;
	FireTimer = 0.f;

	// 플레이어를 향해 단발 발사
	FVector AimDir = FVector(0.f, 0.f, -1.f);
	ACPlayer* Player = Cast<ACPlayer>(
		UGameplayStatics::GetActorOfClass(Owner->GetWorld(), ACPlayer::StaticClass()));
	if (Player)
	{
		FVector ToPlayer = Player->GetActorLocation() - Owner->GetActorLocation();
		ToPlayer.X = 0.f;
		if (!ToPlayer.IsNearlyZero())
			AimDir = ToPlayer.GetSafeNormal();
	}

	Owner->SpawnBullet(AimDir);
}
