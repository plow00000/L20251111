// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATargetBase::ATargetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(32.f, 32.f, 32.f));

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Box);
	Sphere->SetRelativeScale3D(FVector(0.25f, 1.f, 1.f));


	Tags.Add(TEXT("Target"));
}

// Called when the game starts or when spawned
void ATargetBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATargetBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), P_Explosion,
		GetActorLocation());

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Cue_Explosion, GetActorLocation());

	//기획자 하고 싶은거, Blueprint 함수 방법
	// DoDesigner();
	DoDesigner2();

	Destroy();

	return Damage;
}

void ATargetBase::DoDesigner2_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("이건 C++ 기본 구현"));
}

int32 ATargetBase::GetGold()
{
	return 100;
}




