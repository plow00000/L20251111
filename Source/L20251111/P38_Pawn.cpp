// Fill out your copyright notice in the Description page of Project Settings.


#include "P38_Pawn.h"
#include "RocketBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"


// Sets default values
AP38_Pawn::AP38_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(48.0f, 64.0f, 8.f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.5f, -21.f, 0));

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.5f, 21.f, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SocketOffset = FVector(65.0f, 0, 60.0f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(-20.f, 0, 0));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector(70.f, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 100.0f;


	static ConstructorHelpers::FClassFinder<ARocketBase> BP_RocketTemplate(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Rocket.BP_Rocket_C'"));
	if (BP_RocketTemplate.Succeeded())
	{
		RocketTemplate = BP_RocketTemplate.Class;
	}

}

// Called when the game starts or when spawned
void AP38_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP38_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	AddMovementInput(GetActorForwardVector());

	Left->AddLocalRotation(FRotator(0, 0, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 7200.0f));
	Right->AddLocalRotation(FRotator(0, 0, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 7200.0f));

}

// Called to bind functionality to input
void AP38_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AP38_Pawn::Fire()
{
	if (RocketTemplate)
	{
		GetWorld()->SpawnActor<AActor>(RocketTemplate, Arrow->GetComponentTransform());
	}
}

/*
* 이건 비행기 회전
*/
void AP38_Pawn::Rotate(float InPitch, float InRoll)
{
	UE_LOG(LogTemp, Warning, TEXT("%f %f"), InPitch, InRoll);
	AddActorLocalRotation(FRotator(InPitch, 0, InRoll) * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f);
}

