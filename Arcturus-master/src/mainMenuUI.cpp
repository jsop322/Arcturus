#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "mainMenuUI.hpp"


/*
Constructor for class object. Creates the desired shape objects (buttons) and stores them in shapes_ vector.
Also creates required text objects and font objects.
*/
MainMenuUI::MainMenuUI(){
  sf::Font font;
  if (!font.loadFromFile("resources/fonts/Mylodon-Light.otf")){
    std::cout << "Unable to load font" << std::endl;
  }
  font_ = font;                                             // Load and assign the font for the UI.
  sf::Texture texture;
  if (!texture.loadFromFile("resources/graphics/Buttons.png")){
    std::cout << "Unable to load button texture" << std::endl;
  }
  buttonsource_ = texture;
  std::vector<float> geometry = {200, 50, 10, 15, 290, 300};   // Geometry definition: button width, button height, offset, character size, positions x and y
  geometry_ = geometry;
  createButtonSprite(sf::Vector2f(geometry_[0], geometry_[1]), sf::Vector2f(geometry_[4], geometry_[5]));                             // Create buttons
  createButtonSprite(sf::Vector2f(geometry_[0], geometry_[1]), sf::Vector2f(geometry_[4], geometry_[5] + (geometry_[1] + geometry_[2])));
  createButtonSprite(sf::Vector2f(geometry_[0], geometry_[1]), sf::Vector2f(geometry_[4], geometry_[5] + 2*(geometry_[1] + geometry_[2])));
  createTextobject("START GAME", geometry_[3], sf::Color::White, sf::Vector2f(geometry_[4]+35, geometry_[5]+geometry_[2]/2+geometry_[3]/2+2));                                      // Create text objects
  createTextobject("QUIT", geometry_[3], sf::Color::White, sf::Vector2f(geometry_[4]+70, geometry_[5]+2*geometry_[2]+(2*geometry_[1] + geometry_[2]/2+geometry_[3]/2+2)));
  createTextobject("MAIN MENU", geometry_[3]+12, sf::Color::Black, sf::Vector2f(geometry_[4], geometry_[5]-50));
  createTextobject("SELECT MAP", geometry_[3]+12, sf::Color::Black, sf::Vector2f(geometry_[4]-5, geometry_[5]-50));
  createTextobject("MAP EDITOR", geometry_[3], sf::Color::White, sf::Vector2f(geometry_[4]+35, geometry_[5]+geometry_[2]+(geometry_[1] + geometry_[2]/2+geometry_[3]/2+2)));
  sf::Texture texture2;
  if (!texture2.loadFromFile("resources/graphics/MainMenu_background.png")){
    std::cout << "Unable to load background texture" << std::endl;
  }
  background_ = texture2;
}

