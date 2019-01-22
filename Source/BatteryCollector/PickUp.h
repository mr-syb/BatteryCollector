// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UStaticMeshComponent* GetMesh() { return PickupMesh; }

	UFUNCTION(BlueprintPure, category = "Pickup")
	bool IsActive();

	UFUNCTION(BlueprintCallable,category = "Pickup")
	void SetIsActive(bool NewPickupState);

	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();
	
protected:
	bool bIsActive;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Pickup", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;
};
