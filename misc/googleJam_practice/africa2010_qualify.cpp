#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<string>
using namespace std;

class item {
public:
  item(int p=0, int l=0) : price(p), location(l) {}
  int price;
  int location;
};
bool lessThan(const item & a, const item & b) {
  return a.price < b.price ;
}
/*bool operator==(const item &a, const item &b) {
  return (a.price==b.price) && (a.location==b.location);
  }*/
int main(int argc, char ** argv) {
  string fileName= argv[1];
  ifstream input(fileName.c_str());
  int caseN;
  input >> caseN;
  input.get();
  int count = 1;
  while(count <= caseN) {
    int output1 =0;
    int output2 = 0;
    int credit;
    int numberItem;
    input >> credit >> numberItem;
    int i = 0;
    vector<item> vec(numberItem+1);
    while ( i < numberItem) {
      item temp;
      input >> temp.price;
      temp.location = i+1;
      vec[i] = temp;
      i++;
    }
    item temp1;
    temp1.price = credit/2;
    temp1.location = numberItem+1;
    vec[i] = temp1;
    sort(vec.begin(),vec.end(),lessThan);
    vector<item>::iterator itr=vec.begin();
    while ( itr != vec.end()) {
      if ( itr->price ==  temp1.price && itr->location == temp1.location ) {
	break;
      }
      itr++;
    }
    itr++;
    vector<item>::iterator itLeft = vec.begin();
    while ( (itr->price + itLeft->price) != credit ) {
      if ( (itr->price + itLeft->price ) < credit ) {
	itr++;
      } else {
	itLeft++;
      }
    }
    output1 = min(itr->location,itLeft->location);
    output2 = max(itr->location,itLeft->location);
    cout << "Case #" << count << ": " << output1 << " " << output2 << endl;
    count++;
    vec.~vector();
  }
}
