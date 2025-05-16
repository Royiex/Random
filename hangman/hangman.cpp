#include <string>
#include <ncurses.h>
using namespace std;

int lives=5;
int guess=0;
char buffer[50];
string word="";
string guessed="";
string last="";
int midy, midx;
string start="Enter Word:";
string win=" You Win!";
string lose=" You Lose!";
string wrong=" Wrong Char  ";
string correct="Correct Char";



void ProcessGuess() {
  last=guessed;
  for(int i=0; i<word.length(); i++) {
    if(word[i]==guess) guessed[i]=guess;    
  }

  if(guessed==last) {
    lives--;
    mvprintw(midy+5, midx-wrong.length()/2+1, wrong.c_str());
  }
  else mvprintw(midy+5, midx-correct.length()/2+1, correct.c_str());
}

int main() {
  initscr();
  noecho();

  int maxx = getmaxx(stdscr);
  int maxy = getmaxy(stdscr);

  midx = maxx/2;
  midy = maxy/2;

  mvprintw(midy-4, midx-start.length()/2, start.c_str());
  move(midy-3, midx);
  getstr(buffer);
  word=buffer; 

  move(midy-4, 0);
  clrtoeol();
  
  int length = word.length();
  for(int i=0; i<length; i++) guessed+='_';
  
  echo();

  while(1) {
    mvprintw(midy-1, midx-word.length()/2, guessed.c_str());
    move(midy+3,midx);
    if(guessed==word) break;
    if(lives<1) break;
    guess = getch();
    
    ProcessGuess();
  }

  if(lives>0) mvprintw(midy-5, midx-win.length()/2, win.c_str());
  else mvprintw(midy-5, midx-lose.length()/2, lose.c_str());

  getch();
  endwin();
  
  return 0;
}
