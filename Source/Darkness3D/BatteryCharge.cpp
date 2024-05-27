// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryCharge.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
ABatteryCharge::ABatteryCharge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);


	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComp->SetupAttachment(Mesh);
	BoxComp->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ABatteryCharge::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABatteryCharge::OnBeginOverlap);
}

// Called every frame
void ABatteryCharge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABatteryCharge::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerCharacter>(OtherActor);
	player->ChargeFlashlightBattery();
	UGameplayStatics::PlaySound2D(GetWorld(), batterySound, 1, 1, 0);
	Destroy();
}

