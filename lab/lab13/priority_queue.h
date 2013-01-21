#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
using namespace std;


template <class T>
class priority_queue {
private:
  vector<T> m_heap;
public:
  priority_queue() {}

  priority_queue( vector<T> const& values )
  {/*
    int i = 0;
    for ( i=0; i<values.size(); i++ ) {
      push(values[i]);
      }*/
    m_heap = values;
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry);
    int i = m_heap.size();
    i = i-1;
    while( i >= 1 && m_heap[i] < m_heap[(i-1)/2] ) {
      int temp = m_heap[(i-1)/2];
      m_heap[(i-1)/2] = m_heap[i];
      m_heap[i] = temp;
      i = (i-1)/2;
    }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    T temp = m_heap.back();
    m_heap[0] = temp;// copy the last element to the root of the heap and pop back
    m_heap.pop_back();
    this->percolate_down();
  }
  void percolate_down() {
    int i = 0;
    int size = m_heap.size();
    while ( i <= (size-2)/2 - 1  && ( m_heap[i] > m_heap[2*i+1] || m_heap[i] > m_heap[2*i+2] )) {
      if ( m_heap[2*i+1] < m_heap[2*i+2] ) {
	T temp = m_heap[2*i+1];
	m_heap[2*i+1] = m_heap[i];
	m_heap[i] = temp;
	i = 2*i + 1;
      }
      else {
	T temp = m_heap[2*i+2];
	m_heap[2*i+2] = m_heap[i];
	m_heap[i] = temp;
	i = 2*i + 2;
      }
    }
    if ( i == ( size-2 )/2 ) {
      if ( size%2 == 0 && m_heap[i] >  m_heap[size-1] ) {
	T temp = m_heap[i];
	m_heap[i] = m_heap[size-1];
	m_heap[size-1] = temp;
      }
      if ( size%2 != 0 && (m_heap[i] > m_heap[size-1] || m_heap[i] > m_heap[size-2]) ) {
	if ( m_heap[size-1] < m_heap[size-2] ) {
	  T temp = m_heap[size-1];
	  m_heap[size-1] = m_heap[i];
	  m_heap[i] = temp;
	}
	else {
	  T temp = m_heap[size-2];
	  m_heap[size-2] = m_heap[i];
	  m_heap[i] = temp;
	}	
      }
    } 
  }
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an extrernal vector to see that the heap property is realized.
  bool check_heap( const vector<T>& heap )
  {
    // empty heap is heap
    int size = heap.size();
    if ( size  == 0)
      return true;
    if ( size  == 1)
      return true;
    for ( int i=0; i<=(size-2)/2-1; i++ ) { // check up to the last internal node with children 
      int left = 2*i + 1;
      int right = 2*i + 2;
      if ( heap[i] > heap[left] || heap[i] > heap[right] )
	return false;
    }
    // if size is even
    if ( size%2 == 0 && heap[(size-2)/2] <= heap[size-1] ) {
      return true;
    }
    // if size is odd
    if ( size%2 != 0 && heap[(size-2)/2] <= heap[size-1] && heap[(size-2)/2] <= heap[size-2] ) {
      return true;
    }
    return false;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << endl;
  }
  
};


template <class T>
void heap_sort( vector<T> & v )
{
}

#endif
