// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	MoveBank = EMovementDirection::DOWN;
	LastMoveDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(1);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveBank = LastMoveDirection;
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0 ; i < ElementsNum ; ++i )
	{ 
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement;

		NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);

		NewSnakeElement->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NewSnakeElement);
		if (ElemIndex == 0)
		{
			NewSnakeElement -> SetFirstElementType();
		}
	}
}

void ASnakeBase::Move()
{
	if (Length > SnakeElements.Num())
	{
		AddSnakeElement(1);
	}
	
	FVector MovementVector;
	FRotator ElementRotation;

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		ElementRotation = FRotator(0, 360, 0);
		break;

	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		ElementRotation = FRotator(0, 180, 0);
		break;

	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		ElementRotation = FRotator(0, 90, 0);
		break;

	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		ElementRotation = FRotator(0, 270, 0);
		break;
	}


	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		FRotator PrevRotation = PrevElement->GetActorRotation();
		CurrentElement->SetActorLocation(PrevLocation);
		CurrentElement->SetActorRotation(PrevRotation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->SetActorRotation(ElementRotation);
	SnakeElements[0]->ToggleCollision();

}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

int ASnakeBase::LengthGetter()
{
	return Length;
}

