#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 1024

class Game {
private:
  sf::RenderWindow *Window_;

  std::map<std::string, sf::Texture *> Textures_;
  std::vector<Bullet *> Bullets_;

  Player *Player_;

  std::vector<Enemy *> Enemies_;
  float Spawn_Timer_;
  float Spawn_Timer_Max_;

  void InitPlayer();
  void InitEnemy();

  void InitTextures();
  void InitWindow();

public:
  Game();
  virtual ~Game();

  void Run();
  void UpdatePollEvent();
  void UpdateInput();
  void UpdateBullet();
  void UpdateEnemy();
  void Update();
  void Render();
}; // class Game

#endif // GAME_H
