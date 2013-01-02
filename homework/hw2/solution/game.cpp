#include "game.h"
#include <cassert>
#include <iostream>
#include <cstdlib>

// ============================================
// CONSTRUCTOR

GameScore::GameScore(const std::string& n, int s1, int s2, int s3, int s4, int s5) {
  name = n;
  scores = std::vector<int>(5,0);
  scores[0] = s1;
  scores[1] = s2;
  scores[2] = s3;
  scores[3] = s4;
  scores[4] = s5;
  total = s1+s2+s3+s4+s5;
  safeties = 0;
  field_goals = 0;
  _6_pt_touchdowns = 0;
  _7_pt_touchdowns = 0;
  _8_pt_touchdowns = 0;
  for (int i = 0; i < 5; i++) {    
    bool success = ProcessScore(scores[i]);
    if (!success) { std::cout << "process score failure " << scores[i] << std::endl; }
    assert (success);
  }
}

bool GameScore::ProcessScore(int score) {
  // simple base cases
  if (score == 0) return true;
  if (score == 1) return false;
  if (score == 2) { safeties++; return true; }
  if (score == 4) { safeties+=2; return true; }
  if (score == 8) { _8_pt_touchdowns++; return true; }
  
  // if the score can be explained by only 7 point touchdowns
  if (score % 7 == 0) {
    _7_pt_touchdowns += score / 7; 
    return true; 
  }

  // if the score can be explained by one 6 point touchdown 
  // & 0 or more 7 point touchdowns
  if ((score-6) % 7 == 0) {
    _6_pt_touchdowns ++;
    _7_pt_touchdowns += (score-6) / 7; 
    return true; 
  }

  // otherwise, subtract off a field goal and recurse
  assert (score >= 3);
  field_goals++; 
  return ProcessScore(score-3);
}


// ============================================

// CONSTRUCTOR
Game::Game(const Date &d, const GameScore& visitor, const GameScore& home) :
  visitor_score(visitor), home_score(home) {
  date = d;
}



// helper function for sorting games
bool sort_by_differential(const Game &g1, const Game &g2) {
  int diff1 = abs(g1.getVisitorScore().getTotal() - g1.getHomeScore().getTotal());
  int diff2 = abs(g2.getVisitorScore().getTotal() - g2.getHomeScore().getTotal());
  int total1 = g1.getVisitorScore().getTotal() + g1.getHomeScore().getTotal();
  int total2 = g2.getVisitorScore().getTotal() + g2.getHomeScore().getTotal();
  
  std::string visitor1 = g1.getVisitorScore().getName();
  std::string visitor2 = g2.getVisitorScore().getName();
  std::string home1 = g1.getHomeScore().getName();
  std::string home2 = g2.getHomeScore().getName();
  
  if (diff1 < diff2 ||
      (diff1 == diff2 && total1 > total2) ||
      (diff1 == diff2 && total1 == total2 && visitor1 < visitor2) ||
      (diff1 == diff2 && total1 == total2 && visitor1 == visitor2 && home1 < home2)) 
    return true;
  return false;
}



