#include "BossState_Pattern2.h"
#include "Boss.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"

void BossState_Pattern2::Enter()
{
	BossStateBase::Enter();
	FireTimer = 0.f;
}

void BossState_Pattern2::Execute(float DeltaTime)
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

	// 플레이어 방향 계산
	FVector AimDir = FVector(0.f, 0.f, -1.f); // 기본: 아래
	ACPlayer* Player = Cast<ACPlayer>(
		UGameplayStatics::GetActorOfClass(Owner->GetWorld(), ACPlayer::StaticClass()));
	if (Player)
	{
		FVector ToPlayer = Player->GetActorLocation() - Owner->GetActorLocation();
		ToPlayer.X = 0.f;
		if (!ToPlayer.IsNearlyZero())
			AimDir = ToPlayer.GetSafeNormal();
	}

	// 중심각 계산 (ZY 평면)
	float CenterDeg = FMath::RadiansToDegrees(FMath::Atan2(AimDir.Y, AimDir.Z));
	float HalfSpread = SpreadDeg * (BulletsPerBurst - 1) * 0.5f;

	for (int32 i = 0; i < BulletsPerBurst; i++)
	{
		float Deg = CenterDeg - HalfSpread + i * SpreadDeg;
		float Rad = FMath::DegreesToRadians(Deg);
		FVector Dir = FVector(0.f, FMath::Sin(Rad), FMath::Cos(Rad));
		Owner->SpawnBullet(Dir);
	}
}
