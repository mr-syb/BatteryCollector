// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "BatteryPickUp.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickUp : public APickUp
{
	GENERATED_BODY()
	
public:
	ABatteryPickUp();

	void WasCollected_Implementation() override;

	FORCEINLINE float GetPower() {return BatteryPower;}
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,category = "Power",meta = (BlueprintProtected = "true"))
	float BatteryPower;
};
