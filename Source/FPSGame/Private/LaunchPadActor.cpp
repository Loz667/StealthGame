// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPadActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPadActor::ALaunchPadActor()
{
 	
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));;
    OverlapComp->SetBoxExtent(FVector(75, 75, 50));
    RootComponent = OverlapComp;

    OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPadActor::OverlapLaunchPad);

    LaunchStrength = 1500;
    LaunchPitchAngle = 45.0f;

}

void ALaunchPadActor::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    //Make a rotator that combines with the defined pitch angle which is converted to a direction vector multiplied by strength
    FRotator LaunchDirection = GetActorRotation();
    LaunchDirection.Pitch += LaunchPitchAngle;
    FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

    ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
    if (OtherCharacter)
    {
        //Player launched using specified velocity with two bools set to ignore current player velocity
        OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);

        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
    }
    //No player overlap, so check if there's a physics-simulating actor that can be launched
    else if (OtherComp && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
    }

}


