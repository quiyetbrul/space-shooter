#ifndef GAME_H
#define GAME_H

#include <map>
#include <sstream>
#include <string>
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

  sf::Font Font_;
  sf::Text Points_Text_;
  sf::Text Game_Over_Text_;

  sf::Texture World_Bg_Texture_;
  sf::Sprite World_Bg_Sprite_;

  unsigned Points_;

  sf::RectangleShape Player_Hp_Bar_;
  sf::RectangleShape Player_Hp_Bar_Back_;

  Player *Player_;

  std::vector<Enemy *> Enemies_;
  float Spawn_Timer_;
  float Spawn_Timer_Max_;

  void InitPlayer();
  void InitEnemy();

  void InitTextures();
  void InitWindow();
  void InitWorld();
  void InitGUI();
  void InitSystems();

public:
  Game();
  virtual ~Game();

  void Run();
  void UpdatePollEvent();
  void UpdateInput();
  void UpdateGUI();
  void UpdateWorld();
  void UpdateCollision();
  void UpdateBullet();
  void UpdateEnemy();
  void UpdateCombat();
  void Update();

  void RenderGUI();
  void RenderWorld();
  void Render();
}; // class Game

#endif // GAME_H
