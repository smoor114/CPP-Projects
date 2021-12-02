//Spencer Moore
//smoor114

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; 
using std::string;
using std::cout; 
using std::cin; 
using std::endl;

//------------------Document-------------------
class Document {
public:

  Document(const vector <string> & data={}): data_(data){}

  void show();
  void insert(int line, const string &str);
  string remove(int line);

private:
  vector<string> data_; 
}; 

//~~~~~~~~~~~~~~~~~~~Show~~~~~~~~~~~~~~~~~~~~~~~
// Prints text and line numbers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Document::show() 
{
  for(int i = 0; i < data_.size(); ++i)
  {
     cout << i + 1 << ". " << data_[i] << endl; 
  }
}

//~~~~~~~~~~~~~~~~~~~Insert~~~~~~~~~~~~~~~~~~~~~
//Inserts str at line within range
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Document::insert(int line, const string &str) 
{
  int index = line-1;

  if (index <= data_.size())
  {
    data_.insert(data_.begin() + index, str); 
  }
  else
  {
    cout << "line out of range" << endl; 
  }
}

//~~~~~~~~~~~~~~~~~~~Remove~~~~~~~~~~~~~~~~~~~~~
// Deletes given line within range
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  string Document::remove(int line) 
  {
    int index = line-1;
    string deletedLine="";

    if(index < data_.size())
    {
      deletedLine = data_[index];
      data_.erase(data_.begin() + index); 
    }
    else
    {
      cout << "line out of range" << endl; 
    }
    return deletedLine;
  } 

//------------------Command---------------------
class Command{
public:
  Command(Document *doc) : doc_(doc){}
  virtual void execute() = 0; 
  virtual void unexecute() = 0;
  virtual void print() const = 0;
  virtual ~Command(){}
protected:
  Document *doc_; 
}; 

//--------------Insert Command------------------
class InsertCommand : public Command {
public:
  InsertCommand(Document *doc, int line, 
		const string &str): 
    Command(doc), line_(line), 
    str_(str) {}
  void execute() {
    doc_->insert(line_, str_);}
  void unexecute() {doc_->remove(line_);}
  void print() const {
    cout << "Insert line " << line_;}
private:
  int line_; 
  string str_; 
}; 

//----------------Erase Command-----------------
class EraseCommand : public Command {
public:
  EraseCommand(Document *doc, int line): 
    Command(doc), line_(line), str_("") {}
  void execute() {str_ = doc_->remove(line_);}
  void unexecute() {doc_-> insert(line_, str_);}
  void print() const {
    cout << "Erase line " << line_;}
private:
  int line_;
  string str_;
};


class DocumentWithhistory
{
public:
  DocumentWithhistory(const vector<string> & text={}) : doc_(text){}

//~~~~~~~~~~~~~~~~~~~Insert~~~~~~~~~~~~~~~~~~~~~
// Creates InsertCommand and pushes command to back
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void insert(int line, string str) 
  {
    Command *com = new InsertCommand(&doc_, line, str); 
    com->execute(); 
    doneCommands_.push_back(com); 
  }

//~~~~~~~~~~~~~~~~~~~Erase~~~~~~~~~~~~~~~~~~~~~~
// Creates EraseCommand and pushes command to back
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void erase(int line)
  {
    Command *com = new EraseCommand(&doc_, line);
    com->execute();
    doneCommands_.push_back(com);
  }

//~~~~~~~~~~~~~~~~~~History~~~~~~~~~~~~~~~~~~~~~
// Prints the list of hostory from doneCommands
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void history() 
  {
    for (int i = 0; i != doneCommands_.size(); ++i) 
    {
      cout << i << ". ";
      doneCommands_[i]->print(); 
      cout << '\n';
    }

    cout << '\n';
  }

//~~~~~~~~~~~~~~~~~~~~Show~~~~~~~~~~~~~~~~~~~~~~
// Shows the Document line by line
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void show() {doc_.show();}

//~~~~~~~~~~~~~~~~~~~Undo~~~~~~~~~~~~~~~~~~~~~~~
// Checks to make sure doneCommands is not 0
// Unexecutes the back command of doneCommands
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void undo() 
  {
    if(doneCommands_.size() != 0) 
    {
       Command *com = doneCommands_.back(); 
       doneCommands_.pop_back(); 
       com->unexecute();
       delete com;
    }
    else
    {
      cout << "no commands to undo" << endl; 
    }
  }

//~~~~~~~~~~~~~~~~~~~Redo~~~~~~~~~~~~~~~~~~~~~~~
// Executes choice from doneCommands
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void redo(int choice) 
  {
    if(doneCommands_.size() != 0 && choice < doneCommands_.size()) 
    {
      Command *com = doneCommands_[choice];
      com->execute();
      doneCommands_.push_back(com);
    }
    else
    {
       cout << "no commands to redo" << endl;
    }
  }


class Memento *createMemento() const;  
void rollBack(class Memento *); 

private:
  vector<Command*> doneCommands_; 
  Document doc_;
}; 

//-------------------Memento--------------------
class Memento 
{
public:
  Memento(const DocumentWithhistory& doc): doc_(doc) {}
  const DocumentWithhistory& getState() const {return doc_;}  
private:
  const DocumentWithhistory doc_;
};
 

//~~~~~~~~~~~~~~~Create Memento~~~~~~~~~~~~~~~~~
// Creates memento Object
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
Memento *DocumentWithhistory::createMemento() const
{
  // copying the Document itself
  return new Memento(*this); 
}

//~~~~~~~~~~~~~~~~~RollBack~~~~~~~~~~~~~~~~~~~
// Restore to previous state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void DocumentWithhistory::rollBack(Memento *mem)
{
  *this = mem->getState(); 
  this->doneCommands_.clear();
}


int main() {
  DocumentWithhistory his({
      "Lorem Ipsum is simply dummy text of the printing and typesetting",
	"industry. Lorem Ipsum has been the industry's standard dummy text",
	"ever since the 1500s, when an unknown printer took a galley of",
	"type and scrambled it to make a type specimen book. It has",
	"survived five centuries."}); 

  int line; 
  string str; 
  char option;

  Memento *checkpoint = nullptr;

  do {
    his.show(); 
    cout << endl;

    cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command" << endl;
    cout << "(c)heckpoint roll(b)ack (h)istory (r)edo command: ";
    cin >> option; 


  //Command Selection
    switch(option) 
    {
      case 'i':
        cout << "Line number to insert: "; 
        cin >> line; 
        cout << "Line to insert: "; 
        cin.get();
        getline(cin, str); 
        his.insert(line, str); 
      break;
 
    case 'e':
      cout << "Line number to remove: ";
      cin >> line;
      his.erase(line);
    break;

    case 'u':
      his.undo(); 
    break; 

    case 'c':
      checkpoint = his.createMemento();
    break;
      
    case 'b':
      if (checkpoint != nullptr) 
      {
	       his.rollBack(checkpoint);
	       delete checkpoint;
      }
    break;

    case 'h':
      his.history();
    break;

    case 'r':
      his.history();
      cout << "Command to redo: ";
      cin >> line;
      his.redo(line);
    break;

    }

  } while(option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r');
}