/* 12.6
   Exercise: Complete the implementation
   Program: word_search
   Author: Chuck Stewart
   Purpose: A program to solve the word search problem where the
   letters in the word do not need to appear along a straight
   line. Instead, they can twist and turn. The only requirements are
   two-fold: the consecutive letters must be "8-connected" to each
   other (meaning that the locations must touch along an edge or at a
   corner), and no location may be used more than once.
   The real issue is how to search for the letters and then record
   locations as we search. This is most easily done with a recursive
   function. This function will be written during lecture.
   The input is from an input file. The grid is a series of strings,
   ended by a string that begins with ’-’. Each subsequent string in
   the file is used to search the input.
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Simple class to record the grid location.
class loc {
public:
  loc(int r=0, int c=0) : row(r), col(c) {}
  int row, col;
};
bool operator== (const loc& lhs, const loc& rhs) {
  return lhs.row == rhs.row && lhs.col == rhs.col;
}
// Prototype for the main search function
bool search_from_loc(loc position, const vector<string>& board, const string& word, vector<loc>& path);
// Read in the letter grid, the words to search and print the results
int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0]  << " Column#" << " Row#"<< endl;
    return 1;
  }
  int column = 0;
  int row = 0;
  column = atoi(argv[1]);
  row = atoi(argv[2]);


  //  bool ** board;
 /* board = new bool*[column];
  for ( unsigned int i=0; i<column;i++) {
    board[i] = new bool[row];
    for ( unsigned int j=0; j<row; j++ ) {
      board[i][j] = false;
    }
  }
*/
  int number_path =0;// save the number of path from the start to end
  findPath(column,row,number_path);

  vector<loc> path;
  string line;
  //The sequence of locations...
  // Input of grid from a file. Stops when character ’-’ is reached.
  while ((istr >> line) && line[0] != ’-’)
    board.push_back(line);
  while (istr >> word) {
    bool found = false;
    vector<loc> path; 


    /* Path of locations in finding the word
       Check all grid locations. For any that have the first
       letter of the word, call the function search_from_loc
       to check if the rest of the word is there.
    */

    for (unsigned int r=0; r<board.size() && !found; ++r)
      for (unsigned int c=0; c<board[r].size() && !found; ++c) {
	if (board[r][c] == word[0] &&
	    search_from_loc(loc(r,c), board, word, path))
	  found = true;
      }
    // Output results
    cout << "\n** " << word << " ** ";
    if (found) {
      cout << "was found. The path is \n";
      for(unsigned int i=0; i<path.size(); ++i)
	cout << " " << word[i] << ": (" << path[i].row << "," << path[i].col << ")\n";
    } else {
      cout << " was not found\n";
    }
  }
  return 0;
}
// helper function to check if a position has already been used for this word
bool on_path(loc position, vector<loc> const& path) {
  for (unsigned int i=0; i<path.size(); ++i)
    if (position == path[i]) return true;
  return false;
}
bool search_from_loc(loc position, // current position
		     const vector<string>& board,
		     const string& word,
		     vector<loc>& path) // path up to the current pos
{
  
  
}
