// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, category = "Spawning")
	FVector	GetRandomPointInVolume();

	UFUNCTION(BlueprintCallable, category = "Spawning")
	void SetSpawnVolumeActive(bool iShouldActive);

protected:
	UPROPERTY(EditAnywhere,category = "Spawning")
	TSubclassOf<class APickUp> WhatToSpawn;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, category = "Spawning")
	float SpawnDelayRangeHigh;
	
	UPROPERTY(EditAnywhere, category = "Spawning")
	float SpawnDelayRangeLow;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	float SpawnDelay;

	void SpawnPickup();
};
