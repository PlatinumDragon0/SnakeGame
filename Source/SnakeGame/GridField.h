// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridField.generated.h"

USTRUCT(BlueprintType)
struct FGridFieldInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int x{};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int y{};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int z{};

	FGridFieldInfo() = default;

	FGridFieldInfo(int const NewX, int const NewY, int const NewZ)
		: x(NewX), y(NewY), z(NewZ)
	{
	
	}
};

UCLASS()
class SNAKEGAME_API AGridField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridField();

	void SetTileInfo(FGridFieldInfo InFieldInfo)
	{
		FieldInfo = InFieldInfo;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AloowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AloowPrivateAccess = true))
	FGridFieldInfo FieldInfo;

/*
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/
};
