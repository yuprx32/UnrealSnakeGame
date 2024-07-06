// SnakeGame project

#include "UI/SG_GameOverWidget.h"
#include "World/SG_WorldUtils.h"
#include "Components/TextBlock.h"

void USG_GameOverWidget::UpdateScore(uint32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(Score));
    }
}