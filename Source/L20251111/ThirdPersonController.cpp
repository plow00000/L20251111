// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

AThirdPersonController::AThirdPersonController()
{

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_D(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (IMC_D.Succeeded())
	{
		InputMapping.Add(IMC_D.Object);
	}
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_M(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_MouseLook.IMC_MouseLook'"));
	if (IMC_M.Succeeded())
	{
		InputMapping.Add(IMC_M.Object);
	}

}

void AThirdPersonController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (IsLocalPlayerController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				for (TObjectPtr<UInputMappingContext> Data : InputMapping)
				{
					InputSystem->AddMappingContext(Data, 0);
				}
			}
		}
	}
}

void AThirdPersonController::OnUnPossess()
{
	if (IsLocalPlayerController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				for (TObjectPtr<UInputMappingContext> Data : InputMapping)
				{
					InputSystem->RemoveMappingContext(Data);
				}
			}
		}
	}

	Super::OnUnPossess();
}