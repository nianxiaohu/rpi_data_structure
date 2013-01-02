#include<iostream>
#include<cassert>
#include<cstdlib>
#include "date.h"
using namespace std;

const int DaysInMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
const std::string MonthNames[13]={"","January","February","March","April","May","June","July","August","September","October","November","December"};

Date::Date(){
  day = 1;
  month = 1;
  year = 1900;
}
Date::Date(int aMonth, int aDay, int aYear):month(aMonth),day(aDay),year(aYear) {}
int monthstring_to_int(std::string &name)
{
  for (int i=0;i<13;i++){
    if (MonthNames[i]==name)
      return i;
  }
  assert(0);
  exit(0);
}
Date::Date(std::string &aMonth, int aDay, int aYear):day(aDay),year(aYear) {
  month = monthstring_to_int(aMonth);
}
int Date::getDay() const { return day;}
int Date::getMonth() const { return month;}
int Date::getYear() const { return year;}
void Date::setDay(int d){ day = d;}
void Date::setMonth( int m) { month = m;}
void Date::setYear( int y) {year = y;}
void Date::increment() {
  if ( isLastDayInMonth() )
    {
      month++;
      day = 1;
    }
  else
    {
      day++;
    }
  if (month == 13)
    {
      month = 1;
      year++;
    }
}
bool Date::isLeapYear() const {
  return (( year%4==0 && year%100 != 0 )|| year%400 ==0);
}
int Date::lastDayInMonth() const {
  if ( month==2 && isLeapYear())
    return 29;
  else
    return DaysInMonth[month];
}
bool Date::isLastDayInMonth() const {
  return day==lastDayInMonth();
}
void Date::print() const {
  std::cout<< month<<"/"<<day<<"/"<<year;
}
bool Date::isEqual( const Date &date2) const {
  return day==date2.getDay() && month==date2.getMonth() && year==date2.getYear();
}
bool sameDay(const Date &date1, const Date &date2){
  return date1.getDay()==date2.getDay()&& date1.getMonth()== date2.getMonth();
}
