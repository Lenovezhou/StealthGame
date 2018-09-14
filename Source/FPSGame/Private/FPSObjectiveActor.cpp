// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	//���ɶ�Ӧ����
	Meshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meshcomp"));
	Spherecomp = CreateDefaultSubobject<USphereComponent>(TEXT("spherecom"));

	//�㼶��
	RootComponent = Meshcomp;
	Spherecomp->SetupAttachment(Meshcomp);

	//��ײ����
	Meshcomp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Spherecomp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Spherecomp->SetCollisionResponseToAllChannels(ECR_Ignore);
	Spherecomp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SetReplicates(true);
}

void AFPSObjectiveActor::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterFX, GetActorLocation());

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEffect();
}



void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffect();
	
	if (Role == ROLE_Authority)
	{
		AFPSCharacter* mycharacter = Cast<AFPSCharacter>(OtherActor);
		if (mycharacter)
		{
			mycharacter->bIscarringObject = true;
			Destroy();
		}
	}
}

