#include "resource.hpp"

Resource::Resource(sf::Color resourceTypeColor, sf::Sprite resourceSprite, float x, float y)
{
  sprite_ = resourceSprite;
  resourceState_ = 3;
  setType(resourceTypeColor);
  location_.x = x;
  location_.y = y;
  sprite_.setPosition(x*32,y*32);
}

void Resource::setType(sf::Color resourceTypeColor)
{
  if(resourceTypeColor == sf::Color(230,230,230))
  {
    type_ = Silver;
    typeIndex_ = 1;
    maxAmount_ = 500;
    currentAmount_ = maxAmount_;
    sprite_.setTextureRect(sf::IntRect(32*typeIndex_,32*7,32,32));
  }
  if(resourceTypeColor == sf::Color(255,255,0))
  {
    type_ = Gold;
    typeIndex_ = 2;
    maxAmount_ = 50;
    currentAmount_ = maxAmount_;
    sprite_.setTextureRect(sf::IntRect(32*typeIndex_,32*7,32,32));
  }
}

bool Resource::updateResource()
{
  // Sets the correct sprite for each current/max value.
  if(resourceState_ != 2 && (currentAmount_/maxAmount_)*100 <= 66 && (currentAmount_/maxAmount_)*100 > 33){
    sprite_.setTextureRect(sf::IntRect(32*typeIndex_,32*8,32,32));
    resourceState_ = 2;
  }
  if(resourceState_ != 1 && (currentAmount_/maxAmount_)*100 <= 33){
    sprite_.setTextureRect(sf::IntRect(32*typeIndex_,32*9,32,32));
    resourceState_ = 1;
  }
  if(currentAmount_ <= 0){
    return false;
  }
  return true;
}

float Resource::gatherResource(float requestedAmount){
  if(currentAmount_ >= requestedAmount){
    currentAmount_ -= requestedAmount;
    return requestedAmount;
  }
  else{
    float a = currentAmount_;
    currentAmount_ = 0;
    return a;
  }

}
