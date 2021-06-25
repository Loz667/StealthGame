// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHoleActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPSBlackHoleActor::AFPSBlackHoleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void AFPSBlackHoleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSBlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

