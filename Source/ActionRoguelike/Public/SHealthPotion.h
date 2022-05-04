// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SHealthPotion.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

	void Interact_Implementation(APawn* InstigatorPawn);

protected:

	UPROPERTY(BlueprintReadOnly)
	bool bIsInteractable;

	UPROPERTY(EditDefaultsOnly)
	float HeallingAmount;

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent *CapsuleComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	float SpawnDelay;

	// Handle to cancel timer if we already hit something
	FTimerHandle TimerHandle_DelaySpawn;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void Reset();

	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
