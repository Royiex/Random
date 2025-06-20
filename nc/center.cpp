#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;

vector<string> wrapstring(string str, int max) {
  vector<string> words;
  vector<string> wrapped;
  string temp="";
  int linelen=0;
  int wraps=0;

  for(int i=0; i<str.length(); i++) {
    if(str[i]!=' ')
      temp+=str[i];
    else {
      words.push_back(temp);
      temp="";
    }
  }
  temp="";

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
  wrapped.push_back(temp);
  return wrapped;
}


int main(int argc, char *argv[]) {
  // Check for argument, if none return Error
  if(argc<2) {
    printf("Error, no arguments given");
    return 1;
  }

  // Create variables
  int x, y;              // terminal size
  int targetx, targety;  // text center target
  int max=80;            // max line length
  int padding=0;         // padding to center text
  vector<string> lines;  // vector containing each line

  string arg = string(argv[argc-1]);

  // Initilize screen and set invisible cursor
  initscr();
  curs_set(0);
 
  // Get terminal dimensions and find the center
  getmaxyx(stdscr, y, x);
  if(x<100) max=x-20;

  lines = wrapstring(arg, max);

  targety = y/2-lines.size()/2;
  targetx = (x-max)/2;

  // Print lines
  for(int i=0; i<lines.size(); i++) {
    padding = (max-lines[i].length())/2;
    mvprintw(targety+i, targetx+padding, "%s", lines[i].c_str());
  }
     
  // Wait for any input and end window
  getch();
  endwin();
  return 0;
}
