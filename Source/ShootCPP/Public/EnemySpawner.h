// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Prop")
	float enemyGenInterval = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Prop")
	TSubclassOf<AEnemy> enemyFactory;
	
private:
	UPROPERTY(EditAnywhere)
	ACPlayer* player;
	
	UE5Coro::TCoroutine<> SpawnEnemyLoop();
};
