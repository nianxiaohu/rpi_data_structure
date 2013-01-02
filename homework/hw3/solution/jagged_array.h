#ifndef _JaggedArray_h_
#define _JaggedArray_h_

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cmath>

// A templated class to store a collection of elements in bins as a
// jagged array, in either unpacked or packed structure.

template <class T> 
class JaggedArray {

public:   
  typedef unsigned int size_type;

  // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
  // constructor w/ integer argument (unpacked): O(b)
  // constructor w/ integer argument (packed): N/A
  JaggedArray(size_type n) { this->create(n); }
  // copy constructor (unpacked): O(b+e)
  // copy constructor (packed): O(b+e)
  JaggedArray(const JaggedArray& ja) { copy(ja); }
  JaggedArray& operator=(const JaggedArray& ja); 
  // destructor (unpacked): O(b+e)
  // destructor (packed): O(b+e)
  ~JaggedArray() { destroy(); } 

  // ACCESSORS
  bool isPacked() const;
  // numElements (unpacked): O(1)
  // numElements (packed): O(1)
  size_type numElements() const { return num_elements; }
  // numBins (unpacked): O(1)
  // numBins (packed): O(1)
  size_type numBins() const { return num_bins; }
  size_type numElementsInBin(size_type b) const;
  const T& getElement(size_type b, size_type i) const;
  
  // MODIFIERS
  void addElement(size_type b, const T& v);
  void removeElement(size_type b, size_type i);
  void clear();

  // SWITCH REPRESENTATIONS
  void pack();
  void unpack();

  // OUTPUT 
  void print() const;
  int maxEntryWidth() const;
  
private:  

  // PRIVATE MEMBER FUNCTIONS
  void create(size_type n);
  void destroy();
  void copy(const JaggedArray<T>& t); 
  size_type numElementsInBinFromOffsets(size_type b) const;
  
  // REPRESENTATION
  size_type num_elements;
  size_type num_bins;
  size_type* counts;
  size_type* offsets;
  T** unpacked_values;
  T* packed_values;
};

// ==============================================================

// HELPER FUCTION FOR CONSTRUCTOR
// create an empty JaggedArray
// create (unpacked): O(b)
// create (packed): N/A
template <class T>  void JaggedArray<T>::create(size_type n) {
  if (n <= 1) {
    std::cerr << "ERROR: size must be >= 1" << std::endl;
    exit(1);
  }
  num_bins = n;
  num_elements = 0;
  // always start out unpacked
  unpacked_values = new T*[num_bins];
  counts = new size_type[num_bins];
  // initialize each bin as empty (no elements)
  for (unsigned int i = 0; i < num_bins; i++) {
    unpacked_values[i] = NULL;
    counts[i] = 0;
  }
  offsets = NULL;
  packed_values = NULL;
}


// HELPER FUCNTION FOR DESTRUCTOR & ASSIGNMENT OPERATOR
// cleanup all memory 
// destroy (unpacked): O(b+e)
// destroy (packed): O(b+e)
template <class T> void JaggedArray<T>::destroy() {
  if (isPacked()) {
    assert (unpacked_values == NULL);
    assert (counts == NULL);
    assert (packed_values != NULL);
    assert (offsets != NULL);
    delete [] offsets;    
    delete [] packed_values;
  } else {
    assert (packed_values == NULL);
    assert (offsets == NULL);
    assert (unpacked_values != NULL);
    assert (counts != NULL);
    for (unsigned int i = 0; i < num_bins; i++) {
      delete [] unpacked_values[i];
    }
    delete [] unpacked_values; 
    delete [] counts;
  }
}


// ASSIGNMENT OPERATOR
// assignment operator (unpacked): O(b+e)
// assignment operator (packed): O(b+e)
template <class T> JaggedArray<T>& JaggedArray<T>::operator=(const JaggedArray<T>& v) {
  // check for self-assignment
  if (this != &v) {
    destroy();
    this->copy(v);
  }
  return *this;
}


// HELPER FUNCTION FOR COPY CONSTRUCTOR & ASSIGNMENT OPERATOR
// copy (unpacked): O(b+e)
// copy (packed): O(b+e)
template <class T> void JaggedArray<T>::copy(const JaggedArray<T>& v) {
  num_bins = v.num_bins;
  num_elements = v.num_elements;
  if (v.isPacked()) {
    // if it's a packed structure
    offsets = new size_type[num_bins];
    packed_values = new T[num_elements];
    for (unsigned int b = 0; b < num_bins; b++) {
      offsets[b] = v.offsets[b];
    }
    for (unsigned int i = 0; i < num_elements; i++) {
      packed_values[i] = v.packed_values[i];
    }
    counts = NULL;
    unpacked_values = NULL;
  } else {
    // if it's an unpacked structure
    counts = new size_type[num_bins];
    unpacked_values = new T*[num_bins];
    for (unsigned int b = 0; b < num_bins; b++) {
      counts[b] = v.counts[b];
      unpacked_values[b] = new T[counts[b]];
      for (unsigned int i = 0; i < counts[b]; i++) {
	unpacked_values[b][i] = v.unpacked_values[b][i];
      }
    }
    offsets = NULL;
    packed_values = NULL;
  }
}

