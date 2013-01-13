#include<iostream>
#include<cassert>
#include <stdio.h>
#include <stdlib.h>
/*
Author: Xiaohu Nian
The main part of algorithm is the recursively finding the 
number of path from each neighbor to the target point
path(a,b) = path(a.left,b) +path(a.right,b) +
path(a.up,b)+ path(a.down,b)// as for the detail, we need to check each point's validity
The annoying part is to find the basic case of recursive alogrithm, which consumed the majority of the time.
I used leftover argument to track how many points left to travel.
It is very fruitful and fun.
/* second try 
in stead of manually maintain the board for each valid recursive call, all you need to do is to rely on the stack structure 
of computing. However, you need to change whatever you change before the recursive call back to original setting, so after the recursive call
returns, you haven't interfere other neighbors's setting.
It is really smart and extremely fast
 */
using namespace std;

// loc class to save location
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
  // dynamically allocate the board and set every location to 0 expect the  starting point ( which is 1)
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
  // for each location l2 , we need to its four neighbors
  // not all neighbors are in the boundary
  // if the  valid neighbor is just the final target location and the number of points left to explore is one
  // then this is the right path, set path number = 1
  // otherwise if the location is just he final target location whereas there are more than one points left to explore, 
  // then that means it is deadend of some path = 0
  // else recursively call the numberPath using the new location, new leftOver points to explore and set the new location to 1 in the board to denote
  // it is already explored
  // 
  if ( leftOver < 0)
    cout << "Wrong here" << endl;
  int up,down,left,right;
  int path_up =0;
  int path_down =0;
  int path_left =0;
  int path_right =0;
  up = l2.y - 1;
  down = l2.y +1;
  left = l2.x -1;
  right = l2.x + 1;
  
  if (up >= 0) {// check up is not out of bound
    if (loc(l2.x,up) == l1 && leftOver == 1 ) {
      path_up = 1;// if path_up works, then means other paths(down,left,right) are definitely not working so do not check other steps, just returns
      // before return you should mark this l2 as unvisited, since we come back to the calling stack before this stack.
    }
    else if (loc(l2.x,up) == l1 && leftOver > 1) {
      path_up = 0; 
    } else {  if (board[l2.x][up] == 0) {
	board[l2.x][up] = 1;
	path_up = numberPath(l1, loc(l2.x,up), board, bound1, bound2, leftOver-1);
	board[l2.x][up] = 0;
      }
    }
  }
  if (down < bound1 ) {
    if (loc(l2.x,down) == l1 && leftOver == 1 ) {
      path_down = 1;
    }
    else if ( loc(l2.x,down) == l1 && leftOver > 1) {
      path_down = 0;}
    else{ if (board[l2.x][down] == 0) {
      board[l2.x][down] = 1;
      path_down = numberPath(l1, loc(l2.x,down), board, bound1, bound2, leftOver-1);
      board[l2.x][down] = 0;
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
       board[left][l2.y] = 1;
       path_left = numberPath(l1, loc(left,l2.y), board, bound1, bound2, leftOver-1);
       board[left][l2.y] = 0;
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
      board[right][l2.y] = 1;
      path_right = numberPath(l1, loc(right,l2.y), board, bound1, bound2, leftOver-1);
      board[right][l2.y] = 0;
    }
   }
 }
 board[l2.x][l2.y] = 0;
 return path_up+path_down+path_left+path_right;
}
