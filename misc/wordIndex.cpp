// Given a text file, generate an alphabetical listing of the words in the file
// and the file line numbers on which each word appears. If a word appears on
// a line more than once, the line number is listed only once.
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
// implementation omitted, will be covered in a later lecture
vector<string> breakup_line_into_strings(const string& line);
int main() {
  map<string, vector<int> > words_to_lines;
  string line;
  int line_number = 0;
  while (getline(cin, line)) {
    line_number++;
    // Break the string up into words
    vector<string> words = breakup_line_into_strings(line);
    // Find if each word is already in the map.
    for (vector<string>::iterator p = words.begin(); p!= words.end(); ++p) {
      // If not, create a new entry with an empty vector (default) and
      // add to index to the end of the vector
      map<string, vector<int> >::iterator map_itr = words_to_lines.find(*p);
      if (map_itr == words_to_lines.end())
	words_to_lines[*p].push_back(line_number); // could use insert here
      // If it is, check the last entry to see if the line number is
      // already there. If not, add it to the back of the vector.
      else if (map_itr->second.back() != line_number)
	map_itr->second.push_back(line_number);
    }
  }
  // Output each word on a single line, followed by the line numbers.
  map<string, vector<int> >::iterator map_itr;
  for (map_itr = words_to_lines.begin(); map_itr != words_to_lines.end(); map_itr++) {
    cout << map_itr->first << ":\t";
    for (unsigned int i = 0; i < map_itr->second.size(); ++i)
      cout << (map_itr->second)[ i ] << " ";
    cout << "\n";
  }
  return 0;
}
