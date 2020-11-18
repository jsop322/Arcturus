#ifndef ASTAR_H
#define ASTAR_H

#include <SFML/Graphics.hpp>

struct Node
{
  sf::Vector2i position;
  size_t parentIndex;
  float g;
  float h;
  float f;
};

class AStar
{
public:
  AStar(){}
  void setMap(std::vector<std::vector<int>> mapInfo);
  std::vector<sf::Vector2i> calcPath(sf::Vector2i start, sf::Vector2i end);
  //std::vector<sf::Vector2i> continueCalculation();
  bool isEmpty();
  void clear();

private:
  std::vector<std::vector<int>> map_;
  std::vector<Node> open_list;
  std::vector<Node> closed_list;
  struct Node startNode;
  struct Node endNode;
  size_t parent_index = 0;
};


#endif
