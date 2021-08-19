#ifndef WORDLIST
#define WORDLIST
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::string;
using std::endl;

class WordOccurrence {
public:
    WordOccurrence(const string& word="", int num=0);
    bool matchWord(const string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    string getWord() const; 
    int getNum() const;

private:
    string word_;
    int num_;
};

class WordList {
public:
  WordList(); 
  WordList(const WordList&);
  ~WordList();	
  WordList& operator=(const WordList&);
  friend bool equal(const WordList&, const WordList&); 
  void addWord(const string &); 
  void print();
private:
  WordOccurrence * wordArray_; 
  
  int size_;
};

//---------------WORD OCCURANCE FUNCTIONS---------------

//~~~~~~~~~~~CONSTRUCTOR~~~~~~~~~~~~
//takes a word and num to store in node
WordOccurrence::WordOccurrence(const string &word, int num) {
  word_ = word;
  num_ = num;
}

//~~~~~~~~~~~MATCHWORD~~~~~~~~~~~~~~~~
//takes a word and checks if that is equal
//to the current word
bool WordOccurrence::matchWord(const string & match) {
  if (match == word_) return true;
  else return false;
}

////~~~~~~~~~~~~INCREMENT~~~~~~~~~~~~~~~~~
//increments number of occurences by 1
void WordOccurrence::increment() {
  ++num_;
}

//~~~~~~~~~~~~GETWORD~~~~~~~~~~~~~~~
//returns word
string WordOccurrence::getWord() const{
  return word_;
}

//~~~~~~~~~~~~GETNUM~~~~~~~~~~~~~~~
//returns number of occurences 
int WordOccurrence::getNum() const {
  return num_;
}

//----------------WORD LIST FUNCTIONS---------------

//~~~~~~~~~~~~CONSTRUCTOR~~~~~~~~~~~~~~~
WordList::WordList() {
  size_ = 0;
  wordArray_ = new WordOccurrence[size_];
}
//~~~~~~~~~~~~COPY CONSTRUCTOR~~~~~~~~~~~~
//creates a WordList from another rhs
WordList::WordList(const WordList& rhs){
  size_ = rhs.size_;
  wordArray_ = new WordOccurrence[size_];

  for (int i = 0; i < size_; ++i) 
    wordArray_[i] = rhs.wordArray_[i];
}

//~~~~~~~~~~~~DESTRUCTOR~~~~~~~~~~~~~~~
WordList::~WordList() { 
  delete [] wordArray_;
}

//~~~~~~~~~~~~EQUAL~~~~~~~~~~~~~~~
//returns true id the two WordLists are equal
//takes two WordLists lhs and rhs to compare
bool equal(const WordList& lhs, const WordList& rhs) {
  if (lhs.size_ != rhs.size_)
     return false;
  
  for (int i = 0; i < lhs.size_; ++i) 
  {
    if ((lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord()) || (lhs.wordArray_[i].getNum() != rhs.wordArray_[i].getNum()))
      return false;
  }
  return true;
}
//~~~~~~~~~~~~ = OPERATOR~~~~~~~~~~~~~~~
WordList& WordList::operator=(const WordList& rhs) {
  if (this == &rhs) return *this;
  
  if (wordArray_ != nullptr)
    delete[] wordArray_;
  
  size_ = rhs.size_;
  wordArray_ = new WordOccurrence[size_];
  
  for (int i = 0; i < size_; ++i) 
    wordArray_[i] = rhs.wordArray_[i];
  
  return *this;
}

//~~~~~~~~~~~~ADDWORD~~~~~~~~~~~~~~~
//returns word
void WordList::addWord(const string& word) {
  for (int i = 0; i < size_; ++i) {
    if (wordArray_[i].matchWord(word)) {
      wordArray_[i].increment();
      return;
    }
  }
  WordOccurrence *tempArray = new WordOccurrence[size_+1];
  for (int i = 0; i < size_; ++i)
    tempArray[i] = wordArray_[i];
  delete[] wordArray_;
  wordArray_ = tempArray;

  int ins = 0;
  for (int i = 0; i < size_; ++i) 
  {
  
    if (wordArray_[i].getWord().compare(word) > 0) 
    {  
      ins = i; 
      break; 
    }
    else ins = i + 1;
  }
 
  for (int i = size_-1; ins <= i; --i) 
  {
    wordArray_[i + 1] = wordArray_[i];
  }
  
  wordArray_[ins] = WordOccurrence(word, 1); 
  ++size_;
}
//~~~~~~~~~~~~PRINT~~~~~~~~~~~~~~~
// prints word list and occurences of the list
void WordList::print() 
{
  if (size_ == 0)  
  {
    std::cout << "file is empty" << endl;
    return;
  }
  
  int freq = 0;
  for (int i = 0; i < size_; ++i) 
  {
    if (wordArray_[i].getNum() > freq) 
      freq = wordArray_[i].getNum();
  }
  while (freq > 0)
  {
    for (int i = 0; i < size_; ++i) 
    {
      if (wordArray_[i].getNum() == freq)
        std::cout << wordArray_[i].getNum()<< "\t" << wordArray_[i].getWord() << endl;
    }
    --freq;
  }
}






#endif 
