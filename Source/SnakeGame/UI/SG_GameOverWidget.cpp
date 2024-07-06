// SnakeGame project

#include "UI/SG_GameOverWidget.h"
#include "World/SG_WorldUtils.h"
#include "Components/TextBlock.h"

void USG_GameOverWidget::SetScore(uint32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
    }
}

void USG_GameOverWidget::SetResetGameKeyName(const FString& ResetGameKeyName) 
{
    if (ResetGameText)
    {
        const FString ResetGameInfo = FString::Printf(TEXT("press %s to reset"), *ResetGameKeyName.ToLower());
        ResetGameText->SetText(FText::FromString(ResetGameInfo));
    }
}
