#include "BossState_Pattern1.h"
#include "Boss.h"

void BossState_Pattern1::Enter()
{
	BossStateBase::Enter();
	FireTimer = 0.f;
	RingAngle = 0.f;
}

void BossState_Pattern1::Execute(float DeltaTime)
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

	const float AngleStep = 360.f / BulletsPerRing;
	for (int32 i = 0; i < BulletsPerRing; i++)
	{
		float Deg = RingAngle + i * AngleStep;
		float Rad = FMath::DegreesToRadians(Deg);
		// ZY 평면 기준 방향 (X=0)
		FVector Dir = FVector(0.f, FMath::Sin(Rad), FMath::Cos(Rad));
		Owner->SpawnBullet(Dir);
	}

	RingAngle += RotatePerBurst;
}
