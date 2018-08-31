#include <iostream>
#include <fstream>
#include <cstring> 
using namespace std;


// helper function
void helper (ifstream& ifile, int words_left) {

  // basecase
  if (words_left == 0) {
    return;
  }

  // pull off one word from the file stream
  string myword;
  ifile >> myword;

  // goto last word
  helper(ifile, words_left-1);

  // print word and collapse up
  cout << myword << endl;
  return;

}

// main program
int main (int argc, char* argv[]) {

  if(argc < 2) {
    cerr << "Please provide input file filename." << endl;
    return 1;
  }

  // open file
  ifstream ifile (argv[1]);

  // get number of words
  int numwords;
  ifile >> numwords;

  // print words backwards
  helper(ifile, numwords);


  ifile.close();
  return 0;
}
