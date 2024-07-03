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
    GameWidgets.Add(EUIMatchState::GameInProgress, GameplayWidget);

    GameOverWidget = CreateWidget<USG_GameOverWidget>(GetWorld(), GameOverClass);
    check(GameOverWidget);
    GameWidgets.Add(EUIMatchState::GameOver, GameOverWidget);

    for (auto& [UIState, GameWidget] : GameWidgets)
    {
        if (GameWidget)
        {
            GameWidget->AddToViewport();
            GameWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
    if (!InGame) return;

    using namespace SnakeGame;

    Game = InGame;

    SetUIMatchState(EUIMatchState::GameInProgress);
    GameplayWidget->UpdateScore(InGame->score());

    InGame->subscribeOnGameplayEvent(
        [&](GameplayEvent Event)
        {
            switch (Event)
            {
                case GameplayEvent::FoodTaken:  //
                    GameplayWidget->UpdateScore(InGame->score());
                    break;
                case GameplayEvent::GameOver:  //
                    SetUIMatchState(EUIMatchState::GameOver);
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

void ASG_HUD::SetUIMatchState(EUIMatchState MatchState)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (GameWidgets.Contains(MatchState))
    {
        CurrentWidget = GameWidgets[MatchState];
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}