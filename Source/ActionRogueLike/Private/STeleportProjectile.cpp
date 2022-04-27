// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	ExplosionEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionEffectComponent");
	ExplosionEffectComponent->SetupAttachment(SphereComponent);

}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	bIsExploded = false;
	bIsDestroyed = false;
	InitialTime = GetWorld()->GetTimeSeconds();
	ExplosionTime = InitialTime + ExplodeTimer;
	TeleportTime = ExplosionTime + TeleportingDelayAfterExplosion;
}

void ASTeleportProjectile::Explode()
{
	if(bIsExploded)
		return;

	bIsExploded = true;
	/*//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffectComponent, GetActorTransform(), true,EPSCPoolMethod::None, true);
	const FTransform &ActorTransform = GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffectComponent->, ActorTransform);
	UGameplayStatics::spawn*/
	
	/*UParticleSystem *ParticleSystem;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorTransform());*/
	
	MovementComponent->StopMovementImmediately();
}

void ASTeleportProjectile::Teleport()
{
	if (AActor* InstigatorActor = GetInstigator())
	{
		
		InstigatorActor->TeleportTo(GetActorLocation(), InstigatorActor->GetActorRotation(), false, true);
		bIsDestroyed = true;
		Destroy();
	}
}

void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsDestroyed)
		return;

	if(GetWorld()->GetTimeSeconds() >= ExplosionTime)
	{
		if(!bIsExploded)
		{
			Explode();
		}

		if (GetWorld()->GetTimeSeconds() >= TeleportTime)
		{
			Teleport();
		}
	}
}

void ASTeleportProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	int bob = 5;
}