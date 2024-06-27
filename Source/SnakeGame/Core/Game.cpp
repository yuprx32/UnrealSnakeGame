
// SnakeGame project

#include "Game.h"
#include "Grid.h"
#include "Snake.h"
#include "Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All)

using namespace SnakeGame;

SnakeGame::Game::Game(const Settings& settings) : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
    checkf(m_grid->dim().width / 2 >= settings.snake.defaultSize, TEXT("Snake initial length [%i] doesn't fit grid width [%i]"),
        settings.snake.defaultSize, m_grid->dim().width);
    m_snake = MakeShared<Snake>(settings.snake);
    m_food = MakeShared<Food>();

    updateGrid();

    generateFood();
}

void Game::update(float DeltaSeconds, Input input)
{
    if (m_gameOver || !updateTime(DeltaSeconds)) return;

    m_snake->move(input);

    if (died())
    {
        m_gameOver = true;
        UE_LOG(LogGame, Display, TEXT("Game Over"));
        UE_LOG(LogGame, Display, TEXT("Score: %i"), m_score);
        return;
    }

    if (foodTaken())
    {
        ++m_score;
        m_snake->increase();
        generateFood();
    }

    updateGrid();
}

void Game::updateGrid()
{
    m_grid->update(m_snake->links().GetHead(), CellType::Snake);
    m_grid->printDebug();
}

bool Game::updateTime(float DeltaSeconds)
{
    m_moveSeconds += DeltaSeconds;

    if (m_moveSeconds < c_settings.gameSpeed)
    {
        return false;
    }
    else
    {
        m_moveSeconds = 0.0f;
        return true;
    }
}

bool SnakeGame::Game::died() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Wall) || m_grid->hitTest(m_snake->head(), CellType::Snake);
}

void Game::generateFood()
{
    Position foodPosition;
    if (m_grid->randomEmptyPosition(foodPosition))
    {
        m_food->setPosition(foodPosition);
        m_grid->update(m_food->position(), CellType::Food);
    }
    else
    {
        m_gameOver = true;
        UE_LOG(LogGame, Display, TEXT("Game Completed"));
        UE_LOG(LogGame, Display, TEXT("Score: %i"), m_score);
    }
}

bool Game::foodTaken() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Food);
}
