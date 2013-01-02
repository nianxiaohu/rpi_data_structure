#include "team.h"
#include <cassert>
#include <iostream>


// functions for calculating number of wins, number of losses, and
// overall win percentage

double Team::getWinPercentage() const {
  assert (games.size() > 0);
  return getWins() / double(games.size());
}

int Team::getWins() const {
  int total = 0;
  assert (games.size() > 0);
  for (unsigned int i = 0; i < games.size(); i++) {
    if (games[i].getVisitorScore().getName() == name) {
      if (games[i].getVisitorScore().getTotal() > games[i].getHomeScore().getTotal()) 
	total++;
    } else {
      assert (games[i].getHomeScore().getName() == name);
      if (games[i].getVisitorScore().getTotal() < games[i].getHomeScore().getTotal()) 
	total++;
    }
  }
  return total;
}

int Team::getLosses() const {
  return games.size() - getWins();
}


// functions for calculating the (deduced) number of
// touchdowns & fieldgoals by the opponent

double Team::getAverageOpponentTouchdownsPerGame() const {
  assert (games.size() > 0);
  return getTotalOpponentTouchdowns() / (double)games.size();
}

int Team::getTotalOpponentTouchdowns() const {
  int total = 0;
  for (unsigned int i = 0; i < games.size(); i++) {
    if (games[i].getVisitorScore().getName() == name) {
      total += games[i].getHomeScore().getNumTouchdowns();
    } else {
      assert (games[i].getHomeScore().getName() == name);
      total += games[i].getVisitorScore().getNumTouchdowns();
    }
  }
  return total;
}

int Team::getTotalOpponentFieldGoals() const {
  int total = 0;
  for (unsigned int i = 0; i < games.size(); i++) {
    if (games[i].getVisitorScore().getName() == name) {
      total += games[i].getHomeScore().getNumFieldGoals();
    } else {
      assert (games[i].getHomeScore().getName() == name);
      total += games[i].getVisitorScore().getNumFieldGoals();
    }
  }
  return total;
}


// helper functions for sorting teams

bool sort_by_wins(const Team &t1, const Team &t2) {
  if (t1.getWinPercentage() > t2.getWinPercentage() ||
      (t1.getWinPercentage() == t2.getWinPercentage() && (t1.getNumGames() > t2.getNumGames())) ||
      (t1.getWinPercentage() == t2.getWinPercentage() && (t1.getNumGames() == t2.getNumGames()) && t1.getName() < t2.getName()))
    return true;
  return false;
}

bool sort_by_opponent_touchdowns(const Team &t1, const Team &t2) {
  if (t1.getAverageOpponentTouchdownsPerGame() < t2.getAverageOpponentTouchdownsPerGame() ||
      ((t1.getAverageOpponentTouchdownsPerGame() == t2.getAverageOpponentTouchdownsPerGame()) && 
       (t1.getName() < t2.getName())))
    return true;
  return false;
}


