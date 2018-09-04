#include <iostream>
#include <stdlib.h>
#include "simpleCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
	simpleCharManager simplest_mem_manager;
	
	// Alloc Error check
	//char* t1 = simplest_mem_manager.alloc_chars(0);
	//char* t2 = simplest_mem_manager.alloc_chars(100000);
	
	char* text = simplest_mem_manager.alloc_chars(13);

	text[0] = 'H';
	text[1] = 'e';
	text[2] = 'l';
	text[3] = 'l';
	text[4] = 'o';
	text[5] = ' ';
	text[6] = 'w';
	text[7] = 'o';
	text[8] = 'r';
	text[9] = 'l';
	text[10] = 'd';
	text[11] = '!';
	text[12] = '\n';
	
	cout << text;

	// Error check
	//simplest_mem_manager.free_chars(text-1);
	//simplest_mem_manager.free_chars(text+13);

    simplest_mem_manager.free_chars(&(text[6]));
    char* text2 = simplest_mem_manager.alloc_chars(11);

    text2[0] = 'm';
    text2[1] = 'o';
    text2[2] = 'o';
    text2[3] = 'n';
    text2[4] = '!';
    text2[5] = ' ';
    text2[6] = 'b';
    text2[7] = 'y';
    text2[8] = 'e';
    text2[9] = '.';
    text2[10] = '\n';
    
	cout << text;
	
	// Tests
	// simplest_mem_manager.free_chars(text);
	// char* ptr = simplest_mem_manager.alloc_chars(9998);
	// ptr = simplest_mem_manager.alloc_chars(2);
	// cout <<  (void*)ptr << endl;


  /*write driver code as described in the assignment to replace this */
  
  
  return 0;
}

