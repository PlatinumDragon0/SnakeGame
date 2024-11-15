// Fill out your copyright notice in the Description page of Project Settings.


#include "GridField.h"

// Sets default values
AGridField::AGridField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGridField::BeginPlay()
{
	//Super::BeginPlay();
	
}

/*
void AGridField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
*/
