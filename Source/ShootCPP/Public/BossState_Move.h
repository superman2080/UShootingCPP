#pragma once

#include "BossStateBase.h"

class BossState_Move : public BossStateBase
{
public:
	bool bReachedTarget = false;

	BossState_Move(ABoss* InOwner) : BossStateBase(InOwner) {}

	virtual void Enter() override;
	virtual void Execute(float DeltaTime) override;
};