void MainMenuUI::createButtonSprite(sf::Vector2f size, sf::Vector2f position)
{
  sf::Sprite button;
  button.setTexture(buttonsource_);
  button.setTextureRect(sf::IntRect(50, 100, 200, 50));
  button.setPosition(position);
  buttons_.push_back(button);
}
void MainMenuUI::createTextobject(std::string content, float char_size, sf::Color color, sf::Vector2f position)
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
int MainMenuUI::handleEvents(GameEngine &game, sf::Event event)
{
  if (event.type == sf::Event::Closed){
    game.quit();                                                               //Window closing leads to quitting the game
  }
  if (event.type == sf::Event::MouseButtonPressed){
    if (event.mouseButton.button == sf::Mouse::Left){
      sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
      if (buttons_[0].getGlobalBounds().contains(location)){                   //Mousebutton pressed on first button
        buttons_[0].setTextureRect(sf::IntRect(50, 150, 200, 50));
        buttons_[0].setColor(sf::Color(128,128,128));
        clicked_ = 0;
      }
      else if (buttons_[1].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
        buttons_[1].setTextureRect(sf::IntRect(50, 150, 200, 50));
        buttons_[1].setColor(sf::Color(128,128,128));
        clicked_ = 1;
      }
      else if (buttons_[2].getGlobalBounds().contains(location)){              //Mousebutton pressed on third button
        buttons_[2].setTextureRect(sf::IntRect(50, 150, 200, 50));
        buttons_[2].setColor(sf::Color(128,128,128));
        clicked_ = 2;
      }
    }
  }
  else if (event.type == sf::Event::MouseButtonReleased){
    if (event.mouseButton.button == sf::Mouse::Left){
      sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
      if (buttons_[0].getGlobalBounds().contains(location) && clicked_ == 0){
        clicked_ = 10;                                                          //Mousebutton released on first button
        buttons_[0].setTextureRect(sf::IntRect(50, 100, 200, 50));
        buttons_[0].setColor(sf::Color(255,255,255));
        if(mapselect_ == true){
          game.nextState(std::make_shared<PlayState>(game.mapNames_[0], game.getResourceManager()->getMapTexture(),
          game.getResourceManager()->getUnitTexture(), game.getResourceManager()->getBuildingTexture(), game.getResourceManager()->getSoldierWalking(),
          game.getResourceManager()->getSoldierShooting(), game.getResourceManager()->getWorkerWalking(), game.getResourceManager()->getWorkerAct(),
          game.getResourceManager()->getTankDriving(), game.getResourceManager()->getTankShooting(), game.getResourceManager()->getMainBuilding(),
          game.getResourceManager()->getUnitBuilding(), game.getResourceManager()->getFactoryBuilding(), game.getResourceManager()->getResourceBuilding(), game.getResourceManager()->getEnemySoldierWalking(), game.getResourceManager()->getEnemySoldierShooting(), game.getResourceManager()->getEnemyWorkerWalking(),
          game.getResourceManager()->getEnemyWorkerAct(), game.getResourceManager()->getEnemyTankDriving(), game.getResourceManager()->getEnemyTankShooting(), game.getResourceManager()->getEnemyMainBuilding(), game.getResourceManager()->getEnemyUnitBuilding(),
          game.getResourceManager()->getEnemyFactoryBuilding()));
          mapselect_ = false;
        }
        else{
          mapselect_ = true;
        }
      }
      else if (buttons_[2].getGlobalBounds().contains(location) && clicked_ == 2 && mapselect_ == false){              //Mousebutton released on second button
        clicked_ = 10;
        buttons_[2].setTextureRect(sf::IntRect(50, 100, 200, 50));
        buttons_[2].setColor(sf::Color(255,255,255));
        game.quit();
      }
      else if (buttons_[1].getGlobalBounds().contains(location) && clicked_ == 1){
        clicked_ = 10;                //Mousebutton released on second button
        buttons_[1].setTextureRect(sf::IntRect(50, 100, 200, 50));
        buttons_[1].setColor(sf::Color(255,255,255));
        if(mapselect_ == true){
          game.nextState(std::make_shared<PlayState>(game.mapNames_[1], game.getResourceManager()->getMapTexture(),
          game.getResourceManager()->getUnitTexture(), game.getResourceManager()->getBuildingTexture(), game.getResourceManager()->getSoldierWalking(),
          game.getResourceManager()->getSoldierShooting(), game.getResourceManager()->getWorkerWalking(), game.getResourceManager()->getWorkerAct(),
          game.getResourceManager()->getTankDriving(), game.getResourceManager()->getTankShooting(), game.getResourceManager()->getMainBuilding(),
          game.getResourceManager()->getUnitBuilding(), game.getResourceManager()->getFactoryBuilding(), game.getResourceManager()->getResourceBuilding(), game.getResourceManager()->getEnemySoldierWalking(), game.getResourceManager()->getEnemySoldierShooting(), game.getResourceManager()->getEnemyWorkerWalking(),
          game.getResourceManager()->getEnemyWorkerAct(), game.getResourceManager()->getEnemyTankDriving(), game.getResourceManager()->getEnemyTankShooting(), game.getResourceManager()->getEnemyMainBuilding(), game.getResourceManager()->getEnemyUnitBuilding(),
          game.getResourceManager()->getEnemyFactoryBuilding()));
          mapselect_ = false;
        }
        else{
          game.nextState(std::make_shared<MapEditorState>());
        }

      }
      else{                                                                   //Mousebutton released somewhere else
      buttons_[0].setTextureRect(sf::IntRect(50, 100, 200, 50));
      buttons_[1].setTextureRect(sf::IntRect(50, 100, 200, 50));
      buttons_[2].setTextureRect(sf::IntRect(50, 100, 200, 50));
      buttons_[0].setColor(sf::Color(255,255,255));
      buttons_[1].setColor(sf::Color(255,255,255));
      buttons_[2].setColor(sf::Color(255,255,255));
      }
    }
  }
  else if (event.type == sf::Event::MouseMoved){
    sf::Vector2f location(event.mouseMove.x, event.mouseMove.y);
    if (buttons_[0].getGlobalBounds().contains(location)){                     //Mouse hovered on first button
      buttons_[0].setColor(sf::Color(220,220,220));
    }
    else if (buttons_[1].getGlobalBounds().contains(location)){                //Mouse hovered on second button
      buttons_[1].setColor(sf::Color(220,220,220));
    }
    else if (buttons_[2].getGlobalBounds().contains(location)){                //Mouse hovered on third button
      buttons_[2].setColor(sf::Color(220,220,220));
    }
    else {
      buttons_[0].setColor(sf::Color(255,255,255));
      buttons_[1].setColor(sf::Color(255,255,255));
      buttons_[2].setColor(sf::Color(255,255,255));
    }
  }
  return 0;
}
/*
Draws the buttons into GameEngine window. Buttons and texts are defined in mainMenuUI class entity.
*/
void MainMenuUI::draw(GameEngine &game)
{
  sf::Sprite background;
  background.setTexture(background_);
  game.getWindow()->clear();
  game.getWindow()->draw(background);
  if(mapselect_ == false){
    game.getWindow()->draw(buttons_[0]);
    game.getWindow()->draw(buttons_[1]);
    game.getWindow()->draw(buttons_[2]);
    game.getWindow()->draw(texts_[0]);
    game.getWindow()->draw(texts_[1]);
    game.getWindow()->draw(texts_[2]);
    game.getWindow()->draw(texts_[4]);
  }
  else{
    selectMap(game);
  }
  game.getWindow()->display();
}
/*
Function to handle selection of the map.
*/
void MainMenuUI::selectMap(GameEngine &game){
  game.getWindow()->draw(texts_[3]);
  for(unsigned int i = 0; i < game.mapNames_.size(); i++){
    game.getWindow()->draw(buttons_[i]);
    sf::Text text;
    text.setFont(font_);
    std::string mapname = game.mapNames_[i];
    mapname.erase(0, 2);
    text.setString(mapname);
    text.setCharacterSize(geometry_[3]);
    text.setColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(geometry_[4]+10, geometry_[5]+geometry_[2]*i+(geometry_[1]*i + geometry_[2]/2+geometry_[3]/2+2)));
    game.getWindow()->draw(text);
  }
}
