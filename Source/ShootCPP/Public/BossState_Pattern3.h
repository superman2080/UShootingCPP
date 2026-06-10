#pragma once

#include "BossStateBase.h"

// 연사 조준 탄막: 플레이어를 향해 빠른 속도로 단발 연사
class BossState_Pattern3 : public BossStateBase
{
	float FireTimer = 0.f;

	static constexpr float FireInterval    = 0.12f;
	static constexpr float PatternDuration = 5.f;

public:
	BossState_Pattern3(ABoss* InOwner) : BossStateBase(InOwner) { WarmupDuration = 2.5f; }

	virtual void Enter() override;
	virtual void Execute(float DeltaTime) override;
};
