#include<list>
#include<iostream>

using namespace std;
void reverse( std::list<double>  &d)
{
  int size = d.size();
  std::list<double>::iterator fr = d.begin();
  std::list<double>::reverse_iterator ba = d.rbegin();
  for(int i=0; i<size/2;i++,fr++,ba++) {
    double temp;
    temp = *fr;
    *fr = *ba; 
    *ba = temp;
  }
}
void reverseSecond( std::list<double> &d) {
  if(d.size() >= 1)
    {
      double temp1=d.front();
      double temp2=d.back();
      d.pop_front();
      d.pop_back();
      reverseSecond(d);
      d.push_front(temp2);
      d.push_back(temp1);
    }

}

void print( std::list<double> &d ) {
  std::list<double>::iterator fr = d.begin();
  while( fr!=d.end())
    cout<< *fr++<<" ";
}
int main() {
  std::list<double> first;
  for ( unsigned int i=0; i<10; i++){
    first.push_back(double(i));
    cout << "push-back "<< first.back()<<endl;
  }
  print(first);
  cout << "Reverse " << endl;
  reverse(first);
  print(first);
  cout << "Reverse " << endl;
  reverseSecond(first);
  print(first);
}
