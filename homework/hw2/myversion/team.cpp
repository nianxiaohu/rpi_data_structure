#include "team.h"
#include <cassert>
#include <iostream>
double Team::getWinPercentage() const {
  assert( games.size()>0);
  return getWins()/double(games.size());
}
int Team::getWins() const {
  int wins=0;
  for ( unsigned int i=0;i<games.size();i++)
    {
      if ( name == games[i].getHomeScore().getName())
	{
	  if( games[i].getHomeScore().getTotal() > games[i].getVisitorScore().getTotal())
	    wins++;
	}
      else 
	{
	  if ( games[i].getHomeScore().getTotal() < games[i].getVisitorScore().getTotal())
	    wins++;
	}
    }
  return wins;
}
int Team::getLosses() const {
  return games.size()-getWins();
}
double Team::getAverageOpponentTouchdownsPerGame() const{

  return getTotalOpponentTouchdowns()/(double)games.size();
}

int Team::getTotalOpponentTouchdowns() const {
  int totals = 0;
  for ( unsigned int i=0;i<games.size(); i++)
    {
      if ( name == games[i].getHomeScore().getName())
	totals+= games[i].getVisitorScore().getNumTouchdowns();
      else
	totals+= games[i].getHomeScore().getNumTouchdowns();
    }
  return totals;
}

int Team::getTotalOpponentFieldGoals() const {
  int totals = 0;
  for ( unsigned int i=0;i<games.size(); i++)
    {
      if ( name == games[i].getHomeScore().getName())
	totals+= games[i].getVisitorScore().getNumFieldGoals();
      else
	totals+= games[i].getHomeScore().getNumFieldGoals();
    }
  return totals;
}
// helper functions for sorting teams
bool sort_by_wins( const Team &t1, const Team &t2) {
  double p1 = t1.getWinPercentage();
  double p2 = t2.getWinPercentage();
  if (p1 != p2 )
    return p1>p2;
  if (t1.getNumGames() != t2.getNumGames())
    return t1.getNumGames()>t2.getNumGames();
  return t1.getName()<t2.getName();
}

bool sort_by_opponent_touchdowns( const Team &t1, const Team &t2) {
  if ( t1.getAverageOpponentTouchdownsPerGame() != t2.getAverageOpponentTouchdownsPerGame())
    return t1.getAverageOpponentTouchdownsPerGame()< t2.getAverageOpponentTouchdownsPerGame();
  return t1.getName()< t2.getName();
}
