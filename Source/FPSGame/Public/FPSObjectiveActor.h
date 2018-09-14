// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	UPROPERTY(VisibleAnywhere, category = "components")
		UStaticMeshComponent * Meshcomp;

	UPROPERTY(VisibleAnywhere, category = "components")
		USphereComponent* Spherecomp;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
		UParticleSystem * EmitterFX;

	void PlayEffect();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
 
	//called when overlap
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
