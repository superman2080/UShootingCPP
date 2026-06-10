#pragma once

#include "BossStateBase.h"

// 나선형 탄막: 링 형태로 발사하며 매 버스트마다 회전 오프셋 증가
class BossState_Pattern1 : public BossStateBase
{
	float FireTimer  = 0.f;
	float RingAngle  = 0.f;

	static constexpr float  FireInterval    = 0.25f;
	static constexpr float  PatternDuration = 6.f;
	static constexpr int32  BulletsPerRing  = 8;
	static constexpr float  RotatePerBurst  = 22.5f; // degrees

public:
	BossState_Pattern1(ABoss* InOwner) : BossStateBase(InOwner) {}

	virtual void Enter() override;
	virtual void Execute(float DeltaTime) override;
};
