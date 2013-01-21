#include <assert.h>
#include "memory.h"

// ==============================================================================
Node& Memory::operator[](Address addr) { 
  // Return the node corresponding to a particular address
  if (addr == MY_NULL) {
    std::cerr << "ERROR: NULL POINTER EXCEPTION!" << endl; exit(1); }
  if (addr < OFFSET || addr >= OFFSET+CAPACITY) {
    cerr << "ERROR: SEGMENTATION FAULT!" << endl; exit(1); }
  return memory[addr-OFFSET]; 
}

ostream& operator<<(ostream &ostr, Memory &m) {
  ostr << "root-> " << m.root << endl;
  for (int i = 0; i < CAPACITY; i++) {
    ostr.width(4); ostr << i+OFFSET << " "; }
  ostr << endl;
  for (int i = 0; i < CAPACITY; i++) {
    ostr << "   "; ostr.width(1); ostr << m.memory[i].value << " "; }
  ostr << endl;
  for (int i = 0; i < CAPACITY; i++) {
    ostr.width(4); ostr << m.memory[i].left << " "; }
  ostr << endl;
  for (int i = 0; i < CAPACITY; i++) {
    ostr.width(4); ostr << m.memory[i].right << " "; }
  ostr << endl;
  m.print_availability(ostr);
  return ostr;
}

// ==============================================================================
Address CPP_Memory::my_new(char v, Address l, Address r) {
  // starting at next, walk through the memory to find the first
  // available address.  If we walk in a circle, we're out of memory.
  for (int i=0; i < CAPACITY; i++, next++) {
    next %= CAPACITY;
    if (available[next] == true) {
      available[next] = false;
      memory[next].value = v;
      memory[next].left = l;
      memory[next].right = r;
      return OFFSET + next++;
    }
  }
  cerr << "ERROR: OUT OF MEMORY!" << endl; exit(1);
}

void CPP_Memory::my_delete(Address addr) {
  // makes a node available for re-use
  if (addr == MY_NULL) return;  // deleting a NULL pointer is not an error in C++
  if (addr < OFFSET || addr >= OFFSET+CAPACITY) {
    cerr << "ERROR: SEGMENTATION FAULT!" << endl; exit(1); }
  if (available[addr-OFFSET] == true) {
    cerr << "ERROR: CANNOT DELETE MEMORY THAT IS NOT ALLOCATED!" << endl; exit(1); }
  available[addr-OFFSET] = true;
}

void CPP_Memory::print_availability(ostream &ostr) {
  // print "FREE" or "used" for each node
  for (int i = 0; i < CAPACITY; i++) {
    (available[i]) ? ostr << "FREE " : ostr << "used "; }
  ostr << endl;
}

// ==============================================================================
Address StopAndCopy_Memory::my_new(char v, Address l, Address r) {
  // if we are out of memory, collect garbage
  if (next == partition_offset+CAPACITY/2) { 
    collect_garbage(); 
    // update the addresses (since memory has been shuffled!)
    if (l != MY_NULL) l = memory[l-OFFSET].left;
    if (r != MY_NULL) r = memory[r-OFFSET].left;
  }
  // if we are still out of memory, we can't continue
  if (next == partition_offset+CAPACITY/2) { 
    cerr << "ERROR: OUT OF MEMORY!" << endl; exit(1); }
  // assign the next available node
  memory[next].value = v;
  memory[next].left = l;
  memory[next].right = r;
  return OFFSET + next++;
}
 
void StopAndCopy_Memory::print_availability(ostream &ostr) {
  // print "FREE" or "used" for each node in the current partition
  for (int i = 0; i < CAPACITY; i++) {
    if (i >= next && i < partition_offset+CAPACITY/2)
      ostr << "FREE ";
    else if (i >= partition_offset && i < partition_offset+CAPACITY/2)
      ostr << "used ";
    else  // print nothing for the other half of memory
      ostr << "     "; }
  ostr << endl;
}    

void StopAndCopy_Memory::collect_garbage() {
  // switch to the other partition
  partition_offset = (partition_offset == 0) ? CAPACITY/2 : 0;
  // scan & next start at the beginning of the new partition
  Address scan;
  next = scan = partition_offset;
  // copy the root
  copy_help(root);
  // scan through the newly copied nodes
  while (scan != next) {
    // copy the left & right pointers
    copy_help(memory[scan].left);
    copy_help(memory[scan].right);
    scan++;
  }
}

void StopAndCopy_Memory::copy_help(Address &old) {
  // do nothing for NULL Address
  if (old == MY_NULL) return;
  // look for a valid forwarding address to the new partition
  int forward = memory[old-OFFSET].left;
  if (forward-OFFSET >= partition_offset &&
      forward-OFFSET < partition_offset+CAPACITY/2) {
    // if already copied, change pointer to new address
    old = forward;
    return;
  } 
  // otherwise copy it to a free slot and leave a forwarding address
  memory[next] = memory[old-OFFSET];
  memory[old-OFFSET].left = next+OFFSET;
  old = next+OFFSET;
  next++;
}
