// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Objective_Actor_.h"
#include "FPSCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPS_Objective_Actor_::AFPS_Objective_Actor_()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//Setting the collision of the Sphere component to only check queries
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Setting the response of the collision to Ignore
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Setting the collision response to only look for player object overlap
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPS_Objective_Actor_::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
	
}

void AFPS_Objective_Actor_::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}


void AFPS_Objective_Actor_::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter) 
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}
}

