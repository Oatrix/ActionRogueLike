// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "STeleportProjectile.generated.h"

class UParticleSystemComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASProjectile
{
	GENERATED_BODY()

	float InitialTime;
	float ExplosionTime;
	float TeleportTime;
	bool bIsExploded;
	bool bIsDestroyed;
public:
	// Sets default values for this actor's properties
	ASTeleportProjectile();

	UPROPERTY(EditAnywhere)
	float ExplodeTimer = 0.2f;

	UPROPERTY(EditAnywhere)
	float TeleportingDelayAfterExplosion = 0.2f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParticleSystemComponent* ExplosionEffectComponent;

protected:

	virtual void BeginPlay() override;

	void Explode();
	void Teleport();

	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	virtual void Tick(float DeltaTime) override;
};
