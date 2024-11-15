#pragma once

#include "Food.h"
#include "CoreMinimal.h"
#include "GridField.h"
#include "GameFramework/Actor.h"
#include "MasterSpawner.generated.h"


UCLASS()
class SNAKEGAME_API AMasterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMasterSpawner();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodClass;

	UFUNCTION(BlueprintCallable)
	void BuildField(const FVector CenteredLoction, const int x, const int y);
	
	template<typename T>
	void FindAllActors(UWorld* World, TArray<T*>& Out)
	{
		for (TActorIterator<T> It(World); It; ++It)
		{
			Out.Add(*It);
		}
	};
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	AActor* Segment;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D FieldSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> FieldTiles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AGridField> TileClass;
};