// ==============================================================
// ACCESSORS

// isPacked (unpacked):  O(1)
// isPacked (packed):  O(1)
template <class T> bool JaggedArray<T>::isPacked() const { 
  assert ((unpacked_values == NULL && packed_values != NULL) ||
	  (unpacked_values != NULL && packed_values == NULL));
  return (unpacked_values == NULL); 
}

// numElementsInBin (unpacked): O(1)
// numElementsInBin (packed): O(1)
template <class T> 
typename JaggedArray<T>::size_type JaggedArray<T>::numElementsInBin(size_type b) const {
  if (b < 0 || b >= num_bins) {
    std::cerr << "ERROR: invalid bin index" << std::endl;
    exit(1);
  }
  if (!isPacked()) {
    return counts[b];
  } else {
    return numElementsInBinFromOffsets(b);
  }
}

// helper function
// numElementsInBinFromOffsets (unpacked): O(1)
// numElementsInBinFromOffsets (packed): O(1)
template <class T> 
typename JaggedArray<T>::size_type JaggedArray<T>::numElementsInBinFromOffsets(size_type b) const {
  if (b < 0 || b >= num_bins) {
    std::cerr << "ERROR: invalid bin index" << std::endl;
    exit(1);
  }
  assert (offsets != NULL);
  int max = (b != num_bins-1) ? offsets[b+1] : num_elements;
  return max - offsets[b];
}


// getElement (unpacked): O(1)
// getElement (packed): O(1)
template <class T> const T& JaggedArray<T>::getElement(size_type b, size_type i) const {
  if (b < 0 || b >= num_bins) {
    std::cerr << "ERROR: invalid bin index" << std::endl;
    exit(1);
  }
  if (i < 0 || i >= numElementsInBin(b)) {
    std::cerr << "ERROR: invalid element index" << std::endl;
    exit(1);
  }
  if (!isPacked()) {
    return unpacked_values[b][i];
  } else {
    return packed_values[offsets[b]+i];
  }
}


// ==============================================================
// MODIFIERS

// addElement (unpacked): O(k)
// addElement (packed): N/A
template <class T> void JaggedArray<T>::addElement(size_type b, const T& t) {
  if (isPacked()) {
    std::cerr << "ERROR: cannot addElement to a packed JaggedArray" << std::endl;
    exit(1);
  }
  if (b < 0 || b >= num_bins) {
    std::cerr << "ERROR: invalid bin index" << std::endl;
    exit(1);
  }
  if (counts[b] == 0) {
    assert (unpacked_values[b] == NULL);
    unpacked_values[b] = new T[1];
    unpacked_values[b][0] = t;
  } else {
    T* tmp = new T[counts[b]+1];
    for (unsigned int i = 0; i < counts[b]; i++) {
      tmp[i] = unpacked_values[b][i];
    }
    tmp[counts[b]] = t;
    delete [] unpacked_values[b];
    unpacked_values[b] = tmp;
  }
  counts[b]++;
  num_elements++;
}

// removeElement (unpacked): O(k)
// removeElement (packed): N/A
template <class T> void JaggedArray<T>::removeElement(size_type b, size_type i) {
  // verify legal element
  if (isPacked()) {
    std::cerr << "ERROR: cannot removeElement from a packed JaggedArray" << std::endl;
    exit(1);
  }
  if (b < 0 || b >= num_bins) {
    std::cerr << "ERROR: invalid bin index" << std::endl;
    exit(1);
  }
  if (i < 0 || i >= numElementsInBin(b)) {
    std::cerr << "ERROR: invalid element index" << std::endl;
    exit(1);
  }
  if (counts[b] == 1) {
    delete [] unpacked_values[b];
    unpacked_values[b] = NULL;
  } else {
    T* tmp = new T[counts[b]-1];
    for (unsigned int j = 0; j < i; j++) {
      tmp[j] = unpacked_values[b][j];
    }
    for (unsigned int j = i+1; j < counts[b]; j++) {
      tmp[j-1] = unpacked_values[b][j];
    }
    delete [] unpacked_values[b];
    unpacked_values[b] = tmp;
  }
  counts[b]--;
  num_elements--;
}


// clear (unpacked): O(e)
// clear (packed): N/A
template <class T> void JaggedArray<T>::clear() {
  // verify legal element
  if (isPacked()) {
    std::cerr << "ERROR: cannot clear a packed JaggedArray" << std::endl;
    exit(1);
  }
  for (unsigned int b = 0; b < num_bins; b++) {
    delete [] unpacked_values[b];
    unpacked_values[b] = NULL;
    counts[b] = 0;    
  }
  num_elements = 0;
}

