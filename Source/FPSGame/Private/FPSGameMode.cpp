// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Array.h"
#include "FPSGameState.h"
#include "Engine/World.h"
#include "FPSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "FPSAIGuard.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();

}

void AFPSGameMode::MissionComplete(APawn * InstigatorPawn,bool successful)
{
	//set view target with blend
	if (InstigatorPawn)
	{
		APlayerController* pc = Cast<APlayerController>(InstigatorPawn->GetController());
		if (pc)
		{
			TArray<AActor*> outarray;
			UGameplayStatics::GetAllActorsOfClass(this, spectatingviewtargetclass, outarray);
			if (outarray.Num() > 0)
			{
				AActor* newtarget = outarray[0];
				for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++)
				{
					APlayerController* apc = it->Get();
					if (apc)
					{
						apc->SetViewTargetWithBlend(newtarget, 1, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("trying to cast to faled!!!!!!"));
		}
	}

	//Notify All Client GamestateComplete
	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->GamestateComplete(InstigatorPawn, successful);
	}

	//event on blueprint
	OnMissionCompleted(InstigatorPawn,successful);

	//Let AI guard to rest
	TArray<AActor*> allactor;
	UGameplayStatics::GetAllActorsOfClass(this, subofclass, allactor);
	for (int32 i = 0 ;i < allactor.Num();i++)
	{
		AFPSAIGuard* aiguard = Cast<AFPSAIGuard>(allactor[i]);
		FTimerHandle th = aiguard->TimerHandle_ResetOrigineRotation;
		GetWorldTimerManager().ClearTimer(th);
	}


}
