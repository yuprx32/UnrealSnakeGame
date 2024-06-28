// SnakeGame project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SG_SnakeLink.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASG_SnakeLink : public AActor
{
    GENERATED_BODY()

public:
    ASG_SnakeLink();

    void UpdateColors(const FLinearColor& Color);
    void UpdateScale(uint32 CellSize);
    void Explode();

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* LinkMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FVX")
    TObjectPtr<UNiagaraSystem> ExplosionEffect;

    FLinearColor LinkColor;
};
