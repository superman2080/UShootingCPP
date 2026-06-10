#pragma once

#include "BossStateBase.h"

// 조준 부채꼴 탄막: 플레이어를 향해 5-way 부채꼴로 발사
class BossState_Pattern2 : public BossStateBase
{
	float FireTimer = 0.f;

	static constexpr float FireInterval    = 0.4f;
	static constexpr float PatternDuration = 5.f;
	static constexpr int32 BulletsPerBurst = 5;
	static constexpr float SpreadDeg       = 20.f; // 탄 사이 각도

public:
	BossState_Pattern2(ABoss* InOwner) : BossStateBase(InOwner) {}

	virtual void Enter() override;
	virtual void Execute(float DeltaTime) override;
};
