#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;

vector<string> wrapstring(string str, int max) {
  // initilize variables for function
  vector<string> words;
  vector<string> wrapped;
  string temp="";
  int linelen=0;
  int wraps=0;

  // loop through string and split it to words
  for(int i=0; i<str.length(); i++) {
    if(str[i]!=' ')
      temp+=str[i];
    else {
      words.push_back(temp);
      temp="";
    }
  }
  // check if temp is empty, if not push it to the back of $words and empty temp  
  if(temp!="") {
    words.push_back(temp);
    temp="";
  }
  
  // loop through $words and when $wrapped child string gets over $max (line length) put it in a new child string
  for(int i=0; i<words.size(); i++) {
    if(linelen+words[i].length()>max) {
      wraps++; 
      linelen=0;
      wrapped.push_back(temp);
      temp="";
    }
    for(int j=0; j<words[i].length(); j++) {
      temp+=words[i][j];
      linelen++;
    }
    temp+=' ';
    linelen++;
  }
  // push last string to the back of $wrapped
  wrapped.push_back(temp);
  return wrapped;
}


int main(int argc, char *argv[]) {
  // check for arguments, if no string, or no argument for flag return Error
  if(argc<2 || argc%2==1) {
    printf("Error, no argument given");
    return 1;
  }
    
  // create variables
  int x, y;              // terminal size
  int targetx, targety;  // text center target
  int max=80;            // max line length
  int padding=0;         // padding to center text
  vector<string> lines;  // vector containing each line

  string arg0 = string(argv[1]);

  // initilize screen and set invisible cursor
  initscr();
  curs_set(0);

  // if there are more than 2 arguments(binaryand string) check for flags and arguments
  if(argc>2) {
    string arg1 = string(argv[2]);
    if(arg1=="-l") {
      max=stoi(argv[3]);
    }
  }
 
  // get terminal dimensions
  getmaxyx(stdscr, y, x);
  if(x<100 || x<max) max=x-20;
  
  // run &wrapstring on $arg0 (inputted string) and $max (max line length) then return it to $lines vector
  lines = wrapstring(arg0, max);

  // find center of screen horizontally and vertically, also move up vertically by half of the number of lines
  targety = y/2-lines.size()/2;
  targetx = (x-max)/2;

  // print each line in $lines
  for(int i=0; i<lines.size(); i++) {
    padding = (max-lines[i].length())/2;
    mvprintw(targety+i, targetx+padding, "%s", lines[i].c_str());
  }
     
  // wait for any input and end window
  getch();
  endwin();

  return 0;
}
