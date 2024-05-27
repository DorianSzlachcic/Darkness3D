// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class DARKNESS3D_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float value);
	void LadderUp(float value);

	void StartJump();
	void StopJump();

	void StartAiming();
	void StopAiming();

	void ChargeFlashlightBattery();


	UPROPERTY(EditAnywhere)
		bool pressedAiming = false;

	UPROPERTY(BlueprintReadOnly)
		bool isOnLadder = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		bool hasKey = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int facingRight = -1;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
		USpotLightComponent* SpotLightComponent;

	UPROPERTY(VisibleAnywhere)
		USpotLightComponent* OnPlayerSpotlight;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float airControl = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float springArmLength = 500.f;

	UPROPERTY(BlueprintReadOnly)
		float flashlightBattery = 1.0f;

	UPROPERTY(BlueprintReadOnly)
		float mentalHealth = 1.0f;

	UPROPERTY(BlueprintReadOnly)
		float mentalHealthBuffer = 1.0f;

	UPROPERTY(EditAnywhere)
		float batteryDischargeSpeed = 0.005f;

	UPROPERTY(EditAnywhere)
		float bufferDropSpeed = 0.005f;

	UPROPERTY(EditAnywhere)
		float mentalHealthDropSpeed = 0.005f;

	UPROPERTY(EditAnywhere)
		USoundBase* flashlightOnSound;
	UPROPERTY(EditAnywhere)
		USoundBase* flashlightOffSound;

private:
	FVector AimingLocation(FVector InputLocation, FVector InputPin);
};
