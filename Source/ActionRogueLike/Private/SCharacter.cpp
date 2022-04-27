// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"

#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimingDistance = 1000.0f;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>( "SpringArmComponent" );
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>( "CameraComponent" );
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ASCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ASCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &ASCharacter::SecondaryAttack_TimerElapsed, 0.2f);
}


void ASCharacter::SecondaryAttack_TimerElapsed()
{
	FHitResult Hit;
	FCollisionQueryParams QuerryParams;

	FVector From = CameraComponent->GetComponentLocation();
	FVector DesireTarget = From + (CameraComponent->GetForwardVector() * AimingDistance);

	bool bBlockingHit = GetWorld()->LineTraceSingleByProfile(Hit, From, DesireTarget, TEXT("Projectile"), QuerryParams);


	if (bBlockingHit)
	{
		DesireTarget = Hit.ImpactPoint;
	}

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(HandLocation, DesireTarget);
	FTransform SpawnTM = FTransform(LookAt, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(SecondaryProjectileClass, SpawnTM, SpawnParams);
}


void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimerElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimerElapsed()
{
	FHitResult Hit;
	FCollisionQueryParams QuerryParams;	
	
	FVector From = CameraComponent->GetComponentLocation();
	FVector DesireTarget = From + (CameraComponent->GetForwardVector() * AimingDistance);

	bool bBlockingHit = GetWorld()->LineTraceSingleByProfile(Hit, From, DesireTarget, TEXT("Projectile"), QuerryParams);
	 
	
	if( bBlockingHit )
	{
		DesireTarget = Hit.ImpactPoint;
	}

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(HandLocation, DesireTarget);
	FTransform SpawnTM = FTransform(LookAt, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(PrimaryProjectileClass, SpawnTM, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	if(InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
}
