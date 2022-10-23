#ifndef SNAKE_SETTINGS_HPP_INCLUDE
#define SNAKE_SETTINGS_HPP_INCLUDE

namespace SnakeGame
{
    constexpr std::size_t kFramesPerSecond{60U};
    constexpr std::size_t kMsPerFrame{1000U / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640U};
    constexpr std::size_t kScreenHeight{640U};
    constexpr std::size_t kGridWidth{32U};
    constexpr std::size_t kGridHeight{32U};

  enum class Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight,
    kQuit
  };

  enum class KeyStroke {
    none,
    keyUp,
    keyDown,
    keyLeft,
    keyRight,
    keyQuit
  };
  
struct Message {
    SnakeGame::KeyStroke pressedKey_;
};  
  

}

#endif