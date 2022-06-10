#include "Enemy.h"

Enemy::Enemy(float Pos_x, float Pos_Y) {
  this->InitVariables();
  this->InitShape();
  this->Enemy_Shape_.setPosition(Pos_x, Pos_Y);
}

Enemy::~Enemy() {}

void Enemy::InitShape() {
  this->Enemy_Shape_.setRadius(this->Point_Count_ * 5);
  this->Enemy_Shape_.setPointCount(this->Point_Count_);
  this->Enemy_Shape_.setFillColor(
      sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::InitVariables() {
  this->Type_ = 0;
  this->Point_Count_ = rand() % 8 + 3; // min = 3 max = 10
  this->Enemy_Speed_ = static_cast<float>(this->Point_Count_ / 3.0);
  this->Hp_ = this->Hp_Max_;
  this->Hp_Max_ = static_cast<int>(this->Point_Count_);
  this->Damage_ = this->Point_Count_;
  this->Points_ = this->Point_Count_;
}

const sf::FloatRect Enemy::GetBounds() const {
  return this->Enemy_Shape_.getGlobalBounds();
}

const int &Enemy::GetPoints() const { return this->Points_; }

void Enemy::SetDamage() { this->Damage_ = this->Point_Count_; }
const int &Enemy::GetDamage() const { return this->Damage_; }

void Enemy::Update() { this->Enemy_Shape_.move(0.f, this->Enemy_Speed_); }

void Enemy::Render(sf::RenderTarget *Target) {
  Target->draw(this->Enemy_Shape_);
}
