#ifndef ENEMY_H
#define ENEMY_H

#include "include/SFML/Graphics.hpp"

class Enemy {
private:
  sf::CircleShape Enemy_Shape_;

  unsigned Point_Count_;

  int Type_;
  int Hp_;
  int Hp_Max_;
  int Damage_;
  int Points_;
  float Enemy_Speed_;

  void InitShape();
  void InitVariables();

public:
  Enemy(float Pos_x, float Pos_Y);
  virtual ~Enemy();

  const sf::FloatRect GetBounds() const;
  const int &GetPoints() const;

  void SetDamage();
  const int &GetDamage() const;

  void Update();
  void Render(sf::RenderTarget *Target);
};
#endif // ENEMY_H
