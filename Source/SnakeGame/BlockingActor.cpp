// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockingActor.h"
#include "SnakeBase.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABlockingActor::ABlockingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlockingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlockingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlockingActor::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("DIE!"));
		Snake->Destroy();
	}
}

