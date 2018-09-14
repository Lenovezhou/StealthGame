// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLunchPad.h"
#include "Components/MeshComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

// Sets default values
AFPSLunchPad::AFPSLunchPad()
{
	decal = CreateDefaultSubobject<UDecalComponent>(TEXT("decalcomp"));
	decal->SetupAttachment(RootComponent);

	boxcollision = CreateDefaultSubobject<UBoxComponent>(TEXT("collision"));
	boxcollision->SetBoxExtent(FVector(75,75,50));

	RootComponent = boxcollision;

	meshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("rootmesh"));
	meshcomp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	meshcomp->SetupAttachment(boxcollision);

	//boxcollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//boxcollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	boxcollision->OnComponentBeginOverlap.AddDynamic(this, &AFPSLunchPad::handleoverlapevent);


	jumpheigh = 1500;
	jumpangle = 35.0f;

}


void AFPSLunchPad::handleoverlapevent(UPrimitiveComponent * OverlappedComponent,
	AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		AFPSCharacter* mycharacter = Cast<AFPSCharacter>(OtherActor);

		FRotator rotator = GetActorForwardVector().Rotation();
		rotator.Pitch += jumpangle;
		FVector lunchvelocity = rotator.Vector() * jumpheigh;

		if (mycharacter)
		{
			mycharacter->LaunchCharacter(lunchvelocity, true, true);
		}
		else if (OtherComp && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulse(lunchvelocity, NAME_None, true);
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), jumpeffect, GetActorLocation());

	}
}

