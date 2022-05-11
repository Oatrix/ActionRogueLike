// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"




bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(TargetActor);
	if (AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;
}


bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult, float ImpulseMultiplier /*= 1.0f*/)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics())//(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation((HitResult.TraceEnd - HitResult.TraceStart).GetUnsafeNormal() * ImpulseMultiplier, HitResult.ImpactPoint, HitResult.BoneName);
		}
// 		else if(HitComp && !HitComp->IsSimulatingPhysics(HitResult.BoneName) && ImpulseMultiplier != 250.0f)
// 		{
// 			if(USphereComponent *ShpereComp = Cast<USphereComponent>(HitComp))
// 			{
// 
// 			}
// 			int bob = 5;
// 		}
		return true;
	}

	return false;
}
