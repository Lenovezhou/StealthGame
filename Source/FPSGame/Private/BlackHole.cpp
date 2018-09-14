// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Array.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("rootcomp"));
	comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = comp;

	spherein = CreateDefaultSubobject<USphereComponent>(TEXT("spherein"));
	sphereout = CreateDefaultSubobject<USphereComponent>(TEXT("sphereout"));
	
	//sphereout->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	spherein->SetupAttachment(comp);
	sphereout->SetupAttachment(comp);

	spherein->SetSphereRadius(100);
	sphereout->SetSphereRadius(3000);

	//°ó¶¨ÊÂ¼þ
	spherein->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::handleoverlapevent);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> overlappingComps;

	sphereout->GetOverlappingComponents(overlappingComps);

	for (int32 i = 0; i < overlappingComps.Num();i++)
	{
		UPrimitiveComponent* primicomp = overlappingComps[i];
		if (primicomp && primicomp->IsSimulatingPhysics())
		{
			const float radius = sphereout->GetScaledSphereRadius();
			const float strength = -2000;

			primicomp->AddRadialForce(GetActorLocation(), radius, strength, ERadialImpulseFalloff::RIF_Constant,true);
		}
	}
}

void ABlackHole::handleoverlapevent(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult & SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

