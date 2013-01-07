#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
template <class T> void mergesort(vector<T>& values);
template <class T> void mergesort(int low, int high, vector<T>& values, vector<T>& scratch);
template <class T> void merge(int low, int mid, int high, vector<T>& values, vector<T>& scratch);
int main() {
  vector<double> pts(7);
  pts[0] = -45.0;
  pts[1] = 89.0;
  pts[2] = 34.7;
  pts[3] = 21.1;
  pts[4] = 5.0;
  pts[5] = -19.0;
  pts[6] = -100.3;
  mergesort(pts);
  for (unsigned int i=0; i<pts.size(); ++i)
    cout << i << ": " << pts[i] << endl;
}
// The driver function for mergesort. It defines a scratch vector for temporary copies.
template <class T>
void mergesort(vector<T>& values) {
  vector<T> scratch(values.size());
  mergesort(0, int(values.size()-1), values, scratch);
}
// Here’s the actual merge sort function. It splits the vector in
// half, recursively sorts each half, and then merges the two sorted
// halves into a single sorted interval.
template <class T>
void mergesort(int low, int high, vector<T>& values, vector<T>& scratch) {
  cout << "mergesort: low = " << low << ", high = " << high << endl;
  if (low >= high) // intervals of size 0 or 1 are already sorted!
    return;
  int mid = (low + high) / 2;
  mergesort(low, mid, values, scratch);
  mergesort(mid+1, high, values, scratch);
  merge(low, mid, high, values, scratch);
}
// Non-recursive function to merge two sorted intervals (low..mid & mid+1..high)
// of a vector, using "scratch" as temporary copying space.
template <class T>
void merge(int low, int mid, int high, vector<T>& values, vector<T>& scratch) {
  cout << "merge: low = " << low << ", mid = " << mid << ", high = " << high << endl;
  for ( unsigned int i = low; i<= high ; i++ )
    scratch[i] = values[i];
  int i=low, j=mid+1, k= low;
  while( i< mid+1 && j<high+1) {
    if ( scratch[i] <= scratch[j]) {
      values[k] = scratch[i] ;
      k++;
      i++;
    }
    else {
      values[k] = scratch[j];
      k++;
      j++;
    }
  }
    if ( i < mid+1 ) {
      while ( i < mid+1) {
	values[k] = scratch[i];
	i++;
	k++;
      }
      return;
    }
    if ( j < high+1 ) {
      while ( j < high+1 ) {
	values[k] = scratch[j];
	j++;
	k++;
      }
      return;
    }
    exit(1);
}
