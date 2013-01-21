#include <iostream>
#include "word_frequency.h"
#include "MersenneTwister.h"

// given a sequence of words, navigate through the hierarchy to find the necessary submap
void WordFrequency::PrintFrequency(const std::vector<std::string> &sentence) {
  WordFrequency *tmp = this;
  std::string prefix;
  int size = sentence.size();
  for ( unsigned int i = 0; i < size ; i++ ) {
    tmp = tmp->GetWord(sentence[i]);
    prefix += sentence[i] + " ";
    if ( tmp == NULL) {
      std::cout << "NOT FOUND: " << prefix << std::endl;
      return;
    }
  }
  std::cout << prefix << "(" << tmp->samples << ")\n";
  tmp->PrintFrequency(prefix);
  std::cout << std::endl;
}

// helper function to print the submap
void WordFrequency::PrintFrequency( const std::string &prefix) {
  std::map<std::string, WordFrequency*>::const_iterator i;
  if ( depth == 0 ) return;
  for ( i = frequency.begin(); i != frequency.end(); i++ ) {
    WordFrequency *tmp = i->second;
    assert ( tmp != NULL );
    std::cout << prefix << i->first <<" (" << tmp->samples << ")" << std::endl;
  }
}

// generate the next word in the sentence
std::pair<std::string, float> WordFrequency::NextWord( const std::vector<std::string> & sentence, bool random) {
  static MTRand mtrand;
  int start_index = std::max(0,int(sentence.size()) - (depth-1));
  WordFrequency* tmp = this;
  // navigate to the right portion of the overall map hierarchy
  for ( unsigned int i = start_index; i < sentence.size(); i++ ) {
    tmp = tmp->GetWord(sentence[i]);
    if ( tmp == NULL) {
      return std::make_pair(std::string(""),0.0);
    }
  }
  assert(tmp!=NULL);
  // calculate statistis about the options
  int max = -1;
  int total = 0;
  std::string answer;
  std::map<std::string,WordFrequency*>::const_iterator j;
  for ( j= tmp->frequency.begin(); j!=tmp->frequency.end(); j++ ) {
    total += j->second->samples;
    if ( max < j->second->samples) {
      max = j->second->samples;
      answer = j->first;
    }
  }
  if (total == 0 )
    return std::make_pair(std::string(""),0.0);
  if (random == false )
    return std::make_pair(answer,max/double(total));
  assert(total > 0);
  int rand = mtrand.randInt(total-1);
  assert(rand >=0 && rand < total);
  int sum =0;
  int prob = 0;
  for ( j=tmp->frequency.begin(); j != tmp->frequency.end(); j++ ) {
    sum+= j->second->samples;
    if ( sum > rand ) {
      answer = j->first;
      prob = j->second->samples;
      break;
    }
  }
  assert(sum>rand);
  assert(sum <= total);
  assert(answer !="");
  return std::make_pair(answer,prob/float(total));
}
