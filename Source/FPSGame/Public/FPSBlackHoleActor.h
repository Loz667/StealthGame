// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHoleActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHoleActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	//The inner sphere will destroy the overlapping components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphereComp;

	//The outer sphere will pull the components towards the inner sphere
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphereComp;

	//Marked as function to bind with overlap event
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
