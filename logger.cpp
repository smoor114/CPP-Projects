#include <fstream>
#include <iostream>
#include <string>

using std::fstream;
using std::cout; 
using std::endl;
using std::string;

class Logger {
public:
  static Logger& instance();
  void report(const string&);
  ~Logger();

  //Delete Copy Constructor
  Logger(const Logger&) = delete;
  //Delete Assignment Operator
  Logger& operator=(const Logger&) = delete;

private:
  Logger();
  fstream fout;
};

//~~~~~~~~~~~~~~~~~Instance~~~~~~~~~~~~~~~~~~
//Creates and returns a static instance of
//Logger Object
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Logger& Logger::instance() 
{
  static Logger log;
  return log;
}

//~~~~~~~~~~~~~~~~~~Report~~~~~~~~~~~~~~~~~~~
//Outputs str to fstream and prints to console
//confirmation of what was logged
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Logger::report(const string& str)
{
  cout << "Logged: " << str << " to outptut file" << endl;
  fout << str << endl;
}

//~~~~~~~~~~~~~Default Constructor~~~~~~~~~~~
//Opens the file used for fstream and prints
//to file if open was success or not
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Logger::Logger() 
{ 
  fout.open("log.txt", fstream::out | fstream::app); 
  if (!fout.is_open())
    report("ERROR: FILE NOT OPENED");
  else
    report("FILE OPENED");
}

//~~~~~~~~~~~~~~~~Destructor~~~~~~~~~~~~~~~~~
//Closes fstream and prints to console and
//file if close was successful or not
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Logger::~Logger() 
{ 
  report("FILE CLOSED");
  fout.close();
}


int main() 
{
  Logger::instance().report("--called from main()--");
}