#include<iostream>
#include<string>
#include<list>
#include<fstream>
using namespace std;

bool determine(list<char>&,list<char>::iterator&, int);

int main(int argc, char ** argv) {
  if ( argc != 2) {
    cerr << "USAGE:programName  FILE" << endl;
  }

  string fileName= argv[1];
  ifstream inputFileStream(fileName.c_str());
  int caseNumber = 0;
  if ( !inputFileStream ) {
    cerr <<"Could not open input file " << fileName << endl;
    return 1;
  }
  inputFileStream >> caseNumber;
  inputFileStream.get();
  int count = 1;
  while ( count <= caseNumber) {
    string str="";
    getline(inputFileStream, str);
    list<char> li;
    int size = str.size();
    int i=0;
    bool output = true;
    while(i<size){
      if(str[i] == ':' && (str[i+1] == ')' || str[i+1] == '(')) {
	li.push_back(str[i]);
	li.push_back(str[i+1]);
	i++;
	i++;
      }
      else {
	if(str[i] == '(' || str[i] == ')') {
	  li.push_back(str[i]);
	  i++;
	}
	else {
	if ( str[i] == ' ' || str[i] == ':' || (std::isalpha(str[i])&&std::islower(str[i]))) {
	  i++;
	}
	else {
	  output = false;
	  break;
	}
	}
      }
    }
    if ( output == false) {
      cout << "case #" << count <<  ":  NO" << endl;
      count++;
      continue;
    }
    // recursive determine the list's correctness
    list<char>::iterator itr = li.begin();
    int left = 0;
    output = determine(li,itr,left); 
    if(output)
      cout << "case #" << count <<  ":  YES" << endl;
    else
      cout << "case #" << count <<  ":  NO" << endl;
    count++;                                          
  }
}


bool determine(list<char>& li, list<char>::iterator& itr, int left) {
  if (itr==li.end() && left == 0) 
    return true;
  if ( left < 0 )
    return false;
  if ( itr != li.end() ) {
    if(*itr == ':') {
      // you can have two cases either treat : as smiley or just treat : as colon
      // treat as colon
      list<char>::iterator temp(itr);
      itr++;
      bool a1 = determine(li,itr,left);
      temp++;
      temp++;
      // treat as smiley
      bool a2= determine(li, temp,left);
      return a1 || a2;
    } else if (*itr == ')') {
      itr++;
      return determine(li, itr, left-1);
    } else if (*itr == '(') {
      itr++;
      return determine(li, itr, left+1);
    }
  }
}
