// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARocketBase::ARocketBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(30.f, 10.f, 10.f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetRelativeRotation(FRotator(-90.f, 0, 0));
	Body->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1000.f;
	Movement->MaxSpeed = 1000.f;
	Movement->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void ARocketBase::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);

	OnActorBeginOverlap.AddDynamic(this, &ARocketBase::ProcessActorBeginOver);
	
}

// Called every frame
void ARocketBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocketBase::ProcessActorBeginOver(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("Target")))
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			100,
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			this,
			UDamageType::StaticClass()
		);

		Destroy();
	}
}

