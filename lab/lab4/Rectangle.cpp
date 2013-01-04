#include <iostream>
#include <algorithm>
#include <vector>
#include "Rectangle.h"

Rectangle::Rectangle( Point2D const &lower_left, Point2D const &upper_right )
  : m_lower_left(lower_left), m_upper_right(upper_right)
e{ }

bool Rectangle::is_point_within( Point2D const &p ) const
{
  return
    ( p.x() <= m_upper_right.x() && p.y() <= m_upper_right.y() ) ||
    ( p.x() >= m_lower_left.x() && p.y() >= m_lower_left.y() );
}



vector<Point2D> points_in_both( Rectangle const& r1, Rectangle const& r2 )
{
  //  The following access the vector of points in the two rectangles
  //  without copying these vectors.  Instead, r1_points and r2_points
  //  are references to the vectors of points, but since they are
  //  constants neither the vectors nor the points within them can be
  //  changed.
  const vector<Point2D> & r1_points = r1.points_contained();
  const vector<Point2D> & r2_points = r2.points_contained();
  std::vector<Point2D> pointsB;
  for ( unsigned int i=0; i<r1_points.size();i++)
    {
      if ( std::find(r2_points.begin(),r2_points.end(),r1_points[i]) != r2_points.end())
	pointsB.push_back(r1_points[i]);
    }
  return pointsB;

}
bool Rectangle::add_point(Point2D const& p) {
  if (is_point_within(p))
    {
      if (std::find(m_points_contained.begin(),m_points_contained.end(),p)==m_points_contained.end())
	{
	  m_points_contained.push_back(p);
	  return true;
	}
      else return false;
    }
  else
    return false;
}
void print_rectangle( Rectangle const& r1 )
{
  // get all the points that are inside the rectangle
  const vector<Point2D> & r1_points = r1.points_contained();
  
  // print the rectangle coordinates
  cout << "Rectangle: " 
       << r1.lower_left_corner().x() << "," << r1.lower_left_corner().y() << "--"
       << r1.upper_right_corner().x() << "," << r1.lower_left_corner().y() << endl;
       
  // print points that are inside
  cout << "Points inside:" << endl;
  for( vector<Point2D>::size_type i = 0; i < r1_points.size(); ++i ) {
    cout << r1_points[i].x() << "," << r1_points[i].y() << endl;
  }
}


