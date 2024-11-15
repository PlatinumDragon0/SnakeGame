#include "MasterSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

AMasterSpawner::AMasterSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMasterSpawner::BuildField(const FVector CenteredLoction, const int x, const int y)
{
	if (FieldTiles.Num() == 0)
	{
		FieldSize.X = x;
		FieldSize.Y = y;

		for (auto OuterIndex{ 0 }; OuterIndex <= y - 1; ++OuterIndex)
		{
			for (auto InnerIndex{ 0 }; InnerIndex <= x - 1; ++InnerIndex)
			{
				float constexpr SectorSize = 45.f;

				FVector SpawnLocation = FVector(static_cast<float>(InnerIndex) - static_cast<float>(x) / 2.f,
												static_cast<float>(OuterIndex) - static_cast<float>(y) / 2.f,
												0.f) 
					* SectorSize 
					* 1.f 
					+ CenteredLoction;

				FTransform SpawnTransform;
				SpawnTransform.SetLocation(SpawnLocation);

				if (TileClass)
				{
					AActor* TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
																								this, 
																								TileClass.LoadSynchronous(), 
																								SpawnTransform);

					AGridField* Tile = Cast<AGridField>(TileToSpawn);
					if (Tile)
					{
						Tile->SetTileInfo(FGridFieldInfo(InnerIndex, OuterIndex, 0));
					}

					TileToSpawn->FinishSpawning(SpawnTransform);
					FieldTiles.Add(TileToSpawn);
					TileToSpawn->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				}
			}
		}
	}
}

void AMasterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AMasterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	int32 countFieldTiles = FieldTiles.Num();
	if (countFieldTiles == 0)
		return; 

	int32 RandomNumber = FMath::RandRange(0, countFieldTiles - 1);
	AActor* FieldTile = FieldTiles[RandomNumber];

	TArray<AFood*> Food;
	TArray<AActor*> SnakeBits;

	FindAllActors(GetWorld(), Food);
	int32 countFood = Food.Num();
	FieldTile->GetOverlappingActors(SnakeBits);
	int32 countSnakeBits = SnakeBits.Num();

	if (countSnakeBits != 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Something detected!"));
	}

	if (countFood < 5  && countSnakeBits == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Valid spawn"));
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		FVector spawnLocation = FieldTile->GetActorLocation();
		FRotator rotator;
		GetWorld()->SpawnActor<AFood>(FoodClass, spawnLocation, rotator);
	}
}

