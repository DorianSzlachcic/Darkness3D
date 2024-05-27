// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitKey.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
AExitKey::AExitKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComp->SetupAttachment(Mesh);
	BoxComp->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AExitKey::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AExitKey::OnBeginOverlap);
}

// Called every frame
void AExitKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExitKey::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	player->hasKey = true;
	UGameplayStatics::PlaySound2D(GetWorld(), keySound, 1, 1, 0);
	Destroy();
}

