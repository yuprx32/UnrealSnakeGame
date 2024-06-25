// SnakeGame project

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Core/Game.h"
#include "SnakeGame/Core/Grid.h"

DEFINE_SPEC(FSnakeGame, "Snake",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FSnakeGame::Define()
{
    using namespace SnakeGame;

    Describe("CoreGame", [this]() {  //
        It("GridShouldExist",
            [this]()
            {
                Settings GS;
                GS.gridDims = Dim{10, 10};
                GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
                const auto CoreGame = Game(GS);
                TestTrueExpr(CoreGame.grid().IsValid());
            });
    });
}

#endif