// ==============================================================
// pack (unpacked): O(b+e)
// pack (packed): N/A
template <class T> void JaggedArray<T>::pack() {
  if (isPacked()) {
    std::cerr << "ERROR: cannot pack a packed JaggedArray" << std::endl;
    exit(1);
  }
  // sanity check, count the elements
  unsigned int count_check = 0;
  for (unsigned int b = 0; b < num_bins; b++) {
    count_check += counts[b];
  }
  assert (num_elements == count_check);
  // prepare the packed version
  packed_values = new T[num_elements];
  offsets = new size_type[num_bins];
  unsigned int j = 0;
  for (unsigned int b = 0; b < num_bins; b++) {
    offsets[b] = j;
    for (unsigned int i = 0; i < counts[b]; i++) {
      packed_values[j] = unpacked_values[b][i];
      j++;
    }
    delete [] unpacked_values[b];
  }
  // cleanup the unpacked version
  delete [] unpacked_values;
  unpacked_values = NULL;
  delete [] counts;
  counts = NULL;
}

// unpack (unpacked): N/A
// unpack (packed): O(b+e)
template <class T> void JaggedArray<T>::unpack() {
  if (!isPacked()) {
    std::cerr << "ERROR: cannot unpack an unpacked JaggedArray" << std::endl;
    exit(1);
  }
  // prepare the unpacked version
  unpacked_values = new T*[num_bins];
  counts = new size_type[num_bins];
  int j = 0;
  for (unsigned int b = 0; b < num_bins; b++) {
    counts[b] = numElementsInBinFromOffsets(b);
    if (counts[b] == 0) {
      unpacked_values[b] = NULL;
      counts[b] = 0;
    } else {
      unpacked_values[b] = new T[counts[b]];
      for (unsigned int i = 0; i < counts[b]; i++) {
	unpacked_values[b][i] = packed_values[j];
	j++;
      }
    }
  }
  // cleanup the packed version
  delete [] packed_values;
  packed_values = NULL;
  delete [] offsets;
  offsets = NULL;
}


// ==============================================================
// print (unpacked): O(b*k)
// print (packed): O(b*k)
template <class T> void JaggedArray<T>::print() const {
  if (isPacked()) {
    std::cout << "packed JaggedArray\n  num_bins: " << num_bins << "\n  num_elements: " << num_elements << std::endl;
    std::cout << "  offsets: ";
    for (unsigned int b = 0; b < num_bins; b++) {
      std::cout << " " << offsets[b];
    }
    std::cout << std::endl;
    std::cout << "  values:  ";
    for (unsigned int i = 0; i < num_elements; i++) {
      std::cout << " " << packed_values[i];
    }
    std::cout << std::endl;
  } else {
    std::cout << "unpacked JaggedArray\n  num_bins: " << num_bins << "\n  num_elements: " << num_elements << std::endl;
    // find the biggest count of elements
    unsigned int max = 1;
    for (unsigned int b = 0; b < num_bins; b++) {
      if (counts[b] > max) max = counts[b];
    }
    // calculate the width for each column of the table
    int digits = std::max((int)ceil(log10(max+1)),maxEntryWidth());
    // print the table
    std::cout << "  counts: ";
    for (unsigned int b = 0; b < num_bins; b++) {
      std::cout << " " << std::setw(digits) << counts[b];
    }
    std::cout << std::endl;
    for (unsigned int i = 0; i < max; i++) {
      if (i == 0)
	std::cout << "  values: ";
      else
	std::cout << "          ";
      for (unsigned int b = 0; b < num_bins; b++) {
	if (i < counts[b]) {
	  std::cout << " " << std::setw(digits) << unpacked_values[b][i];
	} else {
	  std::cout << " " << std::setw(digits) << " ";
	}
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}


// MAX ENTRY WIDTH: SPECIALIZATION FOR CHAR
template <>
int JaggedArray<char>::maxEntryWidth() const {
  return 1;
}

// MAX ENTRY WIDTH: SPECIALIZATION FOR STRING
template <>
int JaggedArray<std::string>::maxEntryWidth() const {
  int answer = 1;
  for (unsigned int b = 0; b < numBins(); b++) {
    for (unsigned int i = 0; i < numElementsInBin(b); i++) {
      answer = std::max(answer, (int)getElement(b,i).length());
    }
  }
  return answer;
}

// MAX ENTRY WIDTH: SPECIALIZATION FOR INT
template <>
int JaggedArray<int>::maxEntryWidth() const {
  int answer = 1;
  for (unsigned int b = 0; b < numBins(); b++) {
    for (unsigned int i = 0; i < numElementsInBin(b); i++) {
      int tmp = 1;
      int value = getElement(b,i);
      if (value < 0) 
	tmp = log10((float)(-value)) + 2;
      else 
	tmp = log10((float)value) + 1;
      answer = std::max(answer, tmp);
    }
  }
  return answer;
}

// MAX ENTRY WIDTH: ANY OTHER TYPE
template <class T> int JaggedArray<T>::maxEntryWidth() const {
  return 10;
}


#endif
