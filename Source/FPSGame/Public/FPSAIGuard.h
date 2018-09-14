// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAiState:uint8
{
	Ido,

	Suspicious,
	Alerted
};


UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();
	FTimerHandle TimerHandle_ResetOrigineRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "component")
		UPawnSensingComponent* sensingcomp;

	FRotator originrotation;

	UFUNCTION()
		void ResetOriginrotation();


	UPROPERTY(ReplicatedUsing=OnRep_StateChange)
	EAiState CurrentState;

	void Changestate(EAiState newstate);


	UFUNCTION()
	void OnRep_StateChange();

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnAIStateChange(EAiState newstate);

	UPROPERTY(EditInstanceOnly, Category ="AI")
		AActor* pointone;
	UPROPERTY(EditInstanceOnly, Category = "AI")
		AActor* pointtwo;

	AActor* currentpoint;

	void MoveNextPoint();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void HandleSeePawn(APawn* seepawn);
	
	UFUNCTION()
		void HandleHearNoise(APawn* _ins, const FVector& Location, float Volume);
	
};
