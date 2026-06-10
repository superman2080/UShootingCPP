#include "BossState_Move.h"
#include "Boss.h"

void BossState_Move::Enter()
{
	BossStateBase::Enter();
	bReachedTarget = false;
}

void BossState_Move::Execute(float DeltaTime)
{
	if (bReachedTarget) return;

	FVector Current = Owner->GetActorLocation();
	FVector Target  = Owner->TargetPosition;
	FVector Dir     = Target - Current;
	float   Dist    = Dir.Size();

	if (Dist < 5.f)
	{
		Owner->SetActorLocation(Target);
		bReachedTarget = true;
		return;
	}

	Dir.Normalize();
	Owner->SetActorLocation(Current + Dir * Owner->MoveSpeed * DeltaTime);
}
