#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

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
  int countt = 1;
  bool smallCase = false;
  while ( countt <= caseNumber) {
    unsigned int n = 0;
    unsigned int k = 0;
    unsigned int a = 0;unsigned int b = 0; unsigned int c = 0; unsigned int r = 0;
    inputFileStream >> n >> k >> a >> b >> c >> r;
    unsigned int* position = new unsigned int[k];
    unsigned int* count = new unsigned int[k];
    bool* array = new bool[k];
    assert(array);
    assert(position);
    assert(count);
    unsigned int i;
    for ( i=0; i<k; i++) {
      array[i] = false;
      count[i] = 0;
    }
    unsigned int value = a;
    for (i = 0; i<k; i++) {
      position[i] = value;
      if ( value > k-1) {;}
      else {
	array[value] = true;
	count[value]++;
      }
      value = (value*b + c)%r;
    }
    unsigned int progress = k;
    unsigned int output = 0;
    unsigned int index=0;
    while ( progress < 2*k ) {
      for ( i= 0; i<k; i++) {
	if (!array[i]) {
	  output = i;
	  break;
	}
      }
      if (i==k){
	output = k;
      }
      if (position[index%k] < k) {
	count[position[index%k]]--;
	if ( count[position[index%k]] <= 0)
	  array[position[index%k]] = false;
      }
      position[index%k] = output;
      if (output < k) {
	array[output] = true;
       count[output]++;
      }
      if (n == progress+1) {
	cout << "case #" << countt <<  ":  "<< output << endl;
	smallCase = true;
	break;
      }
      progress++;
      index++;
   }
    int key = (n-1-k)%k;
    if (!smallCase) {
      if (key==0)
	cout << "case #" << countt <<  ":  "<< k << endl;
      else
	cout << "case #" << countt <<  ":  "<< position[key-1] << endl;
    }
    countt++;
    delete [] array;
    delete [] position;
    delete [] count;
    smallCase = false;
  }
}
