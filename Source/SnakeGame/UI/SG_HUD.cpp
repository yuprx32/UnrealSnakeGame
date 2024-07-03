// SnakeGame project

#include "SG_HUD.h"
#include "SG_GameplayWidget.h"
#include "SG_GameOverWidget.h"
#include "Core/Game.h"

void ASG_HUD::BeginPlay()
{
    Super::BeginPlay();

    GameplayWidget = CreateWidget<USG_GameplayWidget>(GetWorld(), GameplayWidgetClass);
    check(GameplayWidget);

    GameOverWidget = CreateWidget<USG_GameOverWidget>(GetWorld(), GameOverClass);
    check(GameOverWidget);

    GameplayWidget->AddToViewport();
    GameOverWidget->AddToViewport();

    GameplayWidget->SetVisibility(ESlateVisibility::Visible);
    GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
    if (!InGame) return;

    GameplayWidget->SetVisibility(ESlateVisibility::Visible);
    GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);

    Game = InGame;

    GameplayWidget->UpdateScore(InGame->score());

    using namespace SnakeGame;

    InGame->subscribeOnGameplayEvent(
        [&](GameplayEvent Event)
        {
            switch (Event)
            {
                case GameplayEvent::FoodTaken: GameplayWidget->UpdateScore(InGame->score()); break;
                case GameplayEvent::GameOver:
                    GameplayWidget->SetVisibility(ESlateVisibility::Collapsed);
                    GameOverWidget->SetVisibility(ESlateVisibility::Visible);
                    break;
            }
        });
}

void ASG_HUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (Game.IsValid())
    {
        GameplayWidget->SetGameTime(Game.Pin()->gameTime());
    }
}
