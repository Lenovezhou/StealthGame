// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "FPSPlayerController.h"



void AFPSGameState::GamestateComplete_Implementation(APawn* _ins, bool issuccessful)
{
	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it ; it ++)
	{
		AFPSPlayerController* pc = Cast<AFPSPlayerController>(it->Get());
		if (pc && pc->IsLocalController())
		{
			pc->OmMissionComplete(_ins, issuccessful);

			APawn* ap = pc->GetPawn();
			if (ap && ap->IsLocallyControlled())
			{
				ap->DisableInput(pc);
			}
		}
	}

}
