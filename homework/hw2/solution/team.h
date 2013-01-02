#ifndef __game_h_
#define __game_h_

#include "game.h"

// A Team object stores data about a single football team, the name,
// and the list of all games the team was involved in, from which
// various interesting data can be computed.

class Team {
 public:

  // CONSTRUCTOR
  Team(const std::string& n) : name(n) {}

  // ACCESSORS
  std::string getName() const { return name; }
  int getNumGames() const { return games.size(); }
  double getWinPercentage() const;
  int getWins() const;
  int getLosses() const;
  double getAverageOpponentTouchdownsPerGame() const;
  int getTotalOpponentTouchdowns() const;
  int getTotalOpponentFieldGoals() const;

  // MODIFIERS
  void addGame(const Game &g) { games.push_back(g); }

 private:
  // REPRESENTATION
  std::string name;
  std::vector<Game> games;
};


// helper functions for sorting teams
bool sort_by_wins(const Team &t1, const Team &t2);
bool sort_by_opponent_touchdowns(const Team &t1, const Team &t2);

#endif
