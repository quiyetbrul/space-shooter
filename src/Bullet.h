#ifndef BULLET_H
#define BULLET_H

#include "include/SFML/Graphics.hpp"
#include "include/SFML/System.hpp"

class Bullet {
private:
  sf::Sprite Bullet_Sprite_;

  sf::Vector2f Direction_;
  float Bullet_Speed_;

public:
  Bullet();
  Bullet(sf::Texture *Texture, float Pos_x, float Pos_Y, float Dir_X,
         float Dir_Y, float Movement_speed);
  virtual ~Bullet();

  const sf::FloatRect GetBounds() const;

  void Update();
  void Render(sf::RenderTarget *Target);
};

#endif // BULLET_H
