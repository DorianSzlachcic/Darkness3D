// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Lever.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraSpringArm);

	OnPlayerSpotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("OnPlayerSpotLight"));
	OnPlayerSpotlight->SetupAttachment(RootComponent);
	OnPlayerSpotlight->bAffectsWorld = true;

	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLightComponent->SetupAttachment(RootComponent);
	SpotLightComponent->bAffectsWorld = true;
}

void APlayerCharacter::OnConstruction(const FTransform& Transform)
{
	OnPlayerSpotlight->SetRelativeLocation(FVector(-400.f, 0, 0));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraSpringArm->TargetArmLength = springArmLength;
	GetCharacterMovement()->AirControl = airControl;

	SpotLightComponent->SetVisibility(false);
	OnPlayerSpotlight->SetVisibility(false);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (flashlightBattery <= 0.f)
	{
		SpotLightComponent->SetVisibility(false);
		OnPlayerSpotlight->SetVisibility(false);
	}

	if (!pressedAiming || flashlightBattery <= 0.f)
	{
		if (mentalHealthBuffer > 0.f)
			mentalHealthBuffer -= bufferDropSpeed;
		else if (mentalHealth > 0.f)
			mentalHealth -= mentalHealthDropSpeed;

	}

	if (mentalHealth <= 0.f)
		flashlightBattery = 0.f;



	if (pressedAiming && flashlightBattery > 0.f)
	{
		flashlightBattery -= batteryDischargeSpeed;

		if (mentalHealthBuffer < 1.f)
			mentalHealthBuffer += 2*bufferDropSpeed;

		APlayerController* playerController = (APlayerController*)Controller;

		FVector mouseLocation;
		FVector mouseDirection;
		playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		FVector start = mouseLocation;
		FVector end =  mouseDirection + (mouseDirection * 100000);

		//FCollisionQueryParams traceParams;
		//FHitResult outHit;
		//GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, traceParams);
		//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1.0);
		FVector aimLoc = AimingLocation(start, start + (mouseDirection * 100000));
		//DrawDebugSphere(GetWorld(), aimLoc, 20, 1, FColor::Red, false, 2.0);

		FVector deltaVec = aimLoc - GetActorLocation();
		deltaVec.Normalize();
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, deltaVec.ToString());
		float yaw, pitch;
		UKismetMathLibrary::GetYawPitchFromVector(deltaVec, yaw, pitch);

		if (deltaVec.Y > 0)
		{
			GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
			SpotLightComponent->SetRelativeLocation(FVector(0.f, FMath::Abs(SpotLightComponent->GetRelativeLocation().Y), 0.f));
			facingRight = -1;
		}
		else if (deltaVec.Y < 0)
		{
			GetMesh()->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
			SpotLightComponent->SetRelativeLocation(FVector(0.f, -FMath::Abs(SpotLightComponent->GetRelativeLocation().Y), 0.f));
			facingRight = 1;
		}

		SpotLightComponent->SetWorldRotation(FRotator(pitch, yaw, 0));
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LadderUp", this, &APlayerCharacter::LadderUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &APlayerCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &APlayerCharacter::StopAiming);
}

void APlayerCharacter::MoveRight(float value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	if (value > 0 && !pressedAiming)
		GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	else if (value < 0 && !pressedAiming)
		GetMesh()->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	AddMovementInput(direction, value);
}

void APlayerCharacter::LadderUp(float value)
{
	if (isOnLadder)
	{
		FVector direction = GetActorUpVector();
		AddMovementInput(direction, value);
	}
}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::StartAiming()
{
	pressedAiming = true;
	SpotLightComponent->SetVisibility(true);
	OnPlayerSpotlight->SetVisibility(true);
	UGameplayStatics::PlaySound2D(GetWorld(), flashlightOnSound, 1, 1, 0);
}

void APlayerCharacter::StopAiming()
{
	pressedAiming = false;
	SpotLightComponent->SetVisibility(false);
	OnPlayerSpotlight->SetVisibility(false);
	UGameplayStatics::PlaySound2D(GetWorld(), flashlightOffSound, 1, 1, 0);
}

void APlayerCharacter::ChargeFlashlightBattery()
{
	flashlightBattery = 1.f;
}

FVector APlayerCharacter::AimingLocation(FVector InputLocation, FVector InputPin)
{
	FVector lightLoc = SpotLightComponent->GetComponentLocation();

	float y = (((lightLoc.X - InputLocation.X) * (InputPin.Y - InputLocation.Y)) / (InputPin.X - InputLocation.X)) + InputLocation.Y;
	float z = (((lightLoc.X - InputLocation.X) * (InputPin.Z - InputLocation.Z)) / (InputPin.X - InputLocation.X)) + InputLocation.Z;

	return FVector(lightLoc.X, y, z);
}

