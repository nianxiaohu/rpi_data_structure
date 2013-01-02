#ifndef _JaggedArray_h_
#define _JaggedArray_h_



template <class T>
class JaggedArray {
  private:
  int num_elements;
  int num_bins;
  int* offsets;
  T* packed_values;
  int* counts;
  T** unpacked_values;//pitfall 1
  //private memeber functions
  void create(int n);
  void destroy();
  void copy( const JaggedArray<T>& t);
  int numElementsInBinFromOffsets( int b ) const;

 public:
  //constructor
  JaggedArray();
  JaggedArray(int i){ this->create(n);}
  //copy constructor
  JaggedArray(const JaggedArray& ja) { copy(ja);}
  //assignment operator
  JaggedArray& operator=( const JaggedArray& ja);
  //destructor
  ~JaggedArray() {destroy();}
  //accessor
  int numBins() const { return num_bins;}
  int numElements() const { return num_elements;}
  int numElementsInBin(const int& i) const;
  T& getElement(const int& i, const int& j) const;
  bool isPacked() const;

  //modifiers
  void addElement(int b, const T& v);
  void removeElement( int b, int i);
  void clear();
  //output
  void print();
  int maxEntryWidth() const;
  //switch presentation
  void pack();
  void unpack();

};

template <class T> void JaggedArray<T>::create(int n) {
  num_bins = n;
  num_elements = 0;
  // starts out as unpacked
  offsets = NULL;
  packed_values = NULL;
  unpacked_values = new T*[n];
  counts = new int[n];
  for( unsigned int i=0;i<n;i++)
    {
      counts[i]=0;
      unpacked_values[i] = NULL;
    }
}

}
template <class T> void JaggedArray<T>::destroy() {
  // for offsets and counts and packed_values
  delete [] offsets;
  delete [] counts;
  delete [] packed_values;
  //for unpacked_values
  if (!isPacked())
    {
      //      assert(packed_values == NULL);
      //   assert(offsets == NULL);
      //   assert(unpacked_values !=NULL);
      for ( unsigned int i=0;i<num_bins;i++)
	delete [] unpacked_values[i];
      delete [] unpacked_values;
    }
}
template <class T> void JaggedArray<T>::copy(const JaggedArray<T> &t) {
  // determine whether t is packed or unpacked then clean this object and deep copy
  //copy constructor is to create a new oject with existing object
  // for copy constructor there is no need to see if it is being initialized from itself and there is no need to clean up( delete) an existing value, because there is none. A reference to itself is not returned.
  num_elements = t.numElements();
  num_bins = t.numBins();
  if ( t.isPacked())
    {
      offsets = new int[num_bins];
      packed_values = new T[num_elements];
      for ( unsigned int i=0; i<num_elements;i++)
	packed_values[i]=t.packed_values[i];
      for ( unsigned int j=0; j<num_bins;j++)
	offsets[j]=t.offsets[j];
      counts = NULL;
      unpacked_values = NULL;
    }
  else
    {
      counts = new int[num_bins];
      unpacked_values = new T*[num_bins];
      offsets = NULL;
      packed_values = NULL;
      for ( unsigned int i=0; i<num_bins;i++)
	{
	  // counts[i]=t.numElementsInBin(i);
	  counts[i]=t.counts[i];
	  if (counts[i] == 0)
	    unpacked_values[i]=NULL;
	  else
	    {
	    unpacked_values[i]= new T[counts[i]];
	    for ( unsigned int j=0;j<counts[i];j++)
	      {
		//addElement(i,t.getElement(i,j));
		unpacked_values[i][j] = t.unpacked_values[i][j];
	      }
	    }
	}
    }
}
// assignment operator
template <class T> JaggedArray<T>& JaggedArray<T>::operator=( const JaggedArray<T> &ja) {
  // check self-assignment
  if( this != &ja){
    destroy();
    this->copy(v);
  }
  return *this;
}


// accessor
  template <class T> bool JaggedArray<T>::isPacked() const {
    if ( counts == NULL)
      return true;
    else
      return false;
  }
  template <class T> int JaggedArray<T>::numElementsInBin( const int& i) const {
    if ( i<0 || b>=num_bins) {
      std::cerr << "ERROR: invalid bin index"<< std::endl;
      exit(1);
    }
    if ( isPacked())
      {
	assert(offsets!=NULL);
	if ( i==num_bins-1)
	  return num_elements-offsets[i];
	else
	  return offsets[i+1]-offsets[i];
      }
    else
      {
	assert(counts !=NULL);
	return counts[i];
      }
  }
template <class T> T& JaggedArray<T>::getElement(const int &i, const int &j) {
  if (i<0||i>=num_bins) {
    std::cerr <<"ERROR: Invalid bin index" << std::endl;
    exit(1);
  }
  if ( j<0 || j >= numElementsInBin(i)) {
    std::cerr << "ERROR: invalid element index" << std::endl;
    exit(1);
  }
  if ( isPacked())
    {
      /* unsigned sumToi=0;
      for ( unsigned int b=0;b<i;b++)
	{
	  sumToi+=numElementsInBin(b);
	}
      return packed_values[sumToi+j];
      */
      return packed_values[offsets[b]+i];
    }
  else
    {
      assert(unpacked_values !=NULL);
      return unpacked_values[i][j];
    }
}
// MODIFIERS
template <class T> void JaggedArray<T>::addElement(int b, const T &v) {
  if ( b<0 || b>=num_bins){
    std::cerr << "ERROR: invalid bin index" << std::endl;
    exit(1);
  }
  if ( isPacked() )
    {
      std::cerr << "ERROR: cannot add element to packed array" << std::endl;
      exit(1);
    }
  if ( counts[b] == 0 )
    {
      assert( unpacked_values[b] == NULL);
      unpacked_values[b] = new T[1];
      unpacked_values[b][0]=v;
    }
  else {
    unsigned int i;
    T* newBin = new T[counts[b] + 1];
    for ( i=0;i<counts[b];i++){
      newBin[i]=unpacked_values[b][i];
    }
    newBin[i]=v;
    delete [] unpacked_values[b];
    unpacked_values[b] = newBin;// pitfall newBin is a pointer to array of T
  }
  num_elements++;
  counts[b]++;
}

template <class T> void JaggedArray<T>::removeElement(int b, int i) {
  if ( b<0 || b>=num_bins){
    std::cerr << "ERROR: invalid bin index" << std::endl;
    exit(1);
  }
 if ( i<0 || i >= numElementsInBin(b)) {
    std::cerr << "ERROR: invalid element index" << std::endl;
    exit(1);
  }
 if ( isPacked())
   {
     std::cerr << "ERROR: cannot remove element from packed data structure" << std::endl;
     exit(1);
   }
 // if the number of elements in bin b is only one, then we need to 
 if(counts[b]==1)
   {
     delete [] unpacked_values[b];
     unpacked_values[b] = NULL;
     // assert(unpacked_values[b] == NULL);
   }
 else
   {
     unsigned int j=0;
     T* temp = new T[counts[b]-1];
     for ( j=0; j<counts[b]-1;j++)
       {
	 if (j<i)
	   temp[j] = unpacked_values[b][j];
	 else
	   temp[j] = unpacked_values[b][j+1];
       }
     delete [] unpacked_values[b];
     unpacked_values[b] = temp;

   }
 counts[b] = counts[b] -1;
 num_elements--;
}
template <class T> void JaggedArray<T>::clear() {
 if ( isPacked())
   {
     std::cerr << "ERROR: cannot remove element from packed data structure" << std::endl;
     exit(1);
   }
 for ( unsigned int i=0; i<num_bins;i++) {
   if ( counts[i] != 0)
     {
       delete [] unpacked_values[i];
     }
   unpacked_values[i] = NULL;
   counts[i] = 0;
 }
 num_elements = 0;
}
template <class T> void JaggedArray<T>::pack() {
  if ( isPacked() )
    return;
  offsets = new int[num_bins];
  packed_values = new T[num_elements];
  unsigned int j = 0;
  for ( unsigned int i=0; i< num_bins; i++) {
    unsigned int k = counts[i];
    unsigned int s = 0;
    while ( s<k ) {
      packed_values[j] = unpacked_values[i][s];
      s++;
      j++;
    }
    if ( i==0 )
      offsets[i] = 0;
    else
      offsets[i] = offsets[i-1] + counts[i-1];
    delete [] unpacked_values[i];
    unpacked_values[i] = NULL;
  }
  delete [] counts;
  counts = NULL;

}

template <class T> void JaggedArray<T>::unpack() {
  if ( !isPacked())
    return;
  counts = new int[num_bins];
  unpacked_values = new T*[num_bins];
  unsigned int j = 0;
  for ( unsigned int i=0; i<num_bins; i++) {
    unsigned int k = numElementsInBin(i);
    counts[i] = k;
    if ( k != 0) {
      unpacked_values[i] = new T[k];
      unsigned int s = 0;
      while ( s < k ) {
	unpacked_values[i][s] = packed_values[j];
	j++;
      }
    }
    else
      unpacked_values[i] = NULL;
  }
  delete [] packed_values;
  packed_values = NULL;
  delete [] offsets;
}
template <class T> void JaggedArray<T>::print() {
  if(isPacked())
    {
      std::cout << "packed JaggedArray" << std::endl;
      std::cout << "  num_bins: " << num_bins << std::endl;
      std::cout << "  num_elements: " << num_elements << std::endl;
      std::cout << "  counts: ";
      for ( unsigned int i = 0; i<num_bins; i++)
	std::cout <<" "<<counts[i];
      std::cout << std::endl;
      std::cout << "  values:  ";
    }
  else
    {
      std::cout << "unpacked JaggedArray" << std::endl;

    }

}
