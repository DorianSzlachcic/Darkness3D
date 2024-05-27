// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(Mesh);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (IsValid(playerController) && IsValid(playerController->InputComponent))
	{
		playerController->InputComponent->BindAction("LeverInteract", IE_Pressed, this, &ALever::Interact);
	}

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALever::OnBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ALever::OnEndOverlap);
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Activated)
	//{
	//	GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, "Dziala");
	//}
}

void ALever::Interact()
{
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, "interact()");
	if (ableToInteract)
	{
		Activated = true;
		UGameplayStatics::PlaySound2D(GetWorld(), leverSound, 1, 1, 0);
	}
}

void ALever::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, "OnBeginOverlap()");
	//APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	ableToInteract = true;
}

void ALever::OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ableToInteract = false;
}