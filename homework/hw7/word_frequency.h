#ifndef _WORD_FREQUENCY_H
#define _WORD_FREQUENCY_H
#include<string>
#include<map>
#include<list>
#include<vector>
#include<algorithm>
#include<cassert>

class WordFrequency {
 private:
  int depth;
  int samples;
  void PrintFrequency(const std::string &prefix);
  std::map<std::string,WordFrequency*> frequency;
 public:
  WordFrequency(int i) {assert(i>=0); this->depth = i; samples = 1;}
  //ACCESSORS
  int GetDepth() const { return depth;}
  int GetNumSamples() const { return samples;}
  // return the portion of the hierarchy for this word
  WordFrequency* GetWord(const std::string &word) {
    assert(depth > 0);
    std::map<std::string, WordFrequency*>::iterator itr = frequency.find(word);
    if ( itr == frequency.end())
      return NULL;
    return itr->second;
  }
  void IncrWord(const std::string &word) {
    assert(depth > 0);
    std::map<std::string,WordFrequency*>::iterator itr = frequency.find(word);
    if ( itr != frequency.end() )
      itr->second->samples++;
    else {
      WordFrequency *tmp = NULL;
      tmp = new WordFrequency(depth-1);
      frequency.insert(std::make_pair(word,tmp));
    }
  }
  void PrintFrequency( const std::vector<std::string> &sentence);
  std::pair<std::string,float> NextWord(const std::vector<std::string> &sentence, bool random);
};
#endif
