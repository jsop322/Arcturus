#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>

enum ResourceType{Silver, Gold};

class Resource
{
public:
  Resource(sf::Color resourceTypeColor, sf::Sprite resourceSprite, float x, float y);

  sf::Sprite getSprite() const {return sprite_;}
  ResourceType getType() const {return type_;}
  float getAmount() const {return currentAmount_;}
  sf::Vector2f getLocation() const {return location_;}

  void setType(sf::Color resourceTypeColor);

  float gatherResource(float requestedAmount); // Reduces amount and deposits said amount to player bank. Might need some parameters. Will be decided when workers are added.
  bool updateResource(); // Will update the sprite to represent % amount of resource left. Also checks if it is depleted. Returns FALSE when amount <= 0.

private:
  ResourceType type_;
  int typeIndex_;
  int resourceState_; // Values from 0-3. 3 = 100-66%, 2 = 66-33%, 1 = 33-0%, 0 = EMPTY
  float maxAmount_;
  float currentAmount_;
  sf::Sprite sprite_;
  sf::Vector2f location_;

};

#endif
