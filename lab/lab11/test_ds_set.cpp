#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"
using namespace std;
int main() {

  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!
  string str = "";
  set1.accumulate(str);
  cout << str <<endl;
  assert(set1.sanity_check());
  assert (set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find( "foo" );
  assert (p == set1.end());

  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
	    << "The indentation is proportional to the depth of the node\n"
	    << "so that the value stored at the root is the only value printed\n"
	    << "without indentation.  Also, for each node, the right subtree\n"
	    << "can be found above where the node is printed and indented\n"
	    << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;


  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  

  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);


  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);


  // Test the iterators!
  ds_set<int> set3;
  int a[] ={8,4,12,2,6,10,14,1,3,5,7,9,11,13,15};// this insertion will create a balanced tree 
  for ( int i=0; i<15;i++ ) {
    set3.insert(a[i]);
  }
  assert(set3.size() == 15);
  assert(*(set3.begin()) == 1);
  ds_set<int>::iterator itr = ++(set3.begin()); // increase before the assignment 
  assert(*itr == 2);
  set3.erase(1);
  assert( *(set3.begin()) == 2);
  set3.insert(1);
  set3.print_as_sideways_tree( std::cout );
  ds_set<int>::iterator it = set3.end();
  --it;
  assert( *it == 15 );
  int initial = 0;
  set3.accumulate(initial);
  cout << initial << endl;







  return 0;
}
