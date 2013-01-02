#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <vector>
#include "date.h"

// A football Game consists of a Date, and two GameScore's, storing
// the information for the visiting team and the information for the
// home team.  The GameScore class stores the team name and details
// about the scores per quarter, as well as deduced information about
// the number of field goals, and touchdowns.

class GameScore {
 public:
  // CONSTRUCTOR
  GameScore(const std::string& n, int s1, int s2, int s3, int s4, int s5);
  // ACCESSORS
  const std::string& getName() const { return name; }
  int getTotal() const { return total; }
  int getNumTouchdowns() const { return _6_pt_touchdowns + _7_pt_touchdowns + _8_pt_touchdowns; }
  int getNumFieldGoals() const { return field_goals; }
 private:
  // helper function
  bool ProcessScore(int score);
  // REPRESENTATION
  std::string name;
  std::vector<int> scores;
  int total;
  // deduced score breakdown (may not be accurate)
  int safeties;
  int field_goals;
  int _6_pt_touchdowns;
  int _7_pt_touchdowns;
  int _8_pt_touchdowns;
};



class Game {
 public:
  // CONSTRUCTOR
  Game(const Date &d, const GameScore& visitor, const GameScore& home);
  // ACCESSORS
  const Date& getDate() const { return date; }
  const GameScore& getVisitorScore() const { return visitor_score; }
  const GameScore& getHomeScore() const { return home_score; }
 private:
  // REPRESENTATION
  Date date;
  GameScore visitor_score;
  GameScore home_score;
};

// helper function for sorting games
bool sort_by_differential(const Game &g1, const Game &g2);

#endif
