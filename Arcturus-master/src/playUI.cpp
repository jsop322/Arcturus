#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "playUI.hpp"

/*
Constructor for class object. Creates the desired shape objects (buttons) and stores them in shapes_ vector.
Also creates required text objects and font objects.
*/
PlayUI::PlayUI()
{
  sf::Font font;                                                            // Load and assign the font for the UI.
  if (!font.loadFromFile("resources/fonts/Mylodon-Light.otf")){
    std::cout << "Unable to load font" << std::endl;
  }
  font_ = font;
  sf::Texture buttonsource;                                                      // Load and assign the buttonsource texture for the UI.
  if (!buttonsource.loadFromFile("resources/graphics/Buttons.png")){
    std::cout << "Unable to load button texture" << std::endl;
  }
  buttonsource_ = buttonsource;
  sf::Texture background;
  if (!background.loadFromFile("resources/graphics/PlayUI.png")){             //Loads the background for UI
    std::cout << "Unable to load background texture" << std::endl;
  }
  background_ = background;
  std::vector<float> geometry = {50, 50, 15, 15, 656, 600};   // Geometry definition: button width, button height, offset, character size, positions x and y
  geometry_ = geometry;

  for(int i = 1; i < 9; i++){
    createButtonSprite(sf::Vector2f(geometry_[0], geometry_[1]), sf::IntRect(i*50, 1*50, 50, 50));  //Create all 7 buttons, without positions
  }
  //The buttons are stored in vector so that even indexes are button backgrounds and odd indexes are button images. The order is the same as in the buttonsource texture.

  createTextobject("", 14, sf::Color::Black, sf::Vector2f(0, 0));                                      // Create "empty" text objects for UI
  createTextobject("", 14, sf::Color::Black, sf::Vector2f(0, 0));
  createTextobject("", 12, sf::Color::White, sf::Vector2f(37, 14));
  createTextobject("", 12, sf::Color::White, sf::Vector2f(102, 14));
  createTextobject("", 14, sf::Color::Black, sf::Vector2f(0, 0));
  currentUI_ = blankUI;
  gold_.setTexture(buttonsource_);
  gold_.setTextureRect(sf::IntRect(60, 210, 30, 20));
  gold_.setPosition(sf::Vector2f(5, 11));
  silver_.setTexture(buttonsource_);
  silver_.setTextureRect(sf::IntRect(60+50, 210, 30, 20));
  silver_.setPosition(sf::Vector2f(70, 11));

}
/*
This function creates a button to buttons_ vector from the given inputs, using the texture in buttonsource_
*/
void PlayUI::createButtonSprite(sf::Vector2f size, sf::IntRect textureCrop)
{
  sf::Sprite emptyButton;                                         //Sprite for the button background
  sf::Sprite buttonImage;                                         //Sprite for button functionality image
  emptyButton.setTexture(buttonsource_);
  buttonImage.setTexture(buttonsource_);
  emptyButton.setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));    //Button background crop from texture is hardcoded here as it is same in all the buttons
  buttonImage.setTextureRect(textureCrop);
  buttons_.push_back(emptyButton);
  buttons_.push_back(buttonImage);
}
/*
This function creates a text object in texts_ vector using the given inputs
*/
void PlayUI::createTextobject(std::string content, float char_size, sf::Color color, sf::Vector2f position)
{
  sf::Text text;
  text.setFont(font_);
  text.setString(content);
  text.setCharacterSize(char_size);
  text.setColor(color);
  text.setPosition(position);
  texts_.push_back(text);
}
/*
Handles the different events
*/
eventType PlayUI::handleEvents(GameEngine &game, sf::Event event)
{
  if(currentUI_ == blankUI){
    return emptyEvent;
  }
  else if(currentUI_ == soldierUI){
    if (event.type == sf::Event::MouseButtonPressed){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (buttons_[6].getGlobalBounds().contains(location)){                   //Mousebutton pressed on first button, these are just to make UI more intuitive
          buttons_[6].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[6].setColor(sf::Color(128,128,128));
        }
        else if (buttons_[4].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[4].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[4].setColor(sf::Color(128,128,128));
        }
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (buttons_[6].getGlobalBounds().contains(location)){                   //Mousebutton released on first button
          buttons_[6].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[6].setColor(sf::Color(255,255,255));
          // Attack button
          return attack;
        }
        else if (buttons_[4].getGlobalBounds().contains(location)){              //Mousebutton released on second button
          buttons_[4].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[4].setColor(sf::Color(255,255,255));
          // Selfdestruct button
          return deleteUnit;
        }
        else{                                                                   //Mousebutton released somewhere else
        buttons_[6].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
        buttons_[4].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
        buttons_[6].setColor(sf::Color(255,255,255));
        buttons_[4].setColor(sf::Color(255,255,255));
        }
      }
    }
    else if (event.type == sf::Event::MouseMoved){
      sf::Vector2f location(event.mouseMove.x, event.mouseMove.y);
      if (buttons_[4].getGlobalBounds().contains(location)){                     //Mouse hovered on first button, these are just to make the UI more intuitive
        buttons_[4].setColor(sf::Color(128,128,128));
      }
      else if (buttons_[6].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        buttons_[6].setColor(sf::Color(128,128,128));
      }
      else {
        buttons_[6].setColor(sf::Color(255,255,255));
        buttons_[4].setColor(sf::Color(255,255,255));
      }
    }
    return emptyEvent;
  }
  else if(currentUI_ == workerUI){
    if (event.type == sf::Event::MouseButtonPressed){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (buttons_[0].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[0].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[0].setColor(sf::Color(128,128,128));
        }
        if (buttons_[4].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[4].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[4].setColor(sf::Color(128,128,128));
        }
        if (buttons_[10].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[10].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[10].setColor(sf::Color(128,128,128));
        }
        if (buttons_[14].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[14].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[14].setColor(sf::Color(128,128,128));
        }
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (buttons_[0].getGlobalBounds().contains(location)){              //Mousebutton released on second button
          buttons_[0].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[0].setColor(sf::Color(255,255,255));
          // Build factory button
          return buildFactory;
        }
        if (buttons_[4].getGlobalBounds().contains(location)){              //Mousebutton released on second button
          buttons_[4].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[4].setColor(sf::Color(255,255,255));
          // Selfdestruct button
          return deleteUnit;
        }
        if (buttons_[10].getGlobalBounds().contains(location)){              //Mousebutton released on second button
          buttons_[10].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[10].setColor(sf::Color(255,255,255));
          // Build barracks button
          return buildBarracks;
        }
        if (buttons_[14].getGlobalBounds().contains(location)){              //Mousebutton released on second button
          buttons_[14].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[14].setColor(sf::Color(255,255,255));
          // Build barracks button
          return buildResourcebuilding;
        }
        else{                                                                   //Mousebutton released somewhere else
          buttons_[0].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[0].setColor(sf::Color(255,255,255));
          buttons_[4].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[4].setColor(sf::Color(255,255,255));
          buttons_[10].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[10].setColor(sf::Color(255,255,255));
          buttons_[14].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[14].setColor(sf::Color(255,255,255));
        }
      }
    }
    else if (event.type == sf::Event::MouseMoved){
      sf::Vector2f location(event.mouseMove.x, event.mouseMove.y);
      if (buttons_[4].getGlobalBounds().contains(location)){                     //Mouse hovered on first button, these are just to make the UI more intuitive
        buttons_[4].setColor(sf::Color(128,128,128));
      }
      else if (buttons_[1].getGlobalBounds().contains(location)){                     //Mouse hovered on first button, these are just to make the UI more intuitive
        buttons_[0].setColor(sf::Color(128,128,128));
      }
      else if (buttons_[10].getGlobalBounds().contains(location)){                     //Mouse hovered on first button, these are just to make the UI more intuitive
        buttons_[10].setColor(sf::Color(128,128,128));
      }
      else if (buttons_[14].getGlobalBounds().contains(location)){                     //Mouse hovered on first button, these are just to make the UI more intuitive
        buttons_[14].setColor(sf::Color(128,128,128));
      }
      else {
        buttons_[0].setColor(sf::Color(255,255,255));
        buttons_[4].setColor(sf::Color(255,255,255));
        buttons_[10].setColor(sf::Color(255,255,255));
        buttons_[14].setColor(sf::Color(255,255,255));
      }
    }
    return emptyEvent;
  }
  else if(currentUI_ == buildingUI){
    if (event.type == sf::Event::MouseButtonPressed){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (buttons_[4].getGlobalBounds().contains(location)){                   //Mousebutton pressed on first button, these are just to make UI more intuitive
          buttons_[4].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[4].setColor(sf::Color(128,128,128));
        }
        else if (buttons_[2].getGlobalBounds().contains(location)){                   //Mousebutton pressed on first button, these are just to make UI more intuitive
          buttons_[2].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[2].setColor(sf::Color(128,128,128));
        }
        else if (buttons_[8].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[8].setTextureRect(sf::IntRect(5*50, 3*50, 50, 50));
          buttons_[8].setColor(sf::Color(128,128,128));
        }
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (buttons_[4].getGlobalBounds().contains(location)){                   //Mousebutton released on first button
          buttons_[4].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[4].setColor(sf::Color(255,255,255));
          // Self destruct button
          return deleteBuilding;
        }
        else if (buttons_[2].getGlobalBounds().contains(location)){                   //Mousebutton released on first button
          buttons_[2].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[2].setColor(sf::Color(255,255,255));
          // Attack button
          return levelUp;
        }
        else if (buttons_[8].getGlobalBounds().contains(location)){              //Mousebutton released on second button
          buttons_[8].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[8].setColor(sf::Color(255,255,255));
          // Selfdestruct button
          return produceUnit;
        }
        else{                                                                   //Mousebutton released somewhere else
          buttons_[4].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[2].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[8].setTextureRect(sf::IntRect(5*50, 2*50, 50, 50));
          buttons_[4].setColor(sf::Color(255,255,255));
          buttons_[2].setColor(sf::Color(255,255,255));
          buttons_[8].setColor(sf::Color(255,255,255));
        }
      }
    }
    else if (event.type == sf::Event::MouseMoved){
      sf::Vector2f location(event.mouseMove.x, event.mouseMove.y);
      if (buttons_[4].getGlobalBounds().contains(location)){                     //Mouse hovered on first button, these are just to make the UI more intuitive
        buttons_[4].setColor(sf::Color(128,128,128));
      }
      else if (buttons_[2].getGlobalBounds().contains(location)){                     //Mouse hovered on first button, these are just to make the UI more intuitive
        buttons_[2].setColor(sf::Color(128,128,128));
      }
      else if (buttons_[8].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        buttons_[8].setColor(sf::Color(128,128,128));
      }
      else {
        buttons_[4].setColor(sf::Color(255,255,255));
        buttons_[2].setColor(sf::Color(255,255,255));
        buttons_[8].setColor(sf::Color(255,255,255));
      }
    }
    return emptyEvent;
  }
  return emptyEvent;
}
/*
Draw function once no unit is selected
*/
void PlayUI::draw(GameEngine &game, std::pair<int,int> resources){
  sf::Sprite background;
  background.setTexture(background_);
  background.setPosition(sf::Vector2f(1, 1));
  game.getWindow()->draw(background);
  drawResourceAmount(game, resources.first, resources.second);
  game.getWindow()->draw(texts_[2]);
  game.getWindow()->draw(texts_[3]);
  game.getWindow()->draw(gold_);
  game.getWindow()->draw(silver_);
  buttons_[4].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  buttons_[5].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  game.getWindow()->draw(buttons_[4]);
  game.getWindow()->draw(buttons_[5]);
  currentUI_ = blankUI;
}
/*
This draw function is used when unit selected
*/
void PlayUI::draw(GameEngine &game, std::vector<Unit*> selectedUnits, std::pair<int,int> resources)
{
  sf::Sprite background;
  background.setTexture(background_);
  background.setPosition(sf::Vector2f(1, 1));
  game.getWindow()->draw(background);
  drawResourceAmount(game, resources.first, resources.second);         // TODO: These resource amounts should come from player?
  if(selectedUnits.size() == 1){
    switch(selectedUnits[0]->getType())
    {
      case Soldier:   soldierUnitUI(game, selectedUnits[0]->getDamage(), selectedUnits[0]->getMaxHealth(), selectedUnits[0]->getCurrentHealth());
                      break;

      case Tank:      mechanicalUnitUI(game, selectedUnits[0]->getDamage(), selectedUnits[0]->getMaxHealth(), selectedUnits[0]->getCurrentHealth());
                      break;

      case Flying:    break;

      case Worker:    workerUnitUI(game, selectedUnits[0]->getWorkingTime(), selectedUnits[0]->getCurrentTime(), selectedUnits[0]->getMaxHealth(), selectedUnits[0]->getCurrentHealth(), selectedUnits[0]->gathering());
                      break;
    }
  }
  else{
  }
}

/*
Draw function to be used when building is selected.
*/
void PlayUI::draw(GameEngine &game, std::vector<Building*> selectedBuilding, std::pair<int,int> resources)
{
  sf::Sprite background;
  background.setTexture(background_);
  background.setPosition(sf::Vector2f(1, 1));
  game.getWindow()->draw(background);
  drawResourceAmount(game, resources.first, resources.second);
  drawHealthbar(game, 100, 100*(selectedBuilding[0]->getCurrentHealth()/selectedBuilding[0]->getMaxHealth()), sf::Vector2f(400, 630));
  if(selectedBuilding[0]->isProducing()){
    drawProgressBar(game, selectedBuilding[0]->getProduceTime(), selectedBuilding[0]->getCurrentTime(), sf::Vector2f(400, 683));
  }
  texts_[0].setString("Working time:");
  texts_[4].setString("Level: " + std::to_string(selectedBuilding[0]->getLevel()));
  texts_[1].setString("Health: " + std::to_string(static_cast<int>(selectedBuilding[0]->getCurrentHealth())) + "/" + std::to_string(static_cast<int>(selectedBuilding[0]->getMaxHealth())));
  texts_[0].setPosition(sf::Vector2f(408, 657));
  texts_[1].setPosition(sf::Vector2f(408, 604));
  texts_[4].setPosition(sf::Vector2f(408, 710));
  game.getWindow()->draw(texts_[0]);
  game.getWindow()->draw(texts_[1]);
  game.getWindow()->draw(texts_[4]);
  buttons_[2].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  buttons_[3].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  buttons_[4].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  buttons_[5].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  game.getWindow()->draw(buttons_[2]);
  game.getWindow()->draw(buttons_[3]);
  buttons_[8].setPosition(sf::Vector2f(geometry_[4] + geometry_[0] + geometry_[2], geometry_[5]));
  buttons_[9].setPosition(sf::Vector2f(geometry_[4] + geometry_[0] + geometry_[2], geometry_[5]));
  game.getWindow()->draw(buttons_[8]);
  game.getWindow()->draw(buttons_[9]);
  game.getWindow()->draw(buttons_[4]);
  game.getWindow()->draw(buttons_[5]);
  currentUI_ = buildingUI;
}
/*
Function to draw required buttons and information to UI for soldierUnit
*/
void PlayUI::workerUnitUI(GameEngine &game, float workingTime, float currentTime, int maxHealth, int currentHealth, bool gathering)
{
  buttons_[0].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5]));
  buttons_[1].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5]));
  buttons_[4].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  buttons_[5].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  buttons_[10].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  buttons_[11].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  buttons_[14].setPosition(sf::Vector2f(geometry_[4], geometry_[5] + geometry_[0]+ geometry_[2]));
  buttons_[15].setPosition(sf::Vector2f(geometry_[4], geometry_[5] + geometry_[0]+ geometry_[2]));
  game.getWindow()->draw(buttons_[0]);
  game.getWindow()->draw(buttons_[1]);
  game.getWindow()->draw(buttons_[4]);
  game.getWindow()->draw(buttons_[5]);
  game.getWindow()->draw(buttons_[10]);
  game.getWindow()->draw(buttons_[11]);
  game.getWindow()->draw(buttons_[14]);
  game.getWindow()->draw(buttons_[15]);
  drawHealthbar(game, maxHealth, currentHealth, sf::Vector2f(400, 630));
  if(gathering){
    drawProgressBar(game, workingTime, currentTime, sf::Vector2f(400, 683));
  }
  texts_[1].setString("Health: " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
  texts_[1].setPosition(sf::Vector2f(408, 604));
  texts_[0].setString("Working time:");
  texts_[0].setPosition(sf::Vector2f(408, 657));
  game.getWindow()->draw(texts_[0]);
  game.getWindow()->draw(texts_[1]);
  currentUI_ = workerUI;
}
/*
Specific UI draw function used is soldierUnit is selected
*/
void PlayUI::soldierUnitUI(GameEngine &game, unsigned int damage, int maxHealth, int currentHealth)
{
  buttons_[4].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  buttons_[5].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  game.getWindow()->draw(buttons_[4]);
  game.getWindow()->draw(buttons_[5]);
  drawHealthbar(game, maxHealth, currentHealth, sf::Vector2f(400, 630));
  texts_[0].setString("Damage: " + std::to_string(damage));
  texts_[1].setString("Health: " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
  texts_[0].setPosition(sf::Vector2f(408, 657));
  texts_[1].setPosition(sf::Vector2f(408, 604));
  game.getWindow()->draw(texts_[0]);
  game.getWindow()->draw(texts_[1]);
  buttons_[6].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  buttons_[7].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  game.getWindow()->draw(buttons_[6]);
  game.getWindow()->draw(buttons_[7]);
  currentUI_ = soldierUI;
}
/*
Function to draw required buttons and information to UI for mechanical unit
*/
void PlayUI::mechanicalUnitUI(GameEngine &game, unsigned int damage, int maxHealth, int currentHealth)
{
  buttons_[4].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  buttons_[5].setPosition(sf::Vector2f(geometry_[4] + (geometry_[0] + geometry_[2]), geometry_[5] + 2 * (geometry_[1] + geometry_[2])));
  game.getWindow()->draw(buttons_[4]);
  game.getWindow()->draw(buttons_[5]);
  drawHealthbar(game, maxHealth, currentHealth, sf::Vector2f(400, 630));
  texts_[0].setString("Damage: " + std::to_string(damage));
  texts_[1].setString("Health: " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth));
  texts_[0].setPosition(sf::Vector2f(408, 657));
  texts_[1].setPosition(sf::Vector2f(408, 604));
  game.getWindow()->draw(texts_[0]);
  game.getWindow()->draw(texts_[1]);
  buttons_[6].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  buttons_[7].setPosition(sf::Vector2f(geometry_[4], geometry_[5]));
  game.getWindow()->draw(buttons_[6]);
  game.getWindow()->draw(buttons_[7]);
  currentUI_ = mechanicalUI;
}
/*
Function to draw healthbar to UI
*/
void PlayUI::drawHealthbar(GameEngine &game, int maxHealth, int currentHealth, sf::Vector2f position)
{
  sf::RectangleShape bottom;                          //Create bottom red bar
  sf::RectangleShape top;                             //Create top green bar
  float mhealth = static_cast<float>(maxHealth);
  float chealth = static_cast<float>(currentHealth);
  bottom.setSize(sf::Vector2f(200, 10));      //Set bar sizes according to the unit parameters
  top.setSize(sf::Vector2f((chealth/mhealth)*200, 10));
  bottom.setFillColor(sf::Color::Red);                //Set colors, geometry and positions
  bottom.setPosition(position);
  top.setFillColor(sf::Color::Green);
  top.setPosition(position);
  game.getWindow()->draw(bottom);                     //Draw the bars
  game.getWindow()->draw(top);
}
/*
Function to  draw progress bar into the UI.
*/
void PlayUI::drawProgressBar(GameEngine &game, float max, float current, sf::Vector2f position)
{
  sf::RectangleShape bottom;                          //Create bottom red bar
  sf::RectangleShape top;                             //Create top green bar
  bottom.setSize(sf::Vector2f(150, 10));      //Set bar sizes according to the unit parameters
  top.setSize(sf::Vector2f((current/max)*150, 10));
  bottom.setFillColor(sf::Color(120,120,120));                //Set colors, geometry and positions
  bottom.setPosition(position);
  top.setFillColor(sf::Color::Blue);
  top.setPosition(position);
  game.getWindow()->draw(bottom);                     //Draw the bars
  game.getWindow()->draw(top);
}
/*
Function that draws the resources into upper left corner of UI.
*/
void PlayUI::drawResourceAmount(GameEngine &game, int gold, int silver)
{
  texts_[2].setString(std::to_string(gold));
  texts_[3].setString(std::to_string(silver));
  game.getWindow()->draw(texts_[2]);
  game.getWindow()->draw(texts_[3]);
  game.getWindow()->draw(gold_);
  game.getWindow()->draw(silver_);
}
