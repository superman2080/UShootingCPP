// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = BoxComp;
	
	BodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMeshComp"));
	BodyMeshComp->SetupAttachment(BoxComp);
	
	// BodyMesh에 CubeStaticMesh 데이터 로드해서 할당.
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Game/Models/Drone_low.Drone_low"));
	
	if (tempMesh.Succeeded() /*tempMesh != nullptr*/)
	{
		BodyMeshComp->SetStaticMesh(tempMesh.Object);
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHit);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto dir = FVector::DownVector * speed;
	if (IsValid( player))
	{
		dir = (player->GetActorLocation() - GetActorLocation())	;
		dir.Normalize();
		dir *= speed;
	}
	SetActorLocation(GetActorLocation() + dir * DeltaTime);
}

void AEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<ACPlayer>(OtherActor)) return;

	if (destroySound)
		UGameplayStatics::PlaySound2D(GetWorld(), destroySound);
	OtherActor->Destroy();
	Destroy();
}

