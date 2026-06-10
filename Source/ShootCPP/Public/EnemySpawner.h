#pragma once

#include "CoreMinimal.h"
#include "Boss.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "CPlayer.h"
#include "UE5Coro.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SHOOTCPP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 적 스폰 간격 (초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	float enemyGenInterval = 2.f;

	// 적 스폰 지속 시간 (초) — 이후 보스 페이즈로 전환
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	float enemySpawnDuration = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	TSubclassOf<AEnemy> enemyFactory;

	// 보스 스폰 위치 (레벨 위 바깥)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss")
	FVector bossSpawnPos = FVector(0.f, 0.f, 1800.f);

	// 보스가 이동할 목표 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss")
	FVector bossTargetPos = FVector(0.f, 0.f, 700.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss")
	TSubclassOf<ABoss> bossFactory;

private:
	UPROPERTY()
	ACPlayer* player;

	UE5Coro::TCoroutine<> SpawnLoop();
};
