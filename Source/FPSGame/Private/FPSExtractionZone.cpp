// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "GameFramework/GameMode.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	overlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverLapComp"));
	overlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	overlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	overlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	overlapComp->SetBoxExtent(FVector(200.0f));
	overlapComp->SetHiddenInGame(false);
	overlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleEvent);

	RootComponent = overlapComp;

	decalcomp = CreateDefaultSubobject<UDecalComponent>(TEXT("decalcomp"));
	decalcomp->DecalSize = FVector(200.0f);
	decalcomp->SetupAttachment(RootComponent);
}


void AFPSExtractionZone::HandleEvent(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	/*check otheractor == player && player has colliction something*/

	AFPSCharacter* mypown = Cast<AFPSCharacter>(OtherActor);

	if (nullptr == mypown)
	{
		return;
	}

	if (mypown->bIscarringObject)
	{
		AFPSGameMode* GM = Cast<AFPSGameMode>( GetWorld()->GetAuthGameMode());
		
		if (GM)
		{
			GM->MissionComplete(mypown, true);
			UGameplayStatics::PlaySoundAtLocation(this, completedsound, GetActorLocation());
		}
	}
	else{
		UGameplayStatics::PlaySoundAtLocation(this, fallsound, GetActorLocation());

	}
}

