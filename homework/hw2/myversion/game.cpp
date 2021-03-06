
#include "game.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
// Constructors
GameScore::GameScore(const std::string &n, int s1, int s2, int s3, int s4, int s5){
  name = n;
  scores = std::vector<int>(5,0); /// constructor 
  scores[0]=s1;
  scores[1]=s2;
  scores[3]=s3;
  scores[4]=s4;
  scores[5]=s5;
  total = s1+s2+s3+s4+s5;
  safeties = 0;
  _6_pt_touchdowns = 0;
  _7_pt_touchdowns = 0;
  _8_pt_touchdowns = 0;
  field_goals = 0;
  for ( int i=0; i< 5; i++) {
    bool success = ProcessScore( scores[i]);
    if (!success) { std::cout << "Process Score failure" << scores[i] << std::endl;
      assert(success);
    }
  }
}
bool GameScore::ProcessScore( int score)
{
  if ( score == 0 ) return true;
  if ( score == 1) return false;
  if ( score == 2 ) { safeties++; return true;}
  if ( score == 4) { safeties++; safeties++; return true;}
  if ( score == 8 ) { _8_pt_touchdowns++; return true;}
  // if the score can be only explained by only 7 point touchdowns
  if (score % 7 == 0){
    _7_pt_touchdowns += score/7;
    return true;
  }
  // if the score can be explained by one 6 point touchdowns and 0 or more touch
  if ( (score -6) %7 ==0){
    _6_pt_touchdowns++;
   return ProcessScore(score-6);
  }
  assert( score >= 3);
  field_goals++;
  return ProcessScore(score-3);
}
Game::Game(const Date &d, const GameScore& visitor, const GameScore& home):
  visitor_score(visitor),home_score(home),date(d) { }
// helper function for sorting games
bool sort_by_differential( const Game &g1, const Game &g2) {
  int absDif1 = abs(g1.getVisitorScore().getTotal()- g1.getHomeScore().getTotal());
  int absDif2 = abs(g2.getVisitorScore().getTotal()- g2.getHomeScore().getTotal());
  int total1 = g1.getVisitorScore().getTotal()+ g1.getHomeScore().getTotal();
  int total2 = g2.getVisitorScore().getTotal()- g2.getHomeScore().getTotal();
  std::string visitor1 = g1.getVisitorScore().getName();
  std::string visitor2 = g2.getVisitorScore().getName();
  std::string home1 = g1.getHomeScore().getName();
  std::string home2 = g2.getHomeScore().getName();

  if ( absDif1 != absDif2)
    return ( absDif1 < absDif2);
  if (total1 != total2)
    return ( total1 > total2);
  if (visitor1 != visitor2)
    return ( visitor1 < visitor2);
  return home1 < home2;
}
