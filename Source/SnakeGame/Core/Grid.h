// SnakeGame project

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
class Grid
{
public:
    Grid(const Dim& dim);

    /**
     * Returns grid dimensions including walls (width + 2, height + 2)
     * @return Dim  grid dimensions
     */
    Dim dim() const { return c_dim; }

    void printDebug();

    void update(const TPositionPtr* links, CellType celltype);
    void update(const Position& position, CellType celltype);
    bool hitTest(const Position& position, CellType cellType) const;

    Position randomEmptyPosition() const;

    static Position center(uint32 width, uint32 height) { return Position(width / 2 + 1, height / 2 + 1); }

private:
    const Dim c_dim;
    TArray<CellType> m_cells;
    TMap<CellType, TArray<uint32>> m_indByType = {
        {CellType::Snake, {}},  //
        {CellType::Wall, {}},   //
        {CellType::Food, {}},   //
    };

    void initWalls();
    FORCEINLINE uint32 posToIndex(uint32 x, uint32 y) const;
    FORCEINLINE uint32 posToIndex(const Position& position) const;
    FORCEINLINE Position indexToPos(uint32 index) const;

    void freeCellsByType(CellType celltype);
    void updateInternal(const Position& position, CellType celltype);
};
}  // namespace SnakeGame