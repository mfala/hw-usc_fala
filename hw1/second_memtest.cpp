#include <iostream>
#include <stdlib.h>
#include "flexCharManager.h"
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{

  flexCharManager simplest_mem_manager;

/*replace with driver code as specificed in the assignment*/
  //std::cout << "Hello world!\n";

/*replace with driver code as specificed in the assignment*/
  char* text = simplest_mem_manager.alloc_chars(6);

  
	text[0] = 'H';
	text[1] = 'e';
	text[2] = 'l';
	text[3] = 'l';
	text[4] = 'o';
	text[5] = ' ';

	char* world = simplest_mem_manager.alloc_chars(7);

	world[0] = 'w';
	world[1] = 'o';
	world[2] = 'r';
	world[3] = 'l';
	world[4] = 'd';
	world[5] = '!';
	world[6] = '\n';

  cout << text;
  
  simplest_mem_manager.free_chars(world);

  char* moon = simplest_mem_manager.alloc_chars(7);

	moon[0] = 'm';
	moon[1] = 'o';
	moon[2] = 'o';
	moon[3] = 'n';
	moon[4] = '!';
	moon[5] = ' ';
	moon[6] = 'b';
	moon[7] = 'y';
	moon[8] = 'e';
	moon[9] = '.';
	moon[10] = '\n';

	cout << text;

  return 0;
}

