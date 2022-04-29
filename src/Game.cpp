#include "Game.h"

#include <iostream>

Game::Game() {
  this->InitWindow();
  this->InitPlayer();
  this->InitTextures();
  this->InitEnemy();
}

Game::~Game() {
  delete this->Window_;
  delete this->Player_;
  for (auto &Texture : this->Textures_) {
    delete Texture.second;
  }
  for (auto *Bullet : this->Bullets_) {
    delete Bullet;
  }
  for (auto *Enemy : this->Enemies_) {
    delete Enemy;
  }
}

void Game::InitPlayer() { this->Player_ = new Player(); }

void Game::InitEnemy() {
  this->Spawn_Timer_Max_ = 50.f;
  this->Spawn_Timer_ = this->Spawn_Timer_Max_;
}

void Game::InitTextures() {
  this->Textures_["BULLET"] = new sf::Texture();
  if (!this->Textures_["BULLET"]->loadFromFile("textures/bullet.png")) {
    std::cerr << "ERROR::PLAYER::INITTEXTURE:: failed to load ship.png"
              << std::endl;
  }
}

void Game::InitWindow() {
  this->Window_ = new sf::RenderWindow(
      sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Shooter",
      sf::Style::Titlebar | sf::Style::Close);
  this->Window_->setFramerateLimit(60); // framerate dependent on CPU speed
  this->Window_->setVerticalSyncEnabled(false);
}

void Game::Run() {
  while (this->Window_->isOpen()) {
    this->Update();
    this->Render();
  }
}

void Game::UpdatePollEvent() {
  sf::Event event;
  while (this->Window_->pollEvent(event)) {
    if (event.Event::type == sf::Event::Closed ||
        (event.Event::KeyPressed &&
         event.Event::key.code == sf::Keyboard::Escape)) {
      this->Window_->close();
    }
  }
}

void Game::UpdateInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    this->Player_->Move(-1.0f, 0.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    this->Player_->Move(1.0f, 0.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    this->Player_->Move(0.0f, -1.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    this->Player_->Move(0.0f, 1.0f);
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
      this->Player_->IsAttackCooldown()) {
    this->Bullets_.push_back(new Bullet(
        this->Textures_["BULLET"],
        this->Player_->GetPosition().x + this->Player_->GetBounds().width / 2.f,
        this->Player_->GetPosition().y, 0.f, -1.f, 5.f));
  }
}

void Game::UpdateBullet() {
  unsigned position = 0;
  for (auto *Bullet : this->Bullets_) {
    Bullet->Update();

    if (Bullet->GetBounds().top + Bullet->GetBounds().height < 0.f) {
      delete this->Bullets_.at(position);
      this->Bullets_.erase(this->Bullets_.begin() + position);
      --position;
    }
    ++position;
  }
}

void Game::UpdateEnemy() {
  this->Spawn_Timer_ += 0.5f;
  if (this->Spawn_Timer_ >= this->Spawn_Timer_Max_) {
    this->Enemies_.push_back(new Enemy(rand() % SCREEN_WIDTH, 0.f));
    this->Spawn_Timer_ = 0.f;
  }
  unsigned position = 0;
  for (auto *Enemy : this->Enemies_) {
    Enemy->Update();

    if (Enemy->GetBounds().top > SCREEN_HEIGHT ||
        Enemy->GetBounds().intersects(this->Player_->GetBounds())) {
      delete this->Enemies_.at(position);
      this->Enemies_.erase(this->Enemies_.begin() + position);
    }
    ++position;
  }
}

void Game::Update() {
  this->UpdatePollEvent();
  this->UpdateInput();
  this->Player_->Update();
  this->UpdateBullet();
  this->UpdateEnemy();
}

void Game::Render() {
  this->Window_->clear();

  this->Player_->Render(*this->Window_);

  for (auto *Bullet : this->Bullets_) {
    Bullet->Render(this->Window_);
  }

  for (auto *Enemy : this->Enemies_) {
    Enemy->Render(this->Window_);
  }

  this->Window_->display();
}
