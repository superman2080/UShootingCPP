#pragma once

#include "State.h"

class ABoss;

class BossStateBase : public State
{
protected:
	ABoss* Owner;
	float ElapsedTime    = 0.f;
	float WarmupDuration = 2.f;  // 패턴 진입 후 발사 대기 시간 (서브클래스에서 재정의 가능)
	bool  bDone          = false;

public:
	BossStateBase(ABoss* InOwner) : Owner(InOwner) {}

	virtual void Enter() override
	{
		ElapsedTime = 0.f;
		bDone       = false;
	}

	bool IsDone()     const { return bDone; }
	bool IsWarmedUp() const { return ElapsedTime >= WarmupDuration; }
};
