#include<iostream>
#include<string>

using namespace std;
void permulate(string);
int main() {
  string str;
  str = "Happy";
  permulate(str);
}
void permulate( string str) {
  if ( str.size() == 0)
    return;
  if ( str.size() == 1)
    cout << str[0];
 
}
