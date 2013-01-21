#ifndef city_h_
#define city_h_

#include <vector>
#include <string>
#include <algorithm>

// A City object stores its name and a vector of pointers to other
// City objects that it is linked to.  The links are bidirectional,
// which means that if city A is linked to city B then city B should
// also be linked to city A.

class City {

public:
  City(const std::string& n) : name(n) {}
  
  // ACCESSORS
  const std::string& getName() const { return name; }
  const std::vector<City*>& getNeighbors() const { return neighbors; }
  bool isNeighbor(City* city) const;

  // MODIFIERS
  bool addNeighbor(City* city);
  bool removeNeighbor(City* city);

  // Tell the neighboring cities to remove this City* from its vector of neighbors.
  void removeCityFromItsNeighbors();
  void sortNeighbors();
private: 

  // REPRESENTATION
  std::string name;
  std::vector<City*> neighbors;
};

bool operator==(const City &city1, const City &city2) {
  return city1.getName()==city2.getName();
}
bool sort_by_name(const City *city1, const City *city2) {
  return (city1->getName() <= city2->getName());
}
void City::sortNeighbors() {
  sort(neighbors.begin(),neighbors.end(),sort_by_name);
}
bool City::isNeighbor(City *city) const {
  std::vector<City*>::const_iterator itr;// use const_iterator in const function
  itr = neighbors.begin();
  while (itr != neighbors.end()) {
    if ( (*itr) == city ) 
      return true;
    itr++;
  }
  return false;
}
bool City::addNeighbor(City* city) {
  std::vector<City*>::iterator itr;
  itr = neighbors.begin();
  while( itr != neighbors.end() ) {
    if ( *itr == city ) 
      return false;
    itr++;
  }
  neighbors.push_back(city);
  return true;
}
bool City::removeNeighbor(City* city) {
  std::vector<City*>::iterator itr;
  itr = neighbors.begin();
  while ( itr != neighbors.end() ) {
    if ( *itr == city ) {
      neighbors.erase(itr);
      return true;
    }
    itr++;
  }
  return false;
}

void City::removeCityFromItsNeighbors() {
  if ( neighbors.size() == 0 ) return;
  std::vector<City*>::iterator itr;
  itr = neighbors.begin();
  while( itr != neighbors.end() ) {
    (*itr)->removeNeighbor(this);
    itr++;
  }
}

#endif
