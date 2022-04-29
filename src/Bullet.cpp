#include "Bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(sf::Texture *Texture, float Pos_x, float Pos_Y, float Dir_X,
               float Dir_Y, float Bullet_Speed_) {
  this->Bullet_Sprite_.setTexture(*Texture);
  this->Bullet_Sprite_.setPosition(Pos_x, Pos_Y);
  this->Direction_.x = Dir_X;
  this->Direction_.y = Dir_Y;
  this->Bullet_Speed_ = Bullet_Speed_;
}

Bullet::~Bullet() {}

const sf::FloatRect Bullet::GetBounds() const {
  return this->Bullet_Sprite_.getGlobalBounds();
}

void Bullet::Update() {
  this->Bullet_Sprite_.move(this->Direction_ * this->Bullet_Speed_);
}

void Bullet::Render(sf::RenderTarget *Target) {
  Target->draw(this->Bullet_Sprite_);
}
