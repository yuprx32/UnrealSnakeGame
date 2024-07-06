// SnakeGame project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameOverWidget.generated.h"

class UTextBlock;

UCLASS()
class SNAKEGAME_API USG_GameOverWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void UpdateScore(uint32 Score);

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ScoreText;
};
