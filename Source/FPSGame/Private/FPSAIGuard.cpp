// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "DrawDebugHelpers.h"
#include "Perception/PawnSensingComponent.h"
#include "FPSGameMode.h"
#include "GameFramework/Actor.h"
#include "AI/NavigationSystemBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sensingcomp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("ScensingComp"));
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	sensingcomp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::HandleSeePawn);
	sensingcomp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::HandleHearNoise);
	originrotation = GetActorRotation();
	CurrentState = EAiState::Ido;
	MoveNextPoint();
	SetReplicates(true);
}

void AFPSAIGuard::ResetOriginrotation()
{
	SetActorRotation(originrotation);
}

void AFPSAIGuard::Changestate(EAiState newstate)
{
	if (CurrentState != newstate)
	{
		CurrentState = newstate;
		OnRep_StateChange();
	}
}


void AFPSAIGuard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGuard, CurrentState);
}


void AFPSAIGuard::OnRep_StateChange()
{
	Changestate(CurrentState);
	OnAIStateChange(CurrentState);
}

void AFPSAIGuard::MoveNextPoint()
{
	if (nullptr == currentpoint || currentpoint == pointone)
	{
		currentpoint = pointtwo;
	}else
	{
		currentpoint = pointone;
	}
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIGuard::HandleSeePawn(APawn* seepawn)
{
	if (nullptr == seepawn)
	{
		return;
	}
	
	//be find over and display 
	AFPSGameMode* GM =Cast<AFPSGameMode>( GetWorld()->GetAuthGameMode());

	if (GM)
	{
		GM->MissionComplete(seepawn, false);
	}
	Changestate(EAiState::Alerted);
}

void AFPSAIGuard::HandleHearNoise(APawn * _ins, const FVector & Location, float Volume)
{
	
	if (CurrentState == EAiState::Alerted)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Green, false, 10.f);

	//vector direction
	FVector direction = Location - GetActorLocation();
	//Normalize
	direction.Normalize();
	//get the rotator
	FRotator fr = FRotationMatrix::MakeFromX(direction).Rotator();
	// execute rotate

	fr.Pitch = 0;
	fr.Roll = 0;

	SetActorRotation(fr);

	//set timer
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrigineRotation);

	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrigineRotation, this, &AFPSAIGuard::ResetOriginrotation, 3.f);
	Changestate(EAiState::Suspicious);
}


