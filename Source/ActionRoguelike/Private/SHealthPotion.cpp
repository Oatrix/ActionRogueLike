// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"
#include "SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetCapsuleHalfHeight(50.0f);
	CapsuleComp->SetCapsuleRadius(25.0f);
	RootComponent = CapsuleComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleComp);
	
	HeallingAmount = 50.0f;

	SpawnDelay = 10.0f;
}

void ASHealthPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Reset();
}

void ASHealthPotion::Reset()
{
	bIsInteractable = false;
	Mesh->SetScalarParameterValueOnMaterials("FadingRatio", 0.0f);
	GetWorldTimerManager().SetTimer(TimerHandle_DelaySpawn, this, &ASHealthPotion::Spawn, SpawnDelay);
}

// Called when the game starts or when spawned
void ASHealthPotion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!(ensure(!IsPendingKill())) || !bIsInteractable)
	{
		return;
	}	
		
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp && AttributeComp->GetHealthRatio() < 1)
	{		
		AttributeComp->ApplyHealthChange(HeallingAmount);
		Reset();
	}	
}

void ASHealthPotion::Spawn()
{
	// Clear timer if Spawn was already called through another source.
	GetWorldTimerManager().ClearTimer(TimerHandle_DelaySpawn);

	Mesh->SetScalarParameterValueOnMaterials("FadingRatio", 1.0f);

	bIsInteractable = true;
}
