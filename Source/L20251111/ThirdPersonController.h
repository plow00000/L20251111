// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonController.generated.h"

/**
 * 
 */
UCLASS()
class L20251111_API AThirdPersonController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AThirdPersonController();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Input")
	TArray<TObjectPtr<class UInputMappingContext>> InputMapping;
};
