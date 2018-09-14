// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	void MissionComplete(APawn* InstigatorPawn, bool successful);
	
	UFUNCTION(BlueprintImplementableEvent,Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool successful);

	UPROPERTY(EditDefaultsOnly,Category="spectatingviewtargetclass")
	TSubclassOf<AActor> spectatingviewtargetclass;

	UPROPERTY(EditDefaultsOnly,Category ="aiguard")
	TSubclassOf<AActor> subofclass;

};



