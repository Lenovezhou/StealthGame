// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;
class USoundBase;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();
	
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "components")
		UBoxComponent* overlapComp;

	UPROPERTY(VisibleAnywhere, Category = "components")
		UDecalComponent* decalcomp;


	UFUNCTION()
		void HandleEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(EditDefaultsOnly, Category = "sound")
		USoundBase* fallsound;
	UPROPERTY(EditDefaultsOnly, Category = "sound")
		USoundBase* completedsound;

	
};
