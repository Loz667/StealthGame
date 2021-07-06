// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPadActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class FPSGAME_API ALaunchPadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPadActor();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UFUNCTION()
		void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Impulse value applied to character on overlap function
	UPROPERTY(EditInstanceOnly, Category = "Launch Pad")
		float LaunchStrength;

	//Angle added to Actor rotation upon launching character
	UPROPERTY(EditInstanceOnly, Category = "Launch Pad")
		float LaunchPitchAngle;

	//Effect simulated when overlap occurs
	UPROPERTY(EditInstanceOnly, Category = "Launch Pad")
		UParticleSystem* ActivateLaunchPadEffect;
	
};
