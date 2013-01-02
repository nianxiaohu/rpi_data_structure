#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include "jagged_array.h"

using namespace std;

//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN CHANGES TO MoreTests()
//

// helper testing functions
void SimpleTest();
void MoreTests();
void BatchTest(const char* filename, int num);

//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD CONTAIN NO CHANGES TO main()
//
int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTest();
    cout << "Simple test completed." << endl;
    MoreTests();
    cout << "More tests completed." << endl;    
  } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>" << endl;
      exit(1);
    }
    BatchTest(argv[1],atoi(argv[2]));
    cout << "Batch test completed." << endl;
  }
}


//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD CONTAIN NO CHANGES TO SimpleTest()
//
void SimpleTest() {

  JaggedArray<char> ja(7);

  assert (ja.numBins() == 7);
  assert (ja.numElements() == 0);
  assert (ja.isPacked() == false);

  // intialize the values in the JaggedArray
  ja.addElement(1,'a');
  ja.addElement(1,'b');
  ja.addElement(1,'c');
  ja.addElement(3,'d');
  ja.addElement(3,'e');
  ja.addElement(6,'f');

  // verify data is correct
  std::cout << "STARTS UNPACKED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // pack the structure and verify data is correct
  ja.pack();
  std::cout << "CONVERT TO PACKED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // unpack the structure and verify data is correct
  ja.unpack();
  std::cout << "CONVERT BACK TO UNPACKED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 2);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(6,0) == 'f');

  // add 'g' and verify
  ja.addElement(3,'g');
  std::cout << "ADDED G" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 7);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 3);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 3);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'b');
  assert (ja.getElement(1,2) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(3,2) == 'g');
  assert (ja.getElement(6,0) == 'f');

  // remove 'b' and verify
  ja.removeElement(1,1);
  std::cout << "REMOVED B" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 6);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 2);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 3);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 1);
  assert (ja.getElement(1,0) == 'a');
  assert (ja.getElement(1,1) == 'c');
  assert (ja.getElement(3,0) == 'd');
  assert (ja.getElement(3,1) == 'e');
  assert (ja.getElement(3,2) == 'g');
  assert (ja.getElement(6,0) == 'f');

  // clear
  ja.clear();
  std::cout << "CLEARED" << std::endl;
  ja.print();
  assert (ja.numBins() == 7);
  assert (ja.numElements() == 0);
  assert (ja.numElementsInBin(0) == 0);
  assert (ja.numElementsInBin(1) == 0);
  assert (ja.numElementsInBin(2) == 0);
  assert (ja.numElementsInBin(3) == 0);
  assert (ja.numElementsInBin(4) == 0);
  assert (ja.numElementsInBin(5) == 0);
  assert (ja.numElementsInBin(6) == 0);

  // note...  the JaggedArray destructor is implicitly called for the
  // variable 't' when we leave the function and it goes out of scope
}



