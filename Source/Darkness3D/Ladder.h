// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Ladder.generated.h"

UCLASS()
class DARKNESS3D_API ALadder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALadder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* LadderBase;

	UPROPERTY(VisibleAnywhere)
		UInstancedStaticMeshComponent* LadderParts;
	
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		float ladderHeight = 100.f;

	UPROPERTY(EditAnywhere)
		UStaticMesh* LadderMesh;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
