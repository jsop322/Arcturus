#ifndef MAINMENUUI_H
#define MAINMENUUI_H

#include "gameEngine.hpp"
#include "playState.hpp"
#include "mapEditorState.hpp"

class MainMenuUI{
public:
  MainMenuUI();
  void createButtonSprite(sf::Vector2f size, sf::Vector2f position);
  void createTextobject(std::string content, float char_size, sf::Color color, sf::Vector2f position);
  int handleEvents(GameEngine &game, sf::Event event);
  void draw(GameEngine &game);
  void selectMap(GameEngine &game);
private:

  sf::Texture buttonsource_;
  std::vector<sf::Sprite> buttons_;
  std::vector<sf::Text> texts_;
  sf::Font font_;
  std::vector<float> geometry_;
  sf::Texture background_;
  int clicked_ = 10;
  bool mapselect_ = false;
};

#endif
