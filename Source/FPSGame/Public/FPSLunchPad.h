// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FPSLunchPad.generated.h"

class UBoxComponent;
class UDecalComponent;

class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSLunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLunchPad();

protected:
	UPROPERTY(VisibleAnywhere,Category="staticmesh")
		UStaticMeshComponent* meshcomp;

	UPROPERTY(VisibleAnywhere,Category="boxcollision")
		UBoxComponent* boxcollision;

	UPROPERTY(VisibleAnywhere,Category="decalcomponent")
		UDecalComponent* decal;

	UPROPERTY(EditInstanceOnly,Category = "LunchPad")
		float jumpheigh;
	UPROPERTY(EditInstanceOnly, Category = "LunchPad")
		float jumpangle;
	UPROPERTY(EditInstanceOnly, Category = "LunchPad")
		UParticleSystem* jumpeffect;
public:	

	UFUNCTION()
		void handleoverlapevent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
