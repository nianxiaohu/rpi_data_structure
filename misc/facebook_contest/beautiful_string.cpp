#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int main(int argc, char** argv) {
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
     string str = "";
     getline(inputFileStream, str);
     vector<int> vec(26,0);
     unsigned int size = str.size();
     int i = 0;
     while(i<size) {
       if (std::isalpha(str[i])){
	 if(std::isupper(str[i]))
	   vec[str[i]-65]++;
	 else 
	   vec[str[i]-97]++;
       }
       i++;
     }
     std::sort(vec.begin(),vec.end());
     vector<int>::iterator itr=vec.end();
     itr--;
     int output =0;
     int weight = 26;
     while(itr != vec.begin()){
       output +=(*itr) * weight;
       weight--;
       itr--;
    }
     cout << "case #" << count <<  ":  "<< output << endl;
     count++;
   }
}


