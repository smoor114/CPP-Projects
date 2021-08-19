#include "WordList.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main(int argc, char *argv[]) {
  //File handling
  if (argc != 2) 
  {
    std::cout << "1 File is required. Try again." << std::endl;
    return 1;
  }
  string input = argv[1];
  
  std::ifstream ifs(input);
  
  if (ifs.fail()) 
  {  
    std:cout << "file failed to open" << endl;
    return 1;
  }
//WL handling
  WordList wl;
  string word;
  while (ifs >> word)
  {   
    string fix;
    for (int i = 0; i < word.size(); ++i) 
    {
      char temp = word[i];
      if (0 <= temp && temp <= 127) 
      {
        if (isalnum(temp)) 
        {
          if (isupper(temp)) temp = char(tolower(temp));
            fix.append(sizeof(temp), temp);
        }
      }
    }
    wl.addWord(fix);
  }
  wl.print();
  ifs.close();
}
