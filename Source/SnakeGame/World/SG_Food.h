// SnakeGame project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Food.h"
#include "SG_Food.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ASG_Food : public AActor
{
    GENERATED_BODY()

public:
    ASG_Food();

    void SetModel(const TSharedPtr<SnakeGame::Food>& InFood, uint32 InCellSize, const SnakeGame::Dim& InDims);
    void UpdateColor(const FLinearColor& Color);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* FoodMesh;

public:
    virtual void Tick(float DeltaTime) override;

private:
    TWeakPtr<SnakeGame::Food> Food;
    uint32 CellSize;
    SnakeGame::Dim Dims;
};
