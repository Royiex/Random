#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;

vector<string> wrapstring(string str, int max, int pad) {
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
      // mvprintw(wraps, 0, "Wrapped at %d, max is %d, word is %d %d", linelen, max, i, words[i].length());
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
  if(argc==1) {
    printf("Error, no arguments given");
    return 1;
  }


  char *arg1 = argv[1];
  string arg = string(arg1);

  // Create variables
  int x, y;  
  int targetx, targety;
  int max=80;
  int pad=10;
  int lines=0;

  vector<string> words;

  // Initilize screen and set invisible cursor
  initscr();
  curs_set(0);    

  // Wrap lines >80
  getmaxyx(stdscr, y, x);
  if(x<100) max=x-20;  
  
  words = wrapstring(arg, max, pad);
  // mvprintw(0, 0, "Passed");

  for(int i=0; i<words.size(); i++) {
    mvprintw(15+i, 10, words[i].c_str());
  }
   
  // Get terminal dimensions and find the center
  // targety = y/2-1;
  // targetx = x/2 - arg.length()/2;

  // // Print text at the center
  // mvprintw(targety, targetx, str);

  // // Print debug
  // mvprintw(0, 0, "%d %d", targetx, targety);

  // Wait for any input and end window
  getch();
  endwin();
  return 0;
}
