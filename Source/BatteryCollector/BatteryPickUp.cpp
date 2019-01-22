// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickUp.h"
#include "Components/StaticMeshComponent.h"

ABatteryPickUp::ABatteryPickUp()
{
	GetMesh()->SetSimulatePhysics(true);

	BatteryPower = 150.f;
}

void ABatteryPickUp::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();

	FString PickupDebugStr = GetName();
	UE_LOG(LogClass, Log, TEXT("will be destroy %s"), *PickupDebugStr);

	Destroy();
}

