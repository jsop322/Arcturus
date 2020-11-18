#include "mapEditorState.hpp"

MapEditorState::MapEditorState(){
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
  createButtonSprite(sf::Vector2f(200, 50), sf::Vector2f(50, 100));                             // Create buttons
  createButtonSprite(sf::Vector2f(200, 50), sf::Vector2f(300, 100));
  createButtonSprite(sf::Vector2f(200, 50), sf::Vector2f(550, 100));
  createButtonSprite(sf::Vector2f(200, 50), sf::Vector2f(580, 50));
  createButton(sf::Vector2f(40, 40), sf::Vector2f(30, 55));                              // Create buttons for colors
  createButton(sf::Vector2f(40, 40), sf::Vector2f(80, 55));
  createButton(sf::Vector2f(40, 40), sf::Vector2f(130, 55));
  createButton(sf::Vector2f(40, 40), sf::Vector2f(180, 55));

  createTextobject("2 5 X 2 5", 15, sf::Color::White, sf::Vector2f(100, 115));                                      // Create text objects
  createTextobject("5 0 X 5 0", 15, sf::Color::White, sf::Vector2f(350, 115));
  createTextobject("1 0 0 X 1 0 0", 15, sf::Color::White, sf::Vector2f(590, 115));
  createTextobject("SELECT MAP SIZE", 20, sf::Color::White, sf::Vector2f(280, 50));
  createTextobject("DRAW MAP TEXTURES", 20, sf::Color::White, sf::Vector2f(260, 20));
  createTextobject("DRAW MAP FEATURES", 20, sf::Color::White, sf::Vector2f(280, 20));
  createTextobject("SELECT COLOR BY CLICKING", 10, sf::Color::White, sf::Vector2f(30, 40));
  createTextobject("READY", 15, sf::Color::White, sf::Vector2f(650,65));
  state_ = 0;
  stateSet_ = true;
}

void MapEditorState::pause()
{
  std::cout << "PELI PIIP!" << std::endl;
}

/*
** Resumes the game.
** Might be used just to set game time. Should concider using proper pauseState.
*/
void MapEditorState::resume()
{
  std::cout << "JATKUU!" << std::endl;
}

