#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

#include "game.h"
#include "team.h"

// ==================================================================
// This function reads football game data from a file in a strictly
// specified format.  

void read_data(std::vector<Game> &games, std::ifstream &in_str) {
  std::string weekday, month, visitor_name, home_name;
  int day, year, v1,v2,v3,v4,v5,vtotal,h1,h2,h3,h4,h5,htotal;

  // loop while there is still good data
  while (1) {

    // read in the date
    if (!(in_str >> weekday >> month >> day >> year))
      break;
    Date date(month,day,year);

    // read in the scores
    in_str >> visitor_name >> v1 >> v2 >> v3 >> v4 >> v5 >> vtotal;
    in_str >> home_name >> h1 >> h2 >> h3 >> h4 >> h5 >> htotal;
    GameScore visitor(visitor_name,v1,v2,v3,v4,v5);
    GameScore home(home_name,h1,h2,h3,h4,h5);
    
    // build the Game object and add to master list
    Game game(date,visitor,home);
    assert (vtotal == game.getVisitorScore().getTotal());
    assert (htotal == game.getHomeScore().getTotal());
    games.push_back(game);
  }
}


// ==================================================================
// This function makes a list of all the teams that played at least
// one games, and collects all the games for each team.
void gather_team_stats(const std::vector<Game> &games, std::vector<Team> &teams) {
  for (unsigned int i = 0; i < games.size(); i++) {
    int v_found = false;
    int h_found = false;
    // loop over all the teams, to see if this team already has an entry
    for (unsigned int j = 0; j < teams.size(); j++) {
      if (games[i].getVisitorScore().getName() == teams[j].getName()) {
	teams[j].addGame(games[i]);
	v_found = true;
      }
      if (games[i].getHomeScore().getName() == teams[j].getName()) {
	teams[j].addGame(games[i]);
	h_found = true;
      }
    }
    // add the teams if they haven't been seen befgameore
    if (!v_found) {
      Team t(games[i].getVisitorScore().getName());
      t.addGame(games[i]);
      teams.push_back(t);
    }
    if (!h_found) {
      Team t(games[i].getHomeScore().getName());
      t.addGame(games[i]);
      teams.push_back(t);
    }
  }
}


// ==================================================================
// The main function does the argument parsing and issues commands for
// loading, sorting, and printing the data.

int main(int argc, char* argv[]) {

  // check the number of arguments
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <in-file> <out-file>\n";
    return 1;
  }
  // open and test the input file
  std::ifstream in_str(argv[1]);
  if (!in_str) {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // open and test the output file
  std::ofstream out_str(argv[2]);
  if (!out_str) {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // ===============================================
  // read in all the data  
  std::vector<Game> games;
  read_data(games,in_str);
  // organize data for teams
  std::vector<Team> teams;
  gather_team_stats(games,teams);

  // calculate the longest team name
  int max_name_width = 0;
  for (unsigned int i = 0; i < teams.size(); i++) {
    max_name_width = std::max(max_name_width,(int)teams[i].getName().length());
  }

  // print out the tables
  out_str << "ALL GAMES, SORTED BY POINT DIFFERENTIAL:" << std::endl;
  std::sort(games.begin(),games.end(),sort_by_differential);
  for (unsigned int i = 0; i < games.size(); i++) {
    std::string name1 = games[i].getVisitorScore().getName();
    std::string name2 = games[i].getHomeScore().getName();
    int score1 = games[i].getVisitorScore().getTotal();
    int score2 = games[i].getHomeScore().getTotal();
    out_str << std::setw(max_name_width) << std::left << name1 << "  ";
    if (score1 > score2) {
      out_str << "defeated  ";
    } else {
      out_str << "lost to   ";
    }
    out_str << std::setw(max_name_width) << std::left << name2 << "  " 
	    << std::right 
	    << std::setw(2) << std::fixed << std::setprecision(2) << score1 << " - "
 	    << std::setw(2) << std::fixed << std::setprecision(2) << score2
	    << std::endl;
  }
  
  out_str << "\nALL TEAMS, SORTED BY WIN PERCENTAGE:" << std::endl;
  std::sort(teams.begin(),teams.end(),sort_by_wins);
  for (unsigned int i = 0; i < teams.size(); i++) {
    std::string name = teams[i].getName();
    out_str << std::setw(max_name_width) << std::left << name 
	    << "  " << std::right << std::setw(2) << teams[i].getWins() << " win(s)" 
	    << " - " << std::setw(2) << teams[i].getLosses() << " loss(es)"
	    << "  " << std::setw(4) << std::fixed << std::setprecision(2) << teams[i].getWinPercentage() 
	    << std::endl;
  }

  // ===============================================
  // creative new statistic

  // out_str << "\nYOUR CREATIVE STATISTIC GOES HERE" << std::endl;

  // sample statistic
  out_str << "\nALL TEAMS, SORTED BY AVERAGE OPPONENT TOUCHDOWNS PER GAME:" << std::endl;
  std::sort(teams.begin(),teams.end(),sort_by_opponent_touchdowns);
  for (unsigned int i = 0; i < teams.size(); i++) {
    std::string name = teams[i].getName();
    out_str << std::setw(max_name_width) << std::left << name 
	    << " " << std::setw(3) << std::right << teams[i].getTotalOpponentTouchdowns() << " touchdown(s)" 
	    << " in " << std::setw(2) << std::right << teams[i].getNumGames() << " game(s)"
	    << "  " << std::setw(4) << std::fixed << std::setprecision(2) << teams[i].getAverageOpponentTouchdownsPerGame() << std::endl;
  }
}

