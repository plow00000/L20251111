// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "P38_Pawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class USpringArmComponent;
class UArrowComponent;
struct FInputActionValue;

UCLASS()
class L20251111_API AP38_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP38_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Control, meta = (ShortTooltip = "이건 미사일 발사"))
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Control)
	void Rotate(float InPitch, float InRoll);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TSubclassOf<class ARocketBase> RocketTemplate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UBoxComponent* Box;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Body;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Left;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Right;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UFloatingPawnMovement* Movement;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	UArrowComponent* Arrow;

};
