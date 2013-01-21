#include <iostream>
using namespace std;
#define CAPACITY 16 // size of memory available for this process
#define OFFSET 100  // first valid address for this process
#define MY_NULL 0
typedef int Address;

// ==============================================================================
class Node {
public:
  Node() { value='?'; left=-1; right=-1; } // initialized with "garbage" values
  char value;
  Address left;
  Address right;
};

// ==============================================================================
class Memory {
public:
  Memory() { root = MY_NULL; }

  // Return the node corresponding to a particular address
  Node& operator[](Address addr);  
  // allocate a new node
  virtual Address my_new(char value, Address l, Address r) = 0;
  // print the contents of memory
  friend ostream& operator<<(ostream &ostr, Memory &m);
  virtual void print_availability(ostream &ostr) = 0;

  // the user must set this value such that all useful memory is
  // reachable starting from root  (NOTE: publicly accessible)
  Address root;   
protected:
  Node memory[CAPACITY];   // total machine memory
};

// ==============================================================================
class CPP_Memory : public Memory {
public:
  CPP_Memory() {
    for (int i=0; i < CAPACITY; i++) 
      available[i] = true; 
    next = 0; }
  Address my_new(char v, Address l, Address r);
  void my_delete(Address addr);  // explicit memory management
  void print_availability(ostream &ostr);
protected:
  bool available[CAPACITY];  // which cells have been allocated
  int next;   // where to start looking for the next available node
};

// ==============================================================================
class StopAndCopy_Memory : public Memory {
public:
  StopAndCopy_Memory() {
    partition_offset = 0;
    next = 0; }
  Address my_new(char v, Address l, Address r);
  void collect_garbage();  // automatic memory management
  void print_availability(ostream &ostr);
protected:
  void copy_help(Address &old_address);
  int partition_offset;  // which half of the memory is active
  int next;   // next available node
};
