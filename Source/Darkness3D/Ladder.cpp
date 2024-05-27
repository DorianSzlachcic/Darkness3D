// Fill out your copyright notice in the Description page of Project Settings.


#include "Ladder.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "PlayerCharacter.h"

// Sets default values
ALadder::ALadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LadderBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LadderBase"));
	SetRootComponent(LadderBase);

	LadderParts = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Middles"));
	LadderParts->SetupAttachment(RootComponent);
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALadder::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ALadder::OnEndOverlap);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StaticMeshes/Ladder_LadderPiece.Ladder_LadderPiece'"));
	LadderMesh = Mesh.Object;
}

void ALadder::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	LadderParts->SetRelativeLocation(FVector(0, 300.f, 100.f));
	LadderParts->SetStaticMesh(LadderMesh);
	LadderParts->ClearInstances();

	for (int i = 0; i < ladderHeight / 100; i++)
	{
		FTransform InstanceTransform(FVector(0.0f, 0.0f, 175.f * i));
		LadderParts->AddInstance(InstanceTransform);
	}

	Box->SetRelativeLocation(FVector(-70.f, 0.f, ladderHeight));
	Box->SetBoxExtent(FVector(80.f, 120.f, ladderHeight));
}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadder::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);
	playerCharacter->isOnLadder = true;
	playerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void ALadder::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);
	playerCharacter->isOnLadder = false;
	playerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

}
