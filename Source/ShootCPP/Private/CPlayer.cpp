// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootCPP/Public/CPlayer.h"
#include "Components/BoxComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"


// 에디터 실행 시에 호출
// UClass | CDO 초기화 시에 사용(에디터 끄고 빌드 권장)
// Sets default values
ACPlayer::ACPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// Tick 쓸건지 말건지(성능 개선 위한 prop
	PrimaryActorTick.bCanEverTick = true;
	// GetComponent<>()
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	
	BodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMeshComp"));
	BodyMeshComp->SetupAttachment(BoxComp);
	
	// BodyMesh에 CubeStaticMesh 데이터 로드해서 할당.
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	
	if (tempMesh.Succeeded() /*tempMesh != nullptr*/)
	{
		BodyMeshComp->SetStaticMesh(tempMesh.Object);
	}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//P = P0 + vt
	// P: 위치 벡터
	// v: 방향 벡터
	// t: 시간(dT)
	
	FVector P0 = GetActorLocation();
	FVector vt = dir * DeltaTime * speed;
	
	FVector P = P0 + vt;
	SetActorLocation(P, true);
	dir = FVector::Zero();
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// 사용자 입력 매핑 에셋 등록
	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subSystem)
		{
			subSystem->AddMappingContext(imc_shoot, 0);
		}
	}
	// 처리 함수 및 입력액션을 바인딩
	
	auto playerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (playerInput)
	{
		// Triggered: 계속 누르고 있을 때
		playerInput->BindAction(ia_move, ETriggerEvent::Triggered, this, &ACPlayer::MovePlayer);
	}
}

void ACPlayer::MovePlayer(const struct FInputActionValue& value) /*const: 외부에서 로컬변수 값을 바꿀 수 없음*/
{
	auto v = value.Get<FVector2D>();
	v.Normalize();
	dir.Y = v.X;
	dir.Z = v.Y;
	
}