void MapEditorState::handleEvents(GameEngine &game, sf::Event event)
{
  if (event.type == sf::Event::Closed){
    game.quit();
  }
  if(event.type == sf::Event::KeyReleased)
  {
    if (event.key.code == sf::Keyboard::Escape){
      game.previousState();
    }
  }
  if(state_ == 0){                                                           //Window closing leads to quitting the game
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
        else if (buttons_[2].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[2].setTextureRect(sf::IntRect(50, 150, 200, 50));
          buttons_[2].setColor(sf::Color(128,128,128));
          clicked_ = 2;
        }
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (buttons_[0].getGlobalBounds().contains(location) && clicked_ == 0){                   //Mousebutton released on first button
          buttons_[0].setTextureRect(sf::IntRect(50, 100, 200, 50));
          buttons_[0].setColor(sf::Color(255,255,255));
          mapSize_ = sf::Vector2f(25,25);
          state_ = 1;
          stateSet_ = false;
          border_.setSize(mapSize_*6.f);
          canvas_.setSize(sf::Vector2f(mapSize_.x*6.f-12, mapSize_.y*6.f-12));
          canvas_.setFillColor(sf::Color(120,120,120));
          canvas_.setPosition(sf::Vector2f(327,327));
          border_.setFillColor(sf::Color(0,0,0,0));
          border_.setOutlineColor(sf::Color(255,255,255));
          border_.setOutlineThickness(10);
          border_.setPosition(sf::Vector2f(327,327));
          for(int i = 0; i < 25; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(327+(6*i), 327));
            layer_one_.push_back(pixel);
          }
          for(int i = 0; i < 25; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(327+(6*i), 327+(6*(mapSize_.y-1))));
            layer_one_.push_back(pixel);
          }
          for(int i = 1; i < 24; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(327, 327+(6*i)));
            layer_one_.push_back(pixel);
          }
          for(int i = 1; i < 24; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(327+6*(mapSize_.x-1), 327+(6*i)));
            layer_one_.push_back(pixel);
          }

        }
        else if (buttons_[1].getGlobalBounds().contains(location) && clicked_ == 1){              //Mousebutton released on second button
          buttons_[1].setTextureRect(sf::IntRect(50, 100, 200, 50));
          buttons_[1].setColor(sf::Color(255,255,255));
          mapSize_ = sf::Vector2f(50,50);
          state_ = 1;
          stateSet_ = false;
          border_.setSize(mapSize_*6.f);
          canvas_.setSize(sf::Vector2f(mapSize_.x*6.f-12, mapSize_.y*6.f-12));
          canvas_.setFillColor(sf::Color(120,120,120));
          canvas_.setPosition(sf::Vector2f(252+6,252+6));
          border_.setFillColor(sf::Color(0,0,0,0));
          border_.setOutlineColor(sf::Color(255,255,255));
          border_.setOutlineThickness(10);
          border_.setPosition(sf::Vector2f(252,252));
          for(int i = 0; i < 50; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(252+(6*i), 252));
            layer_one_.push_back(pixel);
          }
          for(int i = 0; i < 50; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(252+(6*i), 252+(6*(mapSize_.y-1))));
            layer_one_.push_back(pixel);
          }
          for(int i = 1; i < 49; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(252, 252+(6*i)));
            layer_one_.push_back(pixel);
          }
          for(int i = 1; i < 49; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(252+6*(mapSize_.x-1), 252+(6*i)));
            layer_one_.push_back(pixel);
          }
        }
        else if (buttons_[2].getGlobalBounds().contains(location) && clicked_ == 2){              //Mousebutton released on second button
          buttons_[2].setTextureRect(sf::IntRect(50, 100, 200, 50));
          buttons_[2].setColor(sf::Color(255,255,255));
          mapSize_ = sf::Vector2f(100,100);
          state_ = 1;
          stateSet_ = false;
          border_.setSize(mapSize_*6.f);
          canvas_.setSize(sf::Vector2f(mapSize_.x*6.f-12, mapSize_.y*6.f-12));
          canvas_.setFillColor(sf::Color(120,120,120));
          canvas_.setPosition(sf::Vector2f(102+6,152+6));
          border_.setFillColor(sf::Color(0,0,0,0));
          border_.setOutlineColor(sf::Color(255,255,255));
          border_.setOutlineThickness(10);
          border_.setPosition(sf::Vector2f(102,152));
          for(int i = 0; i < 100; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(102+(6*i), 152));
            layer_one_.push_back(pixel);
          }
          for(int i = 0; i < 100; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(102+(6*i), 152+(6*(mapSize_.y-1))));
            layer_one_.push_back(pixel);
          }
          for(int i = 1; i < 99; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(102, 152+(6*i)));
            layer_one_.push_back(pixel);
          }
          for(int i = 1; i < 99; i++){
            sf::RectangleShape pixel;
            pixel.setSize(sf::Vector2f(6,6));
            pixel.setFillColor(sf::Color(0,0,0));
            pixel.setPosition(sf::Vector2f(102+6*(mapSize_.x-1), 152+(6*i)));
            layer_one_.push_back(pixel);
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
        clicked_ = 10;
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
      else if (buttons_[2].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        buttons_[2].setColor(sf::Color(220,220,220));
      }
      else {
        buttons_[0].setColor(sf::Color(255,255,255));
        buttons_[1].setColor(sf::Color(255,255,255));
        buttons_[2].setColor(sf::Color(255,255,255));
      }
    }
  }
  else if(state_ == 1){
    if (event.type == sf::Event::MouseButtonPressed){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (colorButtons_[0].getGlobalBounds().contains(location)){                   //Mousebutton pressed on first button
          colorButtons_[0].setOutlineColor(sf::Color::Black);
          clicked_ = 0;
        }
        else if (colorButtons_[1].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          colorButtons_[1].setOutlineColor(sf::Color::Black);
          clicked_ = 1;
        }
        else if (colorButtons_[2].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          colorButtons_[2].setOutlineColor(sf::Color::Black);
          clicked_ = 2;
        }
        else if (colorButtons_[3].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          colorButtons_[3].setOutlineColor(sf::Color::Black);
          clicked_ = 3;
        }
        else if (buttons_[3].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[3].setTextureRect(sf::IntRect(50, 150, 200, 50));
          buttons_[3].setColor(sf::Color(128,128,128));
          clicked_ = 41;
        }
        else if (canvas_.getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          sf::RectangleShape pixel;
          pixel.setSize(sf::Vector2f(6,6));
          pixel.setFillColor(selectedColor_);
          pixel.setPosition(pointer_.getPosition());
          for(size_t i = 0; i < layer_one_.size(); i++){
            if(layer_one_[i].getPosition() == pixel.getPosition()){
              layer_one_.erase(layer_one_.begin() + i);
            }
          }
          layer_one_.push_back(pixel);
          previousloc_ = pointer_.getPosition();
          clicked_ = 4;
        }
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (colorButtons_[0].getGlobalBounds().contains(location) && clicked_ == 0){                   //Mousebutton released on first button
          colorButtons_[0].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(120,120,120);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (colorButtons_[1].getGlobalBounds().contains(location) && clicked_ == 1){              //Mousebutton released on second button
          colorButtons_[1].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(0,255,0);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (colorButtons_[2].getGlobalBounds().contains(location) && clicked_ == 2){              //Mousebutton released on second button
          colorButtons_[2].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(0,0,0);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (colorButtons_[3].getGlobalBounds().contains(location) && clicked_ == 3){              //Mousebutton released on second button
          colorButtons_[3].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(255,120,0);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (buttons_[3].getGlobalBounds().contains(location) && clicked_ == 41){                   //Mousebutton released on first button
          buttons_[3].setTextureRect(sf::IntRect(50, 100, 200, 50));
          buttons_[3].setColor(sf::Color(255,255,255));
          state_ = 2;
          stateSet_ = false;
        }
        else{                                                                   //Mousebutton released somewhere else
          colorButtons_[0].setOutlineColor(sf::Color::White);
          colorButtons_[1].setOutlineColor(sf::Color::White);
          colorButtons_[2].setOutlineColor(sf::Color::White);
          colorButtons_[3].setOutlineColor(sf::Color::White);
          buttons_[3].setTextureRect(sf::IntRect(50, 100, 200, 50));
          buttons_[3].setColor(sf::Color(255,255,255));
        }
        clicked_ = 10;
      }
    }
    else if (event.type == sf::Event::MouseMoved){
      sf::Vector2f location(event.mouseMove.x, event.mouseMove.y);
      if(canvas_.getGlobalBounds().contains(location) && colorSelected_ && clicked_ != 4){
        sf::Vector2f targetloc = location;
        sf::Vector2f canvasLoc = canvas_.getPosition();
        int x = static_cast<int>(location.x - canvasLoc.x);
        int y = static_cast<int>(location.y - canvasLoc.y);
        if( (x % 6) > 0){
          targetloc.x = x-(x%6) + canvasLoc.x;
        }
        if( (y % 6) > 0){
          targetloc.y = y-(y%6) + canvasLoc.y;
        }
        pointer_.setPosition(targetloc);
      }
      else if(clicked_ == 4 && canvas_.getGlobalBounds().contains(location)){
        sf::Vector2f targetloc = location;
        sf::Vector2f canvasLoc = canvas_.getPosition();
        int x = static_cast<int>(location.x - canvasLoc.x);
        int y = static_cast<int>(location.y - canvasLoc.y);
        if( (x % 6) > 0){
          targetloc.x = x-(x%6) + canvasLoc.x;
        }
        if( (y % 6) > 0){
          targetloc.y = y-(y%6) + canvasLoc.y;
        }
        if(targetloc != previousloc_){
          previousloc_ = targetloc;
          sf::RectangleShape pixel;
          pixel.setSize(sf::Vector2f(6,6));
          pixel.setFillColor(selectedColor_);
          pixel.setPosition(targetloc);
          for(size_t i = 0; i < layer_one_.size(); i++){
            if(layer_one_[i].getPosition() == pixel.getPosition()){
              layer_one_.erase(layer_one_.begin() + i);
            }
          }
          layer_one_.push_back(pixel);
        }
      }
      else if (colorButtons_[0].getGlobalBounds().contains(location)){                     //Mouse hovered on first button
        colorButtons_[0].setFillColor(sf::Color(150,150,150));
      }
      else if (colorButtons_[1].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        colorButtons_[1].setFillColor(sf::Color(0,100,0));
      }
      else if (colorButtons_[2].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        colorButtons_[2].setFillColor(sf::Color(0,0,0));
      }
      else if (colorButtons_[3].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        colorButtons_[3].setFillColor(sf::Color(255,76,0));
      }
      else if (buttons_[3].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        buttons_[3].setColor(sf::Color(220,220,220));
      }
      else {
        colorButtons_[0].setFillColor(sf::Color(120,120,120)); //Grey
        colorButtons_[1].setFillColor(sf::Color(0,255,0));     //Green
        colorButtons_[2].setFillColor(sf::Color(0,0,0));       //Black
        colorButtons_[3].setFillColor(sf::Color(255,120,0));   //Brown
        buttons_[3].setColor(sf::Color(255,255,255));
      }
    }
  }
  else if(state_ == 2){
    if (event.type == sf::Event::MouseButtonPressed){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (colorButtons_[0].getGlobalBounds().contains(location)){                   //Mousebutton pressed on first button
          colorButtons_[0].setOutlineColor(sf::Color::Black);
          clicked_ = 0;
        }
        else if (colorButtons_[1].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          colorButtons_[1].setOutlineColor(sf::Color::Black);
          clicked_ = 1;
        }
        else if (colorButtons_[2].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          colorButtons_[2].setOutlineColor(sf::Color::Black);
          clicked_ = 2;
        }
        else if (colorButtons_[3].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          colorButtons_[3].setOutlineColor(sf::Color::Black);
          clicked_ = 3;
        }
        else if (buttons_[3].getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          buttons_[3].setTextureRect(sf::IntRect(50, 150, 200, 50));
          buttons_[3].setColor(sf::Color(128,128,128));
          clicked_ = 41;
        }
        else if (canvas_.getGlobalBounds().contains(location)){              //Mousebutton pressed on second button
          sf::RectangleShape pixel;
          pixel.setSize(sf::Vector2f(6,6));
          pixel.setFillColor(selectedColor_);
          pixel.setPosition(pointer_.getPosition());
          for(size_t i = 0; i < layer_two_.size(); i++){
            if(layer_two_[i].getPosition() == pixel.getPosition()){
              layer_two_.erase(layer_two_.begin() + i);
            }
          }
          layer_two_.push_back(pixel);
          previousloc_ = pointer_.getPosition();
          clicked_ = 4;
        }
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased){
      if (event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f location(event.mouseButton.x, event.mouseButton.y);
        if (colorButtons_[0].getGlobalBounds().contains(location) && clicked_ == 0){                   //Mousebutton released on first button
          colorButtons_[0].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(255,255,0);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (colorButtons_[1].getGlobalBounds().contains(location) && clicked_ == 1){              //Mousebutton released on second button
          colorButtons_[1].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(230,230,230);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (colorButtons_[2].getGlobalBounds().contains(location) && clicked_ == 2){              //Mousebutton released on second button
          colorButtons_[2].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(0,0,255);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (colorButtons_[3].getGlobalBounds().contains(location) && clicked_ == 3){              //Mousebutton released on second button
          colorButtons_[3].setOutlineColor(sf::Color::White);
          selectedColor_ = sf::Color(255,0,0);
          colorSelected_ = true;
          pointer_.setSize(sf::Vector2f(6, 6));
          pointer_.setFillColor(selectedColor_);
        }
        else if (buttons_[3].getGlobalBounds().contains(location) && clicked_ == 41){                   //Mousebutton released on first button
          buttons_[3].setTextureRect(sf::IntRect(50, 100, 200, 50));
          buttons_[3].setColor(sf::Color(255,255,255));
          state_ = 3;
          stateSet_ = false;
        }
        else{                                                                   //Mousebutton released somewhere else
          colorButtons_[0].setOutlineColor(sf::Color::White);
          colorButtons_[1].setOutlineColor(sf::Color::White);
          colorButtons_[2].setOutlineColor(sf::Color::White);
          colorButtons_[3].setOutlineColor(sf::Color::White);
        }
        clicked_ = 10;
      }
    }
    else if (event.type == sf::Event::MouseMoved){
      sf::Vector2f location(event.mouseMove.x, event.mouseMove.y);
      if(canvas_.getGlobalBounds().contains(location) && colorSelected_){
        sf::Vector2f targetloc = location;
        sf::Vector2f canvasLoc = canvas_.getPosition();
        int x = static_cast<int>(location.x - canvasLoc.x);
        int y = static_cast<int>(location.y - canvasLoc.y);
        if( (x % 6) > 0){
          targetloc.x = x-(x%6) + canvasLoc.x;
        }
        if( (y % 6) > 0){
          targetloc.y = y-(y%6) + canvasLoc.y;
        }
        pointer_.setPosition(targetloc);
      }
      if(clicked_ == 4 && canvas_.getGlobalBounds().contains(location)){
        sf::Vector2f targetloc = location;
        sf::Vector2f canvasLoc = canvas_.getPosition();
        int x = static_cast<int>(location.x - canvasLoc.x);
        int y = static_cast<int>(location.y - canvasLoc.y);
        if( (x % 6) > 0){
          targetloc.x = x-(x%6) + canvasLoc.x;
        }
        if( (y % 6) > 0){
          targetloc.y = y-(y%6) + canvasLoc.y;
        }
        if(targetloc != previousloc_){
          previousloc_ = targetloc;
          sf::RectangleShape pixel;
          pixel.setSize(sf::Vector2f(6,6));
          pixel.setFillColor(selectedColor_);
          pixel.setPosition(targetloc);
          for(size_t i = 0; i < layer_two_.size(); i++){
            if(layer_two_[i].getPosition() == pixel.getPosition()){
              layer_two_.erase(layer_two_.begin() + i);
            }
          }
          layer_two_.push_back(pixel);
        }
      }
      else if (colorButtons_[0].getGlobalBounds().contains(location)){                     //Mouse hovered on first button
        colorButtons_[0].setFillColor(sf::Color(255,255,100));
      }
      else if (colorButtons_[1].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        colorButtons_[1].setFillColor(sf::Color(200,200,200));
      }
      else if (colorButtons_[2].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        colorButtons_[2].setFillColor(sf::Color(20,20,230));
      }
      else if (colorButtons_[3].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        colorButtons_[3].setFillColor(sf::Color(230,0,0));
      }
      else if (buttons_[3].getGlobalBounds().contains(location)){                //Mouse hovered on second button
        buttons_[3].setColor(sf::Color(220,220,220));
      }
      else {
        colorButtons_[0].setFillColor(sf::Color(255,255,0)); //Grey
        colorButtons_[1].setFillColor(sf::Color(230,230,230));     //Green
        colorButtons_[2].setFillColor(sf::Color(0,0,255));       //Black
        colorButtons_[3].setFillColor(sf::Color(255,0,0));   //Brown
        buttons_[3].setColor(sf::Color(255,255,255));
      }
    }
  }
  else if(state_ == 3){
    
  }
}

void MapEditorState::draw(GameEngine &game)
{
  game.getWindow()->clear();
  if(state_ == 0){
    game.getWindow()->draw(buttons_[0]);
    game.getWindow()->draw(buttons_[1]);
    game.getWindow()->draw(buttons_[2]);
    game.getWindow()->draw(texts_[0]);
    game.getWindow()->draw(texts_[1]);
    game.getWindow()->draw(texts_[2]);
    game.getWindow()->draw(texts_[3]);
  }
  else if(state_ == 1){
    game.getWindow()->draw(buttons_[3]);
    game.getWindow()->draw(texts_[4]);
    game.getWindow()->draw(texts_[6]);
    game.getWindow()->draw(texts_[7]);
    game.getWindow()->draw(border_);
    game.getWindow()->draw(canvas_);
    game.getWindow()->draw(colorButtons_[0]);
    game.getWindow()->draw(colorButtons_[1]);
    game.getWindow()->draw(colorButtons_[2]);
    game.getWindow()->draw(colorButtons_[3]);
    if(pointer_.getPosition().x != 0 && pointer_.getPosition().y != 0){
      game.getWindow()->draw(pointer_);
    }
    for(auto i : layer_one_){
      game.getWindow()->draw(i);
    }
  }
  else if(state_ == 2){
    game.getWindow()->draw(buttons_[3]);
    game.getWindow()->draw(texts_[5]);
    game.getWindow()->draw(texts_[6]);
    game.getWindow()->draw(texts_[7]);
    game.getWindow()->draw(border_);
    game.getWindow()->draw(canvas_);
    game.getWindow()->draw(colorButtons_[0]);
    game.getWindow()->draw(colorButtons_[1]);
    game.getWindow()->draw(colorButtons_[2]);
    game.getWindow()->draw(colorButtons_[3]);
    if(pointer_.getPosition().x != 0 && pointer_.getPosition().y != 0){
      game.getWindow()->draw(pointer_);
    }
    for(auto i : layer_one_){
      game.getWindow()->draw(i);
    }
    for(auto i : layer_two_){
      game.getWindow()->draw(i);
    }
  }
  game.getWindow()->display();
}

void MapEditorState::update(GameEngine &game, float &deltaTime){
  if(!stateSet_){
    if(state_ == 1){
      colorButtons_[0].setFillColor(sf::Color(120,120,120)); //Grey
      colorButtons_[1].setFillColor(sf::Color(0,255,0));     //Green
      colorButtons_[2].setFillColor(sf::Color(0,0,0));       //Black
      colorButtons_[3].setFillColor(sf::Color(255,120,0));   //Brown
      stateSet_ = true;
    }
    if(state_ == 2){
      colorButtons_[0].setFillColor(sf::Color(255,255,0)); //Gold
      colorButtons_[1].setFillColor(sf::Color(230,230,230));     //Silver
      colorButtons_[2].setFillColor(sf::Color(0,0,255));       //Blue
      colorButtons_[3].setFillColor(sf::Color(255,0,0));   //Red
      stateSet_ = true;
    }
  }
}

void MapEditorState::createButton(sf::Vector2f size, sf::Vector2f position)
{
  sf::RectangleShape button;
  button.setPosition(position);
  button.setOutlineThickness(2);
  button.setOutlineColor(sf::Color::White);
  button.setSize(size);
  colorButtons_.push_back(button);
}

void MapEditorState::createButtonSprite(sf::Vector2f size, sf::Vector2f position)
{
  sf::Sprite button;
  button.setTexture(buttonsource_);
  button.setTextureRect(sf::IntRect(50, 100, 200, 50));
  button.setPosition(position);
  buttons_.push_back(button);
}
void MapEditorState::createTextobject(std::string content, float char_size, sf::Color color, sf::Vector2f position)
{
  sf::Text text;
  text.setFont(font_);
  text.setString(content);
  text.setCharacterSize(char_size);
  text.setColor(color);
  text.setPosition(position);
  texts_.push_back(text);
}

void MapEditorState::setSize(unsigned int width, unsigned int height)
{
  sf::Image textures;
  sf::Image features;
  textures.create(width+2, height+2, sf::Color(0,0,0,0));
  features.create(width+2, height+2, sf::Color(0,0,0,0));
  textures_ = textures;
  features_ = features;
}
