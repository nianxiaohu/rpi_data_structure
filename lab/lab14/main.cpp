#include <iostream>
#include <assert.h>
#include <set>
using namespace std;
#include "memory.h"

// helper functions
void TEST_CPP_Memory();
void TEST_StopAndCopy_Memory();
void TEST_CPP_ErrorMessages();
void TEST_StopAndCopy_ErrorMessages();
void delete_all(CPP_Memory &m, Address &address);

// ==============================================================================

int main() {
  cout << "-------------------------------------------------------------------------------" << endl;
  TEST_CPP_Memory();
  cout << "-------------------------------------------------------------------------------" << endl;
  TEST_StopAndCopy_Memory();
  cout << "-------------------------------------------------------------------------------" << endl;
  TEST_CPP_ErrorMessages();
  TEST_StopAndCopy_ErrorMessages();
  cout << endl << "all testing complete" << endl;
}

// ==============================================================================

void TEST_CPP_Memory() {

  CPP_Memory m;
  cout << "TESTING CPP_Memory" << endl;
  cout << endl << "empty memory:" << endl << m;

  // a temporary variable to help with deletion
  Address tmp;

  // create an interesting data structure
  m.root = m.my_new('a',MY_NULL,MY_NULL);
  tmp = m.my_new('b',MY_NULL,m.root);
  m.my_delete(tmp); // explicit memory management
  m.root = m.my_new('c',m.root,MY_NULL);
  m[m.root].right = m.my_new('d',m[m.root].left,MY_NULL);
  m.root = m.my_new('e',MY_NULL,m.root);
  m[m.root].right = m.my_new('f',m[m.root].right,MY_NULL);
  m[m[m.root].right].right = m.my_new('g',m[m.root].right,MY_NULL);
  m.root = m.my_new('h',m.root,MY_NULL);
  tmp = m.root;
  m.root = m[m[m.root].left].right;
  m.my_delete(m[tmp].left); // explicit memory management
  m.my_delete(tmp);  // explicit memory management

  cout << endl << "8 cells allocated, 3 deleted:" << endl << m;

  // allocate 8 more cells
  char c = 'A';
  for (int i = 0; i < 8; i++,c++) {
    tmp = m.my_new(c,m.root,MY_NULL);
    if (i%2 == 0) m.my_delete(tmp);
    else m.root = tmp;
  }

  cout << endl  << "8 more cells allocated, 4 deleted:" << endl << m;

  // allocate another 7 cells
  for (int i = 0; i < 7; i++,c++) {
    tmp = m.my_new(c,m.root,MY_NULL);
    if (i%2 == 0) m.my_delete(tmp);
    else m.root = tmp;
  }

  cout << endl << "7 more cells allocated, 4 deleted:" << endl << m;

  // recursively delete everything accessible from root
  // UNCOMMENT TO TEST CHECKPOINT 3
  /*
  delete_all(m,m.root);
  cout << endl << "after recursive delete from root:" << endl << m;
  */
}

// ==============================================================================

void TEST_StopAndCopy_Memory() {

  StopAndCopy_Memory m;
  cout << "TESTING StopAndCopyMemory" << endl;
  cout << endl << "empty memory:" << endl << m;

  // create an interesting data structure
  m.root = m.my_new('a',MY_NULL,MY_NULL);
  m.my_new('b',MY_NULL,m.root);
  m.root = m.my_new('c',m.root,MY_NULL);
  m[m.root].right = m.my_new('d',m[m.root].left,MY_NULL);

  cout << endl << "4 cells allocated:" << endl << m;

  m.root = m.my_new('e',MY_NULL,m.root);
  m[m.root].right = m.my_new('f',m[m.root].right,MY_NULL);
  m[m[m.root].right].right = m.my_new('g',m[m.root].right,MY_NULL);
  m.root = m.my_new('h',m.root,MY_NULL);
  m.root = m[m[m.root].left].right;

  cout << endl << "8 cells allocated:" << endl << m;

  // force garbage collection
  m.collect_garbage();
  cout << endl << "after forced garbage collection:" << endl << m;

  // allocate more cells to force garbage collection
  m[m.root].left = m.my_new('i',m.root,MY_NULL);
  m.root = m.my_new('j',m.root,MY_NULL);
  m.root = m.my_new('k',m.root,MY_NULL);

  cout << endl << "after adding 3 more cells:" << endl << m;

  cout << "*** CHECKPOINT 1 HERE ***" << endl;

  // CHECKPOINT 1: Walk through the Stop And Copy garbage collection
  // algorithm on the memory at this point in the program.

  // UNCOMMENT THESE LINES AFTER YOU FINISH CHECKPOINT 1 (to check your work)
  /*
  m.root = m.my_new('l',m.root,MY_NULL);
  cout << endl << "adding another cell triggers automatic garbage collection:" << endl << m;

  // "forget" the root pointer
  m.root = MY_NULL;
  m.collect_garbage();
  cout << endl << "root set to null & forced garbage collection:" << endl << m;
  */
}

// ==============================================================================

void TEST_CPP_ErrorMessages() {

  // CHECKPOINT 2: write code to test the major memory error messages
  // in CPP_Memory

  // Note: Since each "test" will crash the program, you'll need to
  // comment them out once you verify they work

  CPP_Memory m;

  // [] NULL POINTER EXCEPTION


  // [] SEGMENTATION FAULT

  
  // my_delete SEGMENTATION FAULT


  // my_delete CANNOT DELETE MEMORY THAT IS NOT ALLOCATED




  // code that runs OUT_OF_MEMORY in CPP but not StopAndCopy




  // code that runs OUT_OF_MEMORY in both CPP and StopAndCopy



}

void TEST_StopAndCopy_ErrorMessages() {

  // CHECKPOINT 2: write code to test the major memory error messages
  // in StopAndCopy_Memory

  // Note: Since each "test" will crash the program, you'll need to
  // comment them out once you verify they work

  StopAndCopy_Memory m;

  // [] NULL POINTER EXCEPTION


  // [] SEGMENTATION FAULT

  
  // code that runs OUT_OF_MEMORY in CPP but not StopAndCopy




  // code that runs OUT_OF_MEMORY in both CPP and StopAndCopy



}

// ==============================================================================

void delete_all(CPP_Memory &m, Address &address) {

  // CHECKPOINT 3: delete all of the nodes accessible from address

  // NOTE: this function will use recursion, but is not trivial if the
  // data structure is cyclic!  You are allowed to use std::set.

  // Hint: You may want to write a helper function.





}

// ==============================================================================
