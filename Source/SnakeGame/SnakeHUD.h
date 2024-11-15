// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGameMode.h"
#include "GameFramework/HUD.h"
#include "SnakeHUD.generated.h"

class ASnakeBase;

UCLASS()
class SNAKEGAME_API ASnakeHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ASnakeHUD();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	TSubclassOf<class UUserWidget> MainHUD;
	FString HUDLength = FString(TEXT("It just works!"));

	//int GetLength();

protected:
	void DrawHUD() override;

	int ShowScore = 0;

private:

	FLinearColor Colour = FLinearColor(255, 255, 255, 255);

};
