#include "Player.h"

#include <iostream>

Player::Player() {
  this->InitVariables();
  this->InitTexture();
  this->InitSprite();
}

Player::~Player() {}

const sf::Vector2f &Player::GetPosition() const {
  return this->Player_Sprite_.getPosition();
}

const sf::FloatRect Player::GetBounds() const {
  return this->Player_Sprite_.getGlobalBounds();
}

const int &Player::GetHp() const { return this->Hp_; }

const int &Player::GetHpMax() const { return this->Hp_Max_; }

void Player::AttackCooldown() {
  if (this->Attack_Cooldown_ < this->Attack_Cooldown_Max_) {
    this->Attack_Cooldown_ += 0.5f;
  }
}

void Player::SetPosition(const sf::Vector2f position) {
  this->Player_Sprite_.setPosition(position);
}

void Player::SetPosition(const float X, const float Y) {
  this->Player_Sprite_.setPosition(X, Y);
}

void Player::SetHp(const int Hp) { this->Hp_ = Hp; }

void Player::LoseHp(const int Value) {
  this->Hp_ -= Value;
  if (this->Hp_ < 0) {
    this->Hp_ = 0;
  }
}

const bool Player::IsAttackCooldown() {
  if (this->Attack_Cooldown_ >= this->Attack_Cooldown_Max_) {
    this->Attack_Cooldown_ = 0.f;
    return true;
  }
  return false;
}

void Player::InitVariables() {
  this->Player_Speed_ = 10.0f;
  this->Attack_Cooldown_Max_ = 10.f;
  this->Attack_Cooldown_ = this->Attack_Cooldown_Max_;
  this->Hp_Max_ = 100;
  this->Hp_ = this->Hp_Max_;
}

void Player::InitTexture() {
  if (!this->Player_Texture_.loadFromFile("assets/textures/ship.png")) {
    std::cerr << "ERROR::PLAYER::INITTEXTURE:: failed to load ship.png"
              << std::endl;
  }
}

void Player::InitSprite() {
  this->Player_Sprite_.setTexture(this->Player_Texture_);
  this->Player_Sprite_.scale(0.1f, 0.1f);
}

void Player::Update() { this->AttackCooldown(); }

void Player::UpdateAttack() {
  if(this->IsAttackCooldown() < this->Attack_Cooldown_Max_) {
    this->Attack_Cooldown_ += 0.5f;
  }
}

void Player::Render(sf::RenderTarget &target) {
  target.draw(this->Player_Sprite_);
}

void Player::Move(const float Dir_X, const float Dir_Y) {
  this->Player_Sprite_.move(this->Player_Speed_ * Dir_X,
                            this->Player_Speed_ * Dir_Y);
}