//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN CHANGES TO MoreTests()
//
void MoreTests() {

  //
  // you should add your own test cases here.  
  // be sure to test:
  //   * jagged arrays that store types other than char
  //   * copy constructor
  //   * assignment operator
  //   * delete operator
  //

  // make sure it works with integer
  JaggedArray<int> a(5);
  a.addElement(1,10);
  a.addElement(4,5);
  a.addElement(3,888);
  a.addElement(1,64);
  a.addElement(4,2);
  a.addElement(0,333);
  assert (a.getElement(1,1) == 64);
  assert (a.numElements() == 6);
  a.print();
  std::cout << "integer test finished" << std::endl;

  // test the copy constructor
  JaggedArray<int> b(a);
  assert (b.numElements() == a.numElements());
  assert (b.numBins() == a.numBins());
  for (unsigned int i = 0; i < a.numBins(); i++) {
    assert (b.numElementsInBin(i) == a.numElementsInBin(i));
    for (unsigned int j = 0; j < a.numElementsInBin(i); j++) {
      assert (b.getElement(i,j) == a.getElement(i,j));
    }
  }
  b.print();
  std::cout << "copy constructor test finished" << std::endl;

  // test the assignment operator  
  JaggedArray<int> c(12);
  c.addElement(3,16);
  c.addElement(9,25);
  c.addElement(1,64);
  c.addElement(0,355);
  c.addElement(3,9);
  assert (c.numBins() == 12);
  c.print();
  c = a;
  assert (c.numElements() == a.numElements());
  assert (c.numBins() == a.numBins());
  for (unsigned int i = 0; i < a.numBins(); i++) {
    assert (c.numElementsInBin(i) == a.numElementsInBin(i));
    for (unsigned int j = 0; j < a.numElementsInBin(i); j++) {
      assert (c.getElement(i,j) == a.getElement(i,j));
    }
  }
  c.print();
  std::cout << "assignment operator test finished" << std::endl;

  // verify edits happen to the right object
  b.clear();
  assert (b.numElements() == 0);
  assert (a.numElements() == 6);
  assert (a.numBins() == 5);
  assert (b.numBins() == 5);
  a.removeElement(0,0);
  assert (c.numElements() == a.numElements()+1);
  assert (c.numBins() == a.numBins());
  assert (c.numElementsInBin(0) == a.numElementsInBin(0)+1);
  c.addElement(3,16);
  assert (c.numElements() == a.numElements()+2);
  assert (c.numElementsInBin(3) == a.numElementsInBin(3)+1);
  std::cout << "edits happen to the correct operator test finished" << std::endl;

  JaggedArray<string> d(3);
  d.addElement(2,"hi");
  d.addElement(1,"hello");
  d.addElement(2,"bye");
  d.addElement(0,"up");
  d.addElement(1,"down");
  d.addElement(2,"in");
  d.addElement(2,"out");
  assert (d.numBins() == 3);
  assert (d.numElements() == 7);
  assert (d.numElementsInBin(0) == 1);
  assert (d.numElementsInBin(1) == 2);
  assert (d.numElementsInBin(2) == 4);
  assert (d.getElement(0,0) == "up");
  assert (d.getElement(1,0) == "hello");
  assert (d.getElement(1,1) == "down");
  assert (d.getElement(2,0) == "hi");
  assert (d.getElement(2,1) == "bye");
  assert (d.getElement(2,2) == "in");
  assert (d.getElement(2,3) == "out");
  d.print();
  std::cout << "string test finished" << std::endl;

  d.pack();
  assert (d.isPacked());
  d.print();
  JaggedArray<string> e(d);
  assert (e.isPacked());
  e.print();
  assert (e.numBins() == 3);
  assert (e.numElements() == 7);
  assert (e.numElementsInBin(0) == 1);
  assert (e.numElementsInBin(1) == 2);
  assert (e.numElementsInBin(2) == 4);
  assert (e.getElement(0,0) == "up");
  assert (e.getElement(1,0) == "hello");
  assert (e.getElement(1,1) == "down");
  assert (e.getElement(2,0) == "hi");
  assert (e.getElement(2,1) == "bye");
  assert (e.getElement(2,2) == "in");
  assert (e.getElement(2,3) == "out");  
  e.print();
  std::cout << "packed copy constructor tested" << std::endl;

  a.pack();
  assert (a.isPacked());
  b = a;
  assert (b.isPacked());
  assert (b.numElements() == a.numElements());
  assert (b.numBins() == a.numBins());
  for (unsigned int i = 0; i < a.numBins(); i++) {
    assert (b.numElementsInBin(i) == a.numElementsInBin(i));
    for (unsigned int j = 0; j < a.numElementsInBin(i); j++) {
      assert (b.getElement(i,j) == a.getElement(i,j));
    }
  }
  b.print();
  std::cout << "packed assignment operator tested" << std::endl;

  JaggedArray<double> f(3);
  f.addElement(2,3.14);
  f.addElement(1,1.57);
  f.addElement(0,0.33333);
  f.addElement(1,6.02);
  f.print();
  std::cout << "tested with double" << std::endl;
}



//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD NOT CONTAIN CHANGES TO BatchTest()
//

// Batch test will repeatedly load & process a file with JaggedArray
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char* filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << endl;
      exit(1);
    }

    string token;
    char c;
    int b,i;

    // create the initial JaggedArray
    istr >> token >> b;
    assert (token == "create");
    // note: here we explicitly allocate memory for the JaggedArray object
    JaggedArray<char> *ja = new JaggedArray<char>(b);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "addElement") {
        istr >> b >> c;
        ja->addElement(b,c);
      } else if (token == "getElement") {
        istr >> b >> i >> c;
        char c2 = ja->getElement(b,i);
        assert (c == c2);
      } else if (token == "removeElement") {
        istr >> b >> i >> c;
	char c2 = ja->getElement(b,i);
        assert (c == c2);
	ja->removeElement(b,i);
      } else if (token == "pack") {
        ja->pack();
      } else if (token == "unpack") {
        ja->unpack();
      } else if (token == "clear") {
        ja->clear();
      } else {
        std::cerr << "ERROR: unknown token " << token << endl;
        exit(1);
      }
    }

    // print out the jagged array contents at the end of the last iteration
    if (iters == 0) {
      if (ja->isPacked()) {
	ja->unpack();
      }
      ja->print();
      ja->pack();
      ja->print();
    }

    // Because the JaggedArray memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete ja;
  }

}


