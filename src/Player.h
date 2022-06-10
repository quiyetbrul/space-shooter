#ifndef PLAYER_H
#define PLAYER_H

#include "Bullet.h"

class Player {
private:
  sf::Texture Player_Texture_;
  sf::Sprite Player_Sprite_;

  float Player_Speed_;

  int Hp_;
  int Hp_Max_;

  float Attack_Cooldown_;
  float Attack_Cooldown_Max_;

  void InitVariables();
  void InitTexture();
  void InitSprite();

public:
  Player();
  virtual ~Player();

  const sf::Vector2f &GetPosition() const;
  const sf::FloatRect GetBounds() const;
  const int &GetHp() const;
  const int &GetHpMax() const;

  void SetPosition(const sf::Vector2f position);
  void SetPosition(const float X, const float Y);

  void SetHp(const int hp);
  void LoseHp(const int value);

  void AttackCooldown();
  const bool IsAttackCooldown();

  void Update();
  void Render(sf::RenderTarget &target);

  void Move(const float Dir_X, const float Dir_Y);

  void UpdateAttack();
};

#endif // PLAYER_H
