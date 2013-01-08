#include<iostream>
#include<cassert>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


class loc {
public:
  loc(int r=0, int c=0) : x(r), y(c) {}
  int x, y;
};
bool operator== (const loc &l1, const loc &l2) { return l1.x==l2.x && l1.y==l2.y;}
int numberPath(loc,loc,int**&,int,int,int);


int main(int argc, char* argv[]) {
  if ( argc != 3)
    {
      cerr << "Usage: " << argv[0] << "column# row#" << endl;
    }
  int column = 0;
  int row = 0;
  column = atoi(argv[1]); 
  row = atoi(argv[2]);
  // int column = 10;
  // int row = 4;
  int** board = new int*[column];
  for ( unsigned int i=0; i<column;i++) {
    board[i] = new int[row];
    for ( unsigned int j=0; j<row; j++ ) {
      board[i][j] = 0;
    }
  }
  board[0][0] = 1;
  int total=column*row;
  int num =  numberPath(loc(0,row-1),loc(0,0), board, row, column, total-1);
  cout << num << endl;
}

int numberPath( loc l1, loc l2, int** &board, int bound1, int bound2, int leftOver )
{
  // assert ( leftOver >=1 );
  if ( leftOver < 0)
    cout << "Wrong here" << endl;
  // if ( l1 == l2 && leftOver == 1 )
  //   return 1;
  int up,down,left,right;
  int path_up =0;
  int path_down =0;
  int path_left =0;
  int path_right =0;
  up = l2.y - 1;
  down = l2.y +1;
  left = l2.x -1;
  right = l2.x + 1;
  if (up >= 0) {
    if (loc(l2.x,up) == l1 && leftOver == 1 ) {
      path_up = 1;
    }
    else if (loc(l2.x,up) == l1 && leftOver > 1) {
      path_up = 0; 
    } else {  if (board[l2.x][up] == 0) {
	int**  board1 = new int*[bound2];
	for ( unsigned int i=0; i<bound2;i++) {
	  board1[i] = new int[bound1];
	  for ( unsigned int j=0; j<bound1; j++ ) {
	    board1[i][j] = board[i][j];
	  }
	}
	board1[l2.x][up] = 1;
	path_up = numberPath(l1, loc(l2.x,up), board1, bound1, bound2, leftOver-1);
      for ( unsigned int i=0; i<bound2;i++) { 
	delete [] board1[i];
      }
      delete [] board1;
    }
    }
  }
  
  if (down < bound1 ) {
    if (loc(l2.x,down) == l1 && leftOver == 1 ) {
      path_down = 1;
    }
    else if ( loc(l2.x,down) == l1 && leftOver > 1) {
      path_down = 0;}
    else{
    if (board[l2.x][down] == 0) {
      int**  board1 = new int*[bound2];
      for ( unsigned int i=0; i<bound2;i++) {
	board1[i] = new int[bound1];
	for ( unsigned int j=0; j<bound1; j++ ) {
	  board1[i][j] = board[i][j];
	}
      }
      board1[l2.x][down] = 1;
      path_down = numberPath(l1, loc(l2.x,down), board1, bound1, bound2, leftOver-1);
      for ( unsigned int i=0; i<bound2;i++) { 
	delete [] board1[i];
      }
      delete [] board1;
    }
    }
  }
  
  
 if (left >=0 ) {
   if (loc(left,l2.y) == l1 && leftOver == 1 ) {
     path_left = 1;
   }
   else {if (loc(left,l2.y) == l1 && leftOver > 1) {
     ;}
   else  if (board[left][l2.y] == 0) {
     int**  board1 = new int*[bound2];
     for ( unsigned int i=0; i<bound2;i++) {
       board1[i] = new int[bound1];
       for ( unsigned int j=0; j<bound1; j++ ) {
	  board1[i][j] = board[i][j];
       }
     }
     board1[left][l2.y] = 1;
     path_left = numberPath(l1, loc(left,l2.y), board1, bound1, bound2, leftOver-1);
     for ( unsigned int i=0; i<bound2;i++) { 
       delete [] board1[i];
     }
     delete [] board1;
   }
   }
 }

 
 if (right < bound2 ) {
   if (loc(right,l2.y) == l1 && leftOver == 1) {
     path_right = 1;
   }
   else { if ( loc(right,l2.y) == l1 && leftOver > 1) {
     path_right = 0;
   } else  if (board[right][l2.y] == 0) {
     int**  board1 = new int*[bound2];
      for ( unsigned int i=0; i<bound2;i++) {
	board1[i] = new int[bound1];
	for ( unsigned int j=0; j<bound1; j++ ) {
	  board1[i][j] = board[i][j];
	}
      }
      board1[right][l2.y] = 1;
      path_right = numberPath(l1, loc(right,l2.y), board1, bound1, bound2, leftOver-1);
      for ( unsigned int i=0; i<bound2;i++) { 
	delete [] board1[i];
      }
      delete [] board1;
    }
   }
 }
 return path_up+path_down+path_left+path_right;
}
