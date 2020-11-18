#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "resourceManager.hpp"

class GameState;

class GameEngine
{
public:
  GameEngine();
  void changeState(std::shared_ptr<GameState> state);
  void nextState(std::shared_ptr<GameState> state);
  void previousState();

  void handleEvents();
  void update(float &deltaTime);
  void draw();
  int getStateCount(){ return states_.size(); }
  bool isRunning() const { return running_; }
  void quit() { running_ = false; }
  void setMusicFalse() { musicChanged_ = false; }
  bool changeMusic() { return musicChanged_; }

  sf::RenderWindow* getWindow(){return &window_;}
  sf::View* getView(){return &defaultView_;}
  ResourceManager* getResourceManager() {return &resourceManager;}
  std::vector<std::string> mapNames_;

private:

  sf::Vector2i resolution_;
  bool running_;
  bool musicChanged_;
  std::vector<std::shared_ptr<GameState>> states_;
  int tileDimension_;
  int xTiles_;
  int yTiles_;
  sf::RenderWindow window_;
  sf::View defaultView_;
  ResourceManager resourceManager;


};

#endif
