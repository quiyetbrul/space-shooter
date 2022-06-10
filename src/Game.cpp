#include "Game.h"

#include <iostream>

Game::Game() {
  this->InitWindow();
  this->InitTextures();
  this->InitGUI();
  this->InitWorld();
  this->InitSystems();

  this->InitPlayer();
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
  if (!this->Textures_["BULLET"]->loadFromFile("assets/textures/bullet.png")) {
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

void Game::InitGUI() {
  if (!this->Font_.loadFromFile("assets/fonts/PixellettersFull.ttf"))
    std::cout << "ERROR::GAME::Failed to load font"
              << "\n";

  // Init point text
  this->Points_Text_.setPosition(700.f, 25.f);
  this->Points_Text_.setFont(this->Font_);
  this->Points_Text_.setCharacterSize(20);
  this->Points_Text_.setFillColor(sf::Color::White);
  this->Points_Text_.setString("test");

  this->Game_Over_Text_.setFont(this->Font_);
  this->Game_Over_Text_.setCharacterSize(60);
  this->Game_Over_Text_.setFillColor(sf::Color::Red);
  this->Game_Over_Text_.setString("Game Over!");
  this->Game_Over_Text_.setPosition(
      this->Window_->getSize().x / 2.f -
          this->Game_Over_Text_.getGlobalBounds().width / 2.f,
      this->Window_->getSize().y / 2.f -
          this->Game_Over_Text_.getGlobalBounds().height / 2.f);

  // Init player GUI
  this->Player_Hp_Bar_.setSize(sf::Vector2f(300.f, 25.f));
  this->Player_Hp_Bar_.setFillColor(sf::Color::Red);
  this->Player_Hp_Bar_.setPosition(sf::Vector2f(20.f, 20.f));

  this->Player_Hp_Bar_Back_ = this->Player_Hp_Bar_;
  this->Player_Hp_Bar_Back_.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::InitWorld() {
  if (!this->World_Bg_Texture_.loadFromFile("assets/textures/background.jpg")) {
    std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE"
              << "\n";
  }

  this->World_Bg_Sprite_.setTexture(this->World_Bg_Texture_);
}

void Game::InitSystems() {
  this->Window_->setKeyRepeatEnabled(false);
  this->Window_->setMouseCursorVisible(false);
  this->Points_ = 0;
}

void Game::Run() {
  while (this->Window_->isOpen()) {
    this->UpdatePollEvent();
    if (this->Player_->GetHp() > 0)
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

void Game::UpdateGUI() {
  std::stringstream ss;

  ss << "Points: " << this->Points_;

  this->Points_Text_.setString(ss.str());

  // Update player GUI
  float hpPercent =
      static_cast<float>(this->Player_->GetHp()) / this->Player_->GetHpMax();
  this->Player_Hp_Bar_.setSize(
      sf::Vector2f(300.f * hpPercent, this->Player_Hp_Bar_.getSize().y));
}

void Game::UpdateWorld() {
  this->World_Bg_Sprite_.setPosition(
      this->Window_->mapPixelToCoords(sf::Vector2i(0, 0)));
}

void Game::UpdateCollision() {
  // CLAMP PLAYER
  // Left world collision
  if (this->Player_->GetBounds().left < 0.f) {
    this->Player_->SetPosition(0.f, this->Player_->GetBounds().top);
  }
  // Right world collison
  else if (this->Player_->GetBounds().left + this->Player_->GetBounds().width >=
           this->Window_->getSize().x) {
    this->Player_->SetPosition(this->Window_->getSize().x -
                                   this->Player_->GetBounds().width,
                               this->Player_->GetBounds().top);
  }
  // Top world collision
  if (this->Player_->GetBounds().top < 0.f) {
    this->Player_->SetPosition(this->Player_->GetBounds().left, 0.f);
  }
  // Bottom world collision
  else if (this->Player_->GetBounds().top + this->Player_->GetBounds().height >=
           this->Window_->getSize().y) {
    this->Player_->SetPosition(this->Player_->GetBounds().left,
                               this->Window_->getSize().y -
                                   this->Player_->GetBounds().height);
  }
  // CLAMP PLAYER
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
      this->Player_->LoseHp(Enemy->GetDamage());
    }
    ++position;
  }
}

void Game::UpdateCombat() {
  for (int i = 0; i < this->Enemies_.size(); ++i) {
    bool enemy_deleted = false;
    for (size_t k = 0; k < this->Bullets_.size() && enemy_deleted == false;
         k++) {
      if (this->Enemies_[i]->GetBounds().intersects(
              this->Bullets_[k]->GetBounds())) {
        this->Points_ += this->Enemies_[i]->GetPoints();

        delete this->Enemies_[i];
        this->Enemies_.erase(this->Enemies_.begin() + i);

        delete this->Bullets_[k];
        this->Bullets_.erase(this->Bullets_.begin() + k);

        enemy_deleted = true;
      }
    }
  }
}

void Game::Update() {
  this->UpdateInput();

  this->Player_->Update();

  this->UpdateCollision();

  this->UpdateBullet();

  this->UpdateEnemy();

  this->UpdateCombat();

  this->UpdateGUI();

  this->UpdateWorld();
}

void Game::RenderGUI() {
  this->Window_->draw(this->Points_Text_);
  this->Window_->draw(this->Player_Hp_Bar_Back_);
  this->Window_->draw(this->Player_Hp_Bar_);
}

void Game::RenderWorld() { this->Window_->draw(this->World_Bg_Sprite_); }

void Game::Render() {
  this->Window_->clear();

  // Draw world
  this->RenderWorld();

  // Draw all the stuffs
  this->Player_->Render(*this->Window_);

  for (auto *bullet : this->Bullets_) {
    bullet->Render(this->Window_);
  }

  for (auto *enemy : this->Enemies_) {
    enemy->Render(this->Window_);
  }

  this->RenderGUI();

  // Game over screen
  if (this->Player_->GetHp() <= 0)
    this->Window_->draw(this->Game_Over_Text_);

  this->Window_->display();
}
