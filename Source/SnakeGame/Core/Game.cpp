
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
    m_snake = MakeShared<Snake>(settings.snake);
    m_food = MakeShared<Food>();

    updateGrid();

    generateFood();
}

void Game::update(float DeltaSeconds, Input input)
{
    if (m_gameOver || !updateTime(DeltaSeconds)) return;

    move(input);

    if (died())
    {
        m_gameOver = true;
        UE_LOG(LogGame, Display, TEXT("Game Over"));
        UE_LOG(LogGame, Display, TEXT("Score: %i"), m_score);
    }

    if (foodTaken())
    {
        ++m_score;
        m_snake->increase();
        generateFood();
    }
}

void Game::move(Input input)
{
    m_snake->move(input);
    updateGrid();
}

void Game::updateGrid()
{
    m_grid->update(m_snake->body(), CellType::Snake);
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
    m_food->setPosition(m_grid->randomEmptyPosition());
    m_grid->update(m_food->position(), CellType::Food);
}

bool Game::foodTaken() const
{
    return m_grid->hitTest(m_snake->head(), CellType::Food);
}
