// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P38_PC.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class L20251111_API AP38_PC : public APlayerController
{
	GENERATED_BODY()
	
public:
	AP38_PC();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	TObjectPtr<UInputMappingContext> DefaultIMC;

};
