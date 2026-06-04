// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootCPP/Public/ShootGameMode.h"
#include  "CPlayer.h"
#include "SNegativeActionButton.h"

AShootGameMode::AShootGameMode()
{
	// UE_LOG(LogTemp, Warning, TEXT("Hello, world!"));
	static  ConstructorHelpers::FClassFinder<APawn> playerBP(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Player.BP_Player'"));
	if (playerBP.Succeeded())
	{
		DefaultPawnClass = playerBP.Class;
		
	}
}
