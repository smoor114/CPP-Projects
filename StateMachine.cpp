
#include <string>
#include <iostream>

using std::string;

class State; 

class Process {
public:
  Process();
  void changeState(State* s) { state_ = s; }
  string getName() const { return name_; }
  string report();
  Process* clone();
  void run(std::ostream& out = std::cout);
  bool hasFinished();
  int getRemainingRunTime();
private:
  const string name_;
  State* state_;
  static int counter;
};

Process::Process() : name_("Process" + std::to_string(counter++)),
                     remainingRunTime(rand()%999+1) {
  state_ = NewState::instance();
}

string Process::report() {
  return name_ + " is " + state_->report();
}

Process* Process::clone() {
  // returns process in new state
  return new Process(); // parenthesese value initilizes clone
}

void Process::run(std::ostream& out) {
  // time slice broken up into sub slices. 
  // a trap can be thrown randomly at any of these time slices
  const int kSubSlice = 10;

  // increase this to make traps less likely
  // if trapLikelihood = 0, traps will throw every time
  const int trapLikelihood = 3; 

  bool printedFinishStatement = false;

  for (int i=0; i<kSubSlice; ++i) {
    if (((rand() % (trapLikelihood*kSubSlice)) == 0) && !hasFinished())
      throw "Process requires I/O";
    else {
      if (hasFinished() && printedFinishStatement == false) {
        out << "FINISHED (busy wait for remainder of time slice)";
        printedFinishStatement = true;
      }
      remainingRunTime -= (Scheduler::ksTimeSlice/kSubSlice);
      waitDots(1);
    } 
  }

/* 
  // original code
  if ((rand() % 3) == 0)
    throw "Process requires I/O";
  else {
    remainingRunTime -= Scheduler::ksTimeSlice;
    waitDots(10);
  }
  */
}

bool Process::hasFinished() {
  return (remainingRunTime <= 0);
}

int Process::getRemainingRunTime() {
  return remainingRunTime;
}


int Process::counter = 0;

