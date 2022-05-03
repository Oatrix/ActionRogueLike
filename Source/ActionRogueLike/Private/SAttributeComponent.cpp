// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100;
	Health = MaxHealth;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	float NewHealth = Health + Delta;

	if(NewHealth < 0)
	{
		Delta -= NewHealth;
		NewHealth = 0;
	}
	else if(NewHealth > MaxHealth)
	{
		Delta -= NewHealth - MaxHealth;
		NewHealth = MaxHealth;
	}
		
	Health = NewHealth;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}
