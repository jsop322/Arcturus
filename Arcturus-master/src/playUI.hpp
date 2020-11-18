#ifndef PLAYUI_H
#define PLAYUI_H
#include "gameEngine.hpp"
#include "unit.hpp"
#include "building.hpp"

enum eventType
{
  emptyEvent,
  deleteUnit,
  deleteBuilding,
  attack,
  produceUnit,
  levelUp,
  buildBarracks,
  buildFactory,
  buildResourcebuilding,
};
enum UIType
{
  blankUI,
  soldierUI,
  workerUI,
  buildingUI,
  mechanicalUI,
};

class PlayUI {
public:
  PlayUI();
  void createButtonSprite(sf::Vector2f size, sf::IntRect textureCrop);
  void createTextobject(std::string content, float char_size, sf::Color color, sf::Vector2f position);
  eventType handleEvents(GameEngine &game, sf::Event event);
  void draw(GameEngine &game, std::pair<int,int> resources);
  void draw(GameEngine &game, std::vector<Unit*> selectedUnits, std::pair<int,int> resources);
  void draw(GameEngine &game, std::vector<Building*> selectedBuilding, std::pair<int,int> resources);
  void workerUnitUI(GameEngine &game, float workingTime, float currentTime, int maxHealth, int currentHealth, bool gathering);
  void soldierUnitUI(GameEngine &game, unsigned int damage, int maxHealth, int currentHealth);
  void mechanicalUnitUI(GameEngine &game, unsigned int damage, int maxHealth, int currentHealth);
  void drawHealthbar(GameEngine &game, int maxHealth, int currentHealth, sf::Vector2f position);
  void drawProgressBar(GameEngine &game, float max, float current, sf::Vector2f position);
  void drawResourceAmount(GameEngine &game, int gold, int silver);

private:
  sf::Texture buttonsource_;
  std::vector<sf::Sprite> buttons_;
  std::vector<sf::Text> texts_;
  sf::Sprite gold_;
  sf::Sprite silver_;
  sf::Font font_;
  std::vector<float> geometry_;
  sf::Texture background_;
  UIType currentUI_;
};

#endif
