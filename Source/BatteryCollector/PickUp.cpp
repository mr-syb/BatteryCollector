// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bIsActive = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickUp::IsActive()
{
	return bIsActive;
}

void APickUp::SetIsActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickUp::WasCollected_Implementation()
{
	FString PickupDebugStr = GetName();
	UE_LOG(LogClass, Log, TEXT("you have collected %s"), *PickupDebugStr);
}

