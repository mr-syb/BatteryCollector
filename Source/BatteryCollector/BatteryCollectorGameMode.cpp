// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PrimaryActorTick.bCanEverTick = true;

	DecayRate = 0.05f;
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
	if (MyCharacter)
	{
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetGameState(EBatteryPlayState::EWon);
		}
		else if(MyCharacter->GetCurrentPower() > 0)
		{
			//UE_LOG(LogClass, Log, TEXT("GameMode Tick is called"));
			MyCharacter->UpdatePower(-DecayRate*DeltaTime*MyCharacter->GetIntialPower());
		}
		else
		{
			SetGameState(EBatteryPlayState::EGameOver);
		}
	}
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), AllActors);
	for (auto Actor : AllActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetGameState(EBatteryPlayState::EPlaying);

	ABatteryCollectorCharacter* MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = MyCharacter->GetIntialPower()*1.25;
	}
	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

void ABatteryCollectorGameMode::SetGameState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
	HandleGameState(NewState);
}

void ABatteryCollectorGameMode::HandleGameState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		case EBatteryPlayState::EPlaying:
		{
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawnVolumeActive(true);
			}
		}break;
		case EBatteryPlayState::EWon:
		{
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawnVolumeActive(false);
			}
		}break;
		case EBatteryPlayState::EGameOver:
		{
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawnVolumeActive(false);
			}
			APlayerController* MyController = UGameplayStatics::GetPlayerController(this,0);
			if (MyController) 
			{
				MyController->SetCinematicMode(true, false, false, true, true);
			}
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter) 
			{
				MyCharacter->GetMesh()->SetSimulatePhysics(true);
				MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}break;
		case EBatteryPlayState::EUnknown:
		{
			//do nothing
		}break;
		default:
			break;

	}
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentGameState() const
{
	return CurrentState;
}

