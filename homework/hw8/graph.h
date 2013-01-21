#ifndef _graph_h_
#define _graph_h_

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>


#include "person.h"
#include "city.h"
//class Person;
//class City;


// A Graph object holds a vector of pointers to City objects, the
// cities in the graph.  Objects of type Person may be added to the
// graph in the role of evader or pursuer.  There is at most one
// evader at a time.  Person objects move along the links in the
// graph, one step per time tick.  If the evader and a pursuer are in
// the same city at the end of a tick, the game is over.

class Graph {

public:
  Graph();
  ~Graph();

  // ACCESSORS
  Person* getEvader() const { return evader; }
  const std::vector<Person*>& getPursuers() const { return pursuers; }

  // MODIFIERS
  // each return true if command was successful
  bool addCity(const std::string& city_name);
  bool removeCity(const std::string& city_name);
  bool addLink(const std::string& city_name1, const std::string& city_name2);
  bool removeLink(const std::string& city_name1, const std::string& city_name2);
  bool placePursuer(const std::string& person_name, const std::string& city_name);
  bool placeEvader(const std::string& person_name, const std::string& city_name);
  void sortCities();
  // Move the evader & pursuers.  Return false if the evader has been caught.
  bool tick(const std::string &evader_arg, const std::string &pursuer_arg); 
  // OUTPUT
  friend std::ostream& operator<<(std::ostream &ostr, const Graph &city_graph);

 private:  

  // helper function
  City* getCityWithName(const std::string& name) const;

  // ==============
  // REPRESENTATION
  std::vector<City*> cities;
  Person* evader;
  std::vector<Person*> pursuers;
};
Graph::Graph() {
  // cities = NULL;
  evader = NULL;
  //pursuers = NULL;
}
Graph::~Graph() {
  for (unsigned int i = 0; i<cities.size(); i++) {
    cities[i]->removeCityFromItsNeighbors();
    delete cities[i];
  }
  cities.clear();
  assert(cities.size() == 0);
  delete evader;
  for (unsigned int i = 0; i<pursuers.size(); i++) {
    delete pursuers[i];
  }
  pursuers.clear();
  assert(pursuers.size() == 0 );
}
City* Graph::getCityWithName(const std::string& name) const {
  std::vector<City*>::const_iterator itr = cities.begin();
  while (itr != cities.end() ) {
    if ((*itr)->getName()== name) 
      return *itr;
  }
  City* city = NULL;
  return city;
}
bool Graph::addCity(const std::string& city_name) {
  std::vector<City*>::iterator itr = cities.begin();
  while (itr != cities.end() ) {
    if ((*itr)->getName() == city_name) 
      return false;
  }
  City *city = new City(city_name);
  cities.push_back(city);
  return true;
}

bool Graph::removeCity(const std::string& city_name) {
  std::vector<City*>::iterator itr = cities.begin();
  while (itr != cities.end() ) {
    if ((*itr)->getName() == city_name) {
      City* temp = *itr;
      cities.erase(itr);
      for (unsigned int i = 0; i<cities.size(); i++)
	cities[i]->removeNeighbor(temp);
      delete temp;
      return true;
    }
  }
return false;
}

bool Graph::addLink(const std::string& city_name1, const std::string& city_name2) {
 std::vector<City*>::iterator itr = cities.begin();
 City* c1;
 City* c2;
 int i=0;
  while (itr != cities.end() ) {
    if ((*itr)->getName() == city_name1) { c1 = *itr;i++;}
    if ((*itr)->getName() == city_name2) { c2 = *itr;i++;}
  }
  if ( i!=2)
    return false;
 bool c11 = c1->addNeighbor(c2);
 bool c22 = c2->addNeighbor(c1);
 return c11 && c22;
}
bool Graph::removeLink(const std::string& city_name1, const std::string& city_name2) {
 std::vector<City*>::iterator itr = cities.begin();
 City* c1;
 City* c2;
 int i=0;
  while (itr != cities.end() ) {
    if ((*itr)->getName() == city_name1) { c1 = *itr;i++;}
    if ((*itr)->getName() == city_name2) { c2 = *itr;i++;}
  }
  if ( i != 2)
    return false;
  bool c11 =  c1->removeNeighbor(c2);
  bool c22 = c2->removeNeighbor(c1);
  return c11&&c22;
}
bool Graph::placePursuer(const std::string& person_name, const std::string& city_name) {
  std::vector<Person*>::iterator itr = pursuers.begin();
  while (itr != pursuers.end() ) {
    if ((*itr)->getName() == person_name) 
      return false;
  }
  std::vector<City*>::iterator it = cities.begin();
  while (it != cities.end() ) {
    if ((*it)->getName() == city_name) 
      break;
  }
  if (it == cities.end())
    return false;
  Person *person = new Person(person_name,*it);
  pursuers.push_back(person);
  return true;
}
bool Graph::placeEvader(const std::string& person_name, const std::string& city_name){
  assert(evader==NULL);
  std::vector<City*>::iterator itr = cities.begin();
  while (itr != cities.end() ) {
    if ((*itr)->getName() == city_name) 
      break;
  }
  if( itr == cities.end()) return false;
  evader = new Person(person_name,*itr);
  return true;
}
std::ostream& operator<<(std::ostream &ostr, const Graph &city_graph){
 std::cout << std::endl;

  std::vector<City*> neighbors;
  for (int i = 0; i < city_graph.cities.size(); i++) {
    std::cout << "Neighbors for city " << city_graph.cities[i]->getName() << ": ";
    neighbors = city_graph.cities[i]->getNeighbors();
    for (int j = 0; j < neighbors.size(); j++) {
      std::cout << neighbors[j]->getName() << ' ';
    }
    std::cout << std::endl;
  }

  if ( city_graph.evader ) {
    std::cout << "Evader " << city_graph.evader->getName() <<
      " is at city " << city_graph.evader->getLocation()->getName() << std::endl;
  }

  for (int i = 0; i < city_graph.pursuers.size(); i++) {
    std::cout << "Pursuer " << city_graph.pursuers[i]->getName() <<
      " is at city " << city_graph.pursuers[i]->getLocation()->getName() << std::endl;
  }
  std::cout << std::endl;

  return ostr;
}

void Graph::sortCities() {
  // sort all of the cities by name
  std::sort(cities.begin(), cities.end(), sort_by_name);

  // sort each city's neighbors by name
  for (int i = 0; i < cities.size(); i++)
    cities[i]->sortNeighbors();
}

#endif
