// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHoleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSBlackHoleActor::AFPSBlackHoleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetupAttachment(MeshComp);
	InnerSphereComp->SetSphereRadius(100);

	//Binds to event
	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHoleActor::OverlapInnerSphere);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetupAttachment(MeshComp);
	OuterSphereComp->SetSphereRadius(1000);

}

// Called when the game starts or when spawned
void AFPSBlackHoleActor::BeginPlay()
{
	Super::BeginPlay();
}


//The event. Will destroy any overlapped component
void AFPSBlackHoleActor::OverlapInnerSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}


// Called every frame
void AFPSBlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Finds overlapping components that can collide and must be physically simulating
	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterSphereComp->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			//This is the component being looked for, must be physically simulating in order to apply the following force

			const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();
			const float ForceStrength = -2000; //The negative value here will create a pull

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}


