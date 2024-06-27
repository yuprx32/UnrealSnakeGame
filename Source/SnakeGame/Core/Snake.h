// SnakeGame project

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
class Snake
{
public:
    Snake(const Settings::Snake& settings);

    const TSnakeList& links() const { return m_links; }
    Position head() const { return m_links.GetHead()->GetValue(); }

    void move(const Input& input);
    void increase();

private:
    TSnakeList m_links;
    Input m_lastInput{Input::Default};
};
}  // namespace SnakeGame