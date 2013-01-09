#ifndef MULTILL_H_
#define MULTILL_H_

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Node.h"
#include "list_iterator.h"
#include "MersenneTwister.h"
using namespace std;
template <class T>
class MultiLL {
  public:
    MultiLL() : chrono_head_(NULL), chrono_tail_(NULL), sorted_head_(NULL), sorted_tail_(NULL), random_head_(NULL), size_(0) { }
    MultiLL(const MultiLL<T>& old) { this->copy_list(old); }
    ~MultiLL() { this->destroy_list(); }
    MultiLL& operator= (const MultiLL<T>& old);

    unsigned int size() const { return size_; }
    bool empty() const { return chrono_head_ == NULL; }
    void clear() { this->destroy_list(); }

    typedef list_iterator<T> iterator;
    void add(const T &value);
    iterator erase(iterator itr);
    // iterator insert(iterator itr, T const& v);
    iterator begin_chronological() { return iterator( chrono_head_, chrono_ ); }
    iterator begin_sorted() { return iterator( sorted_head_, sorted_ ); }
    iterator begin_random();// { return iterator( random_head_, random_ ); }
    iterator end_chronological() { return iterator(chrono_); }
    iterator end_sorted() { return iterator(sorted_); }

  private:
    void copy_list(MultiLL<T> const &old);
    void destroy_list();

    // -- REPRESENTATION -- \\
    
    // chronological (insertion) ordering
    Node<T>* chrono_head_;
    Node<T>* chrono_tail_;

    // sorted (alphabetic) ordering
    Node<T>* sorted_head_;
    Node<T>* sorted_tail_;

    // random ordering
    Node<T>* random_head_;

    // number of nodes in the list
    unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::begin_random() {
  // use MersenneTwister to create a random number
  assert(size_ > 0);
  if ( size_ == 0 )
    return iterator(random_);
  // there is only one element in the list
  if ( size_ == 1) {
    random_head_ = chrono_head_;
    random_head_ -> random_next_ = random_head_;
  } else {
    // there are more than one elements in the list
    
    // set up the random_head_ 
    MTRand random_number;
    unsigned int i =  random_number.randInt(size_);
    cout << i<<endl;
    int j = 0;
    int leftOver = size_;
    Node<T>* temp = chrono_head_;
    i--;
    while ( j < i ) {
      temp = temp->chrono_next_;
    }
    random_head_ = temp;
    --leftOver;
    Node<T>* current = random_head_;
    for ( unsigned int i = 0; i < size_-1 ; i++ , leftOver-- ) {
      MTRand random_number;
      unsigned int index =  random_number.randInt(leftOver);
      // find the right pointer to the node
      iterator itr(chrono_head_, chrono_);
      unsigned int g = 0;
      while ( g < index ) {
	if ( itr.ptr_->random_next_ == NULL ) {
	  g++;
	}
	else {
	  ;
	}
	++itr;
      }
      current->random_next_ = itr.ptr_;
      current = itr.ptr_;
    }
    current->random_next_ = random_head_;
  }
}

template <class T> 
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;

  // save an iterator to the next node to return
  iterator temp(itr);
  temp++;

  // One node left in the list.  
  if (itr.ptr_ == chrono_head_ && chrono_head_ == chrono_tail_) {
    chrono_head_ = chrono_tail_ = NULL;
  } else { // more than one node in the list 
    // Take care of chronical section
    if (itr.ptr_ == chrono_head_) {
      chrono_head_ = chrono_head_ -> chrono_next_;
      chrono_head_ -> chrono_prev_ = NULL;
    } else if (itr.ptr_ == chrono_tail_) {
      chrono_tail_ = chrono_tail_ -> chrono_prev_;
      chrono_tail_ -> chrono_next_ = NULL;
    } else { 
      itr.ptr_ -> chrono_prev_ -> chrono_next_ = itr.ptr_ -> chrono_next_;
      itr.ptr_ -> chrono_next_ -> chrono_prev_ = itr.ptr_ -> chrono_prev_;
    }
  }

  // Take care of the sorted section
  if (itr.ptr_ == sorted_head_ && sorted_head_ == sorted_tail_) {
    sorted_head_ = sorted_tail_ = NULL;
  } else {
    if (itr.ptr_ == sorted_head_) {
      sorted_head_ = sorted_head_ -> sorted_next_;
      sorted_head_ -> sorted_prev_ = NULL;
    } else if (itr.ptr_ == sorted_tail_) {
      sorted_tail_ = sorted_tail_ -> sorted_prev_;
      sorted_tail_ -> sorted_next_ = NULL;
    } else { // easy case -- just fix links
      itr.ptr_ -> sorted_prev_ -> sorted_next_ = itr.ptr_ -> sorted_next_;
      itr.ptr_ -> sorted_next_ -> sorted_prev_ = itr.ptr_ -> sorted_prev_;
    }
  }
  
  // Take care of the random
  if (itr.ptr_ == random_head_) {
    random_head_ = random_head_ -> random_next_;
  } else { 
    // random is singly-linked -- it's not as easy
    /*
      iterator present = iterator(random_head_, random_);
      iterator next = present->next;    
      for( ; next.ptr_ != itr.ptr_; next++,present++ )
      ;    
      present.ptr_ -> random_next_ = next.ptr_ -> random_next_;
      itr.ptr_ -> chrono_next_ -> chrono_prev_ = itr.ptr_ -> chrono_prev_;
    */
    
    Node<T> *present, *next;
    present = random_head_;
    next = present->random_next_;  
    for ( ; next != itr.ptr_; present = next, next = next->random_next_)
      ; // ride along until you get one before the node you want to remove
    present->random_next_ = next->random_next_;
  } 
  delete itr.ptr_;
  return temp;
}

template <class T>
void MultiLL<T>::add(const T &value) {
  Node<T>* node = new Node<T>(value);
  if ( size_ == 0 ) {
    chrono_head_ = node;
    chrono_tail_ = node;
    sorted_head_ = node;
    sorted_tail_ = node;
    ++size_;
    return;
  } else {
    ++size_;
    // arranage the chrono pointer for the new node
    chrono_tail_->chrono_next_ = node;
    node->chrono_prev_ = chrono_tail_;
    chrono_tail_ = node;

    // arrange sorted pointers for the new node
    Node<T>* temp = sorted_tail_;
    while ( temp != sorted_head_ ) {
      if ( temp->value_ < value ) {
	  if ( temp == sorted_tail_ ) {
	      // insert the new node at the end of sorted list
	      sorted_tail_->sorted_next_ = node;
	      node->sorted_prev_ = sorted_tail_;
	      sorted_tail_ = node;
	      return;
	    } else {
	      // insert the new node at the middle of sorted list
	      Node<T>* temp2 = temp->sorted_next_;
	      temp->sorted_next_ = node;
	      node->sorted_prev_ = temp;
	      node->sorted_next_ = temp2;
	      temp2->sorted_prev_ = node;
	      return;
	    }
      }
      temp = temp->sorted_prev_;
    }

    if ( value < sorted_head_->value_) {
      // we are inserting the node at the beginning of the sorted list
      sorted_head_->sorted_prev_ = node;
      node->sorted_next_ = sorted_head_;
      // fix the sorted head to point to the new node
      sorted_head_ = node;
      return;
    } else { // value >= sorted_header->value_
      if (size_ == 2) {
	sorted_head_ -> sorted_next_ = node;
	node-> sorted_prev_ = sorted_head_;
	sorted_tail_ = node;
	return;
      } else {
	Node<T>* temp2 = sorted_head_ -> sorted_next_;
	sorted_head_->sorted_next_ = node;
	node->sorted_prev_ = sorted_head_;
	temp2->sorted_prev_ = node;
	node->sorted_next_ = temp2;
	return;
      }
    }
  }
}

template <class T> 
void MultiLL<T>::copy_list(MultiLL<T> const & old) {
  size_ = old.size_;


  // Handle the special case of an empty list.
  if (size_ == 0) {
    chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = NULL;
    return;
  }
  int i=0;
  chrono_head_ = new Node<T>(old.chrono_head_ -> value_);
  // check if random_head_ or sorted_head_ or sorted_tail_ points to the same chrono_head_ 
  if (old.random_head_ == old.chrono_head_) {
    random_head_ = chrono_head_;
    i++;
  }
  if (old.sorted_tail_ == old.chrono_head_) {
    sorted_tail_ = chrono_head_;
    i++;
  }
  if (old.sorted_head_ == old.chrono_head_) {
    sorted_head_ = chrono_head_;
    i++;
  }  
  chrono_tail_ = chrono_head_;
  // copy the sorted_next_ and sorted_prev_ and random_next_

  Node<T>* old_p = old.chrono_head_ -> chrono_next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    Node<T>* temp = new Node<T>(old_p -> value_);
    chrono_tail_ -> chrono_next_ = temp;
    if(i != 3) {
      if (old.random_head_ == old_p) {
	random_head_ = temp;
	i++;
      }
      if (old.sorted_tail_ == old_p) {
	sorted_tail_ = temp;
	i++;
      }
      if (old.sorted_head_ == old_p) {
	sorted_head_ = temp;
	i++;
      }  
    }
    temp -> chrono_prev_ = chrono_tail_;
    chrono_tail_ = temp;
    old_p = old_p -> chrono_next_;
  }
}


template <class T> 
void MultiLL<T>::destroy_list() {

  if (size_ == 0) { // special case: empty list
    return; // do nothing
  }
  // there's at least one node in the list
  Node<T> *present, *temp;
  present = chrono_head_;
  // since you know the size, it is just nicer to do it like this way
  for ( unsigned int i = 0; i < size_; i++ ) {
    temp = present->chrono_next_;
    delete present;
    present = temp;
  }
    chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = NULL;
    size_ = 0;
}

#endif
