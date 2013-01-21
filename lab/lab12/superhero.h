#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_
#include<iostream>
#include<string>
#include<map>
using namespace std;
class Team;

class Superhero{
 static std::map<std::pair<std::string,std::string> ,bool> rank;
 public:
  static int count;
 Superhero(std::string n, std::string t, std::string p, bool good=true):name(n),true_identity(t),power(p),is_good(good) 
  {if(count == 0) { count = 1;  populate();}}
  //Accessor
  const std::string & getName() const { return name;}
  const std::string & getPower() const { return power;}
  const bool & isGood() const { return is_good;}
  friend void operator- (Superhero &s) {if ( s.is_good ) s.is_good = false; else s.is_good = true; }
  friend std::ostream& operator<< ( std::ostream &out, const Superhero &s ) {
    if (s.is_good) {
      out << "Superhero "<< s.name << " has power "<< s.power << std::endl;
    }
    else {
      out << "Supervillian "<< s.name << " has power "<< s.power << std::endl;
    }
    return out;
  }// if return value is void, then you can't overload like cout << a << b
  friend bool operator== ( const Superhero &s, std::string st)  {
    return s.true_identity == st;
  }
  friend bool operator!= ( const Superhero &s, std::string st) {
    return s.true_identity != st;
  }
  friend bool operator< (const std::pair<Superhero,Superhero> & s1, const std::pair<Superhero,Superhero> & s2) {
    return s1.first.getName() < s2.first.getName();
  }
  friend Team;
  /* friend bool operator> ( const Superhero &s, const Superhero &ss ) {
     if ( s.rank.find(std::make_pair(s,ss)) == s.rank.end() && s.rank.find(std::make_pair(ss,s)) == s.rank.end() ) {
     std::cout << "It is uncomparable..." << std::endl;
      return false;
      }
      else if (s.rank.find(std::make_pair(s,ss)) != s.rank.end()) 
      return (*(s.rank.find(std::make_pair(s,ss)))).second;
      else return (*(s.rank.find(std::make_pair(ss,s)))).second;
      }*/
   void populate() {
    rank.insert(std::make_pair(std::make_pair("Fire", "Wood"),true));
    rank.insert(std::make_pair(std::make_pair("Wood", "Water"),true));
    rank.insert(std::make_pair(std::make_pair("Fire", "Water"),false));
  }
private:
  bool is_good;
  std::string name;
  std::string true_identity;
  std::string power;
  const std::string& getTrueIdentity() const { return true_identity;}
};
int Superhero::count = 0;

#endif
