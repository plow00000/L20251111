// Fill out your copyright notice in the Description page of Project Settings.


#include "MyThirdPersonCharacter.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyThirdPersonCharacter::AMyThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 9.f));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	static ConstructorHelpers::FObjectFinder<UInputAction> IAJ(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Jump.IA_Jump'"));
	if (IAJ.Succeeded())
	{
		IA_Jump = IAJ.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAM(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'"));
	if (IAM.Succeeded())
	{
		IA_Move = IAM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAML(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_MouseLook.IA_MouseLook'"));
	if (IAML.Succeeded())
	{
		IA_MouseLook = IAML.Object;
	}
}

// Called when the game starts or when spawned
void AMyThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyThirdPersonCharacter::CharacterMove);
		EIC->BindAction(IA_MouseLook, ETriggerEvent::Triggered, this, &AMyThirdPersonCharacter::Aim);
	}
}

void AMyThirdPersonCharacter::CharacterMove(FInputActionValue const& Value)
{
	FVector2D MoveValue = Value.Get<FVector2D>();
	FRotator F = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, F.Yaw, F.Roll)), MoveValue.X);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, F.Yaw, 0)), MoveValue.Y);
}

void AMyThirdPersonCharacter::Aim(FInputActionValue const& Value)
{
	FVector2D AimValue = Value.Get<FVector2D>();
	AddControllerYawInput(AimValue.X);
	AddControllerPitchInput(AimValue.Y);
}