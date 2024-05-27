// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelExit.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelExit::ALevelExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(BoxComp);
	BoxComp->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ALevelExit::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString ALevelExit::GetNextLevelName()
{
	return nextLevelName;
}

