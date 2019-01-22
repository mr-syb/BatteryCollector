// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

UENUM(BlueprintType)
enum  EBatteryPlayState
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime)override;
	virtual void BeginPlay()override;

	UFUNCTION(BlueprintPure, category = "Power")
	float GetPowerToWin() const;

	void SetGameState(EBatteryPlayState NewState);

	void HandleGameState(EBatteryPlayState NewState);

	UFUNCTION(BlueprintPure, category = "Power")
	EBatteryPlayState GetCurrentGameState() const;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,category = "Power",meta = (BlueprintProtected = "true"))
	float DecayRate;

	UPROPERTY(BlueprintReadOnly, category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
private:
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;
};



