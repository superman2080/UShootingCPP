// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "UE5Coro.h"
using namespace UE5Coro;
using namespace UE5Coro::Latent;


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));
	SpawnEnemyLoop();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TCoroutine<> AEnemySpawner::SpawnEnemyLoop()
{
	while (true)
	{
		co_await Seconds(enemyGenInterval);

		if (!IsValid(this)) break;
		if (!IsValid(player)) break;
		if (!enemyFactory) break;
		UWorld* world = GetWorld();
		if (!world) break;

		FVector spawnPos = FVector(0, FMath::FRandRange(-540.0f, 540.0f), 960);
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		world->SpawnActor<AEnemy>(enemyFactory, spawnPos, FRotator::ZeroRotator, spawnParams);
	}
}

