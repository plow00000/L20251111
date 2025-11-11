// Fill out your copyright notice in the Description page of Project Settings.


#include "P38_PC.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AP38_PC::AP38_PC()
{
}

void AP38_PC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);


	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(DefaultIMC, 0);
			}
		}
	}
}

void AP38_PC::OnUnPossess()
{
	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(DefaultIMC);
			}
		}
	}

	Super::OnUnPossess();
}
