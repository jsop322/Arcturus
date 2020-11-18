#include "aStar.hpp"
#include <math.h>
#include <iostream>

static double calcH(int x, int y, Node dest)
{
  double dist = sqrt(pow((x - dest.position.x), 2) + pow((y - dest.position.y), 2));
  return dist;
}

bool AStar::isEmpty()
{
  if(closed_list.empty()){
    return true;
  }
  else{
    return false;
  }
}
void AStar::clear()
{
  open_list.clear();
  closed_list.clear();
  parent_index = 0;
}
void AStar::setMap(std::vector<std::vector<int>> mapInfo)
{
  map_ = mapInfo;
}
std::vector<sf::Vector2i> AStar::calcPath(sf::Vector2i start, sf::Vector2i end)
{
  if(map_[end.x][end.y] != 1){
    startNode.position = start;
    endNode.position = end;
    startNode.g = 0;
    startNode.h = 0;
    startNode.f = 0;
    endNode.g = 0;
    endNode.h = 0;
    endNode.f = 0;
    open_list.push_back(startNode);
    struct Node currentNode;
    while(open_list.size() != 0){
      size_t index = 0;
      currentNode = open_list[0];
      // Find the node with least F in open list
      for(size_t i = 1; i < open_list.size(); i++){
        if (currentNode.f > open_list[i].f){
          currentNode = open_list[i];
          index = i;
        }
      }
      // Move it to the closed list
      open_list.erase(open_list.begin()+index);
      closed_list.push_back(currentNode);

      // Check if the end is found
      if(currentNode.position == end){
        // If the end was found, create path from closed list, by iterating backwards from last node to nodes parent node.
        std::vector<Node> nodePath;
        nodePath.push_back(closed_list.back());
        while(nodePath[0].position != start){
          nodePath.insert(nodePath.begin(), closed_list[nodePath[0].parentIndex]);
        }
        std::vector<sf::Vector2i> path;
        for(auto point : nodePath){
          path.push_back(point.position);
        }
        return path;
      }

      // Create the children nodes
      std::vector<Node> children;
      std::vector<std::pair<int, int>> adjacent_nodes = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,-1}, {-1,1}, {-1,-1}, {1,1}};
      bool withinRange;
      // Tähän menee
      for(auto pos_change : adjacent_nodes){
        withinRange = true;
        Node new_node;
        new_node.position.x = currentNode.position.x + pos_change.first;
        new_node.position.y = currentNode.position.y + pos_change.second;
        new_node.parentIndex = parent_index;
        if(withinRange){
          if(map_[new_node.position.x][new_node.position.y] == 0){
            children.push_back(new_node);
          }
        }
      }
      // Loop through children nodes
      for(auto child : children){
        bool not_closed = true;                     //Chech if the he node is already in closed list
        for(auto closed_child : closed_list){
          if(closed_child.position == child.position){
            not_closed = false;
          }
        }
        bool not_open = true;
        if(not_closed){
          child.g = currentNode.g + 1;
          child.h = calcH(child.position.x, child.position.y, endNode);
          child.f = child.g + child.h;
          for(auto open_node : open_list){
            if(open_node.position == child.position){
              not_open = false;
            }
          }
          if(not_open){
            open_list.push_back(child);
          }
        }
      }
      parent_index ++;
      //counter++;
    }
    std::vector<sf::Vector2i> empty;
    empty.push_back(start);
    return empty;
  }
  else{
    std::vector<sf::Vector2i> empty;
    empty.push_back(start);
    return empty;
  }
}

/*std::vector<sf::Vector2i> AStar::continueCalculation()
{
  struct Node currentNode;
  size_t counter = 0;
  while(open_list.size() != 0){
    size_t index = 0;
    if(counter == 10){
      std::vector<sf::Vector2i> unready;
      unready.push_back(sf::Vector2i(0,0));
      return unready;
    }
    currentNode = open_list[0];
    // Find the node with least F in open list
    for(size_t i = 1; i < open_list.size(); i++){
      if (currentNode.f > open_list[i].f){
        currentNode = open_list[i];
        index = i;
      }
    }
    // Move it to the closed list
    open_list.erase(open_list.begin()+index);
    closed_list.push_back(currentNode);

    // Check if the end is found
    if(currentNode.position == endNode.position){
      // If the end was found, create path from closed list, by iterating backwards from last node to nodes parent node.
      std::vector<Node> nodePath;
      nodePath.push_back(closed_list.back());
      while(nodePath[0].position != startNode.position){
        nodePath.insert(nodePath.begin(), closed_list[nodePath[0].parentIndex]);
      }
      std::vector<sf::Vector2i> path;
      for(auto point : nodePath){
        path.push_back(point.position);
      }
      return path;
    }

    // Create the children nodes
    std::vector<Node> children;
    std::vector<std::pair<int, int>> adjacent_nodes = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,-1}, {-1,1}, {-1,-1}, {1,1}};
    bool withinRange;
    // Tähän menee
    for(auto pos_change : adjacent_nodes){
      withinRange = true;
      Node new_node;
      new_node.position.x = currentNode.position.x + pos_change.first;
      new_node.position.y = currentNode.position.y + pos_change.second;
      new_node.parentIndex = parent_index;
      if(withinRange){
        if(map_[new_node.position.x][new_node.position.y] == 0){
          children.push_back(new_node);
        }
      }
    }
    // Loop through children nodes
    for(auto child : children){
      bool not_closed = true;                     //Chech if the he node is already in closed list
      for(auto closed_child : closed_list){
        if(closed_child.position == child.position){
          not_closed = false;
        }
      }
      bool not_open = true;
      if(not_closed){
        child.g = currentNode.g + 1;
        child.h = calcH(child.position.x, child.position.y, endNode);
        child.f = child.g + child.h;
        for(auto open_node : open_list){
          if(open_node.position == child.position){
            not_open = false;
          }
        }
        if(not_open){
          open_list.push_back(child);
        }
      }
    }
    parent_index++;
    counter++;
  }
  std::vector<sf::Vector2i> empty;
  empty.push_back(startNode.position);
  return empty;
}*/
