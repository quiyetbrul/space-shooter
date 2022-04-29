#include "Game.h"

#include <time.h>

int main() {
  srand(time_t(static_cast<unsigned>(0)));

  Game Game;

  Game.Run();

  return 0;
}
