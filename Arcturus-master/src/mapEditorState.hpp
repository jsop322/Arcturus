#ifndef MAPEDITORSTATE_H
#define MAPEDITORSTATE_H

#include <SFML/Graphics.hpp>
#include "gameState.hpp"
#include <iostream>

class MapEditorState : public GameState
{
public:
  MapEditorState();
  void handleEvents(GameEngine &game, sf::Event event);
  void pause();
  void resume();
  void update(GameEngine &game, float &deltaTime);
  void draw(GameEngine &game);
  void createButton(sf::Vector2f size, sf::Vector2f position);
  void createButtonSprite(sf::Vector2f size, sf::Vector2f position);
  void createTextobject(std::string content, float char_size, sf::Color color, sf::Vector2f position);
  void setSize(unsigned int width, unsigned int height);

private:
  int clicked_;
  sf::Texture buttonsource_;
  std::vector<sf::Sprite> buttons_;
  std::vector<sf::RectangleShape> colorButtons_;
  sf::RectangleShape pointer_;
  std::vector<sf::RectangleShape> layer_one_;
  std::vector<sf::RectangleShape> layer_two_;
  sf::Vector2f previousloc_;
  bool colorSelected_ = false;
  std::vector<sf::Text> texts_;
  sf::Font font_;
  sf::Vector2f mapSize_;
  sf::Image textures_;
  sf::Image features_;
  sf::RectangleShape border_;
  sf::RectangleShape canvas_;
  int state_; //Which state of map editing is currently used. 0: size selection, 1: Basic walls etc, 2: Map features, 3: Naming and saving
  sf::Color selectedColor_;
  bool stateSet_;
  std::string str_;
  sf::String text_;
};

#endif
