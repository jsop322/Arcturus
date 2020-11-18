#include "gameEngine.hpp"
#include "gameState.hpp"
#include "mainMenuState.hpp"
#include "playState.hpp"

GameEngine::GameEngine ()
{
  running_ = true;
  tileDimension_ = 32;
  xTiles_ = 25;
  yTiles_ = 25;
  resolution_.x = xTiles_ * tileDimension_;
  resolution_.y = yTiles_ * tileDimension_;
  musicChanged_ = false;
  window_.create(sf::VideoMode(resolution_.x, resolution_.y), "Arcturus", sf::Style::Close);
  //defaultView_.setSize(sf::Vector2f(800.f, 800.f));
  //defaultView_.setCenter(sf::Vector2f(400.f, 400.f));
  defaultView_.reset(sf::FloatRect(1.f, 1.f, 800.f, 800.f));
  window_.setView(defaultView_);
  mapNames_.push_back("50 exampleMap");       //TODO: Figure out where these should come, if not hardcoded. Maybe once new map is added the name is added here?
  mapNames_.push_back("25 exampleMap");
  //Makes sure that the states vector is empty
  states_.clear();
  //Game engine will be initialized on start up so first state will be menu. If we want we can add splashscreen or intro later.
  nextState(std::make_shared<MainMenuState>());
}

/*
** Swaps the current state to another. NOTE: Has not been tested yet, so might not work!
*/
void GameEngine::changeState(std::shared_ptr<GameState> state)
{
  states_.pop_back();
  states_.push_back(state);
  defaultView_.reset(sf::FloatRect(1.f, 1.f, 800.f, 800.f));
}

/*
** Moves forward to a next game state.
** Example: from playState to pauseState.
*/
void GameEngine::nextState(std::shared_ptr<GameState> state)
{
  states_.push_back(state);
  //defaultView_.setSize(sf::Vector2f(800.f, 800.f));
  defaultView_.reset(sf::FloatRect(1.f, 1.f, 800.f, 800.f));
  musicChanged_ = true;
}

/*
** Goes back one game state.
** Example: The game is in pause menu. When player clicks resume the state goes back to playState.
*/
void GameEngine::previousState()
{
  states_.pop_back();
  defaultView_.reset(sf::FloatRect(1.f, 1.f, 800.f, 800.f));
  musicChanged_ = true;
}

/*
** Checks for user input. Sends the input info to current game state for handling.
*/
void GameEngine::handleEvents()
{
  sf::Event event;
  while (window_.pollEvent(event))
  {
      states_.back()->handleEvents(*this, event);
  }
}

/*
** Updates game logic/state/map? TODO: Write description for update function
*/
void GameEngine::update(float &deltaTime)
{
  states_.back()->update(*this, deltaTime);
}

/*
** Calls the current game state's draw function.
*/
void GameEngine::draw()
{
  window_.setView(defaultView_);
  states_.back()->draw(*this);
}
