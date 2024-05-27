// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "LevelExit.generated.h"

UCLASS()
class DARKNESS3D_API ALevelExit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelExit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
		FString nextLevelName = "SandboxLevel";

	UFUNCTION(BlueprintCallable)
		FString GetNextLevelName();

};
