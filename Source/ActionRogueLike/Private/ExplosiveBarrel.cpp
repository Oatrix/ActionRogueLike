// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "PhysicsEngine\RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	StaticMesh->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnComponentHit);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetComponentTickEnabled(true);
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->Falloff = ERadialImpulseFalloff::RIF_Linear;
	RadialForceComponent->Radius = 500.0f;
	RadialForceComponent->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//RadialForceComponent->TickComponent(DeltaTime, ELevelTick::LEVELTICK_All, &AExplosiveBarrel::Tick );
}

void AExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	  RadialForceComponent->FireImpulse();
}



