// SnakeGame project

#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Containers/List.h"

namespace SnakeGame
{
// width x height
struct Dim
{
    uint32 width;
    uint32 height;
};

struct Position
{
    Position(const Position& position = Position::Zero) : x(position.x), y(position.y) {}
    Position(uint32 inX, uint32 inY) : x(inX), y(inY){};

    uint32 x;
    uint32 y;

    FORCEINLINE Position& operator+=(const Position& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    FORCEINLINE bool operator==(const Position& rhs) const { return x == rhs.x && y == rhs.y; }

    static const Position Zero;
};

struct Input
{
    int8 x;
    int8 y;

    FORCEINLINE bool opposite(const Input& rhs) const  //
    {
        return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
    }

    static const Input Default;
};

enum class CellType
{
    Empty = 0,
    Wall,
    Snake,
    Food
};

struct Settings
{
    Dim gridDims{40, 10};

    struct Snake
    {
        uint32 defaultSize{4};
        Position startPosition{Position::Zero};
    } snake;

    float gameSpeed{1.0f};
};

using TSnakeList = TDoubleLinkedList<Position>;
using TPositionPtr = TSnakeList::TDoubleLinkedListNode;

enum class GameplayEvent
{
    GameOver = 0,
    GameCompleted,
    FoodTaken
};

using GameplayEventCallback = TFunction<void(GameplayEvent)>;

}  // namespace SnakeGame
