// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHUD.h"
#include "Blueprint/UserWidget.h"
#include "SnakeBase.h"
#include "SnakeGameMode.h"
#include "Kismet/GameplayStatics.h"

ASnakeHUD::ASnakeHUD() : Super()
{
	ConstructorHelpers::FClassFinder<UUserWidget> WBPScore(TEXT("/Game/WBP_Score"));
	MainHUD = WBPScore.Class;	
}

/*int ASnakeHUD::GetLength()
{
	ASnakeBase* Snake = Cast<ASnakeBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int Score = Snake->Length;
	return Score;
}*/

void ASnakeHUD::DrawHUD()
{
	Super::DrawHUD();	
	this -> DrawText(HUDLength, Colour,110.0f, 110.0f);
}

void ASnakeHUD::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* SnakeWidget = CreateWidget(GetWorld(), MainHUD);
	SnakeWidget->AddToViewport();
	ShowScore = SnakeGameMode -> ScoreGetter();
}

void ASnakeHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//HUDLength = Length;
}