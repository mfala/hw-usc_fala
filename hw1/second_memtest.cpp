#include <iostream>
#include <stdlib.h>
#include "flexCharManager.h"
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
  flexCharManager charmander;

/*replace with driver code as specificed in the assignment*/
  //std::cout << "Hello world!\n";
  
  /*
  char* text = charmander.alloc_chars(15);

  strcpy(text, "Hello world! \n");
  cout << text;
  */

  char* frag1 = charmander.alloc_chars(3);
  strcpy(frag1, "in ");
  char* frag2 = charmander.alloc_chars(7);
  strcpy(frag2, "French ");
  char* frag3 = charmander.alloc_chars(7);
  strcpy(frag3, "chapeau");

  // remove in
  charmander.free_chars(frag1);

  char* frag4 = charmander.alloc_chars(3);
  strcpy(frag4, "top");

  // remove french
  charmander.free_chars(frag2);


  char* frag5 = charmander.alloc_chars(8);
  //strcpy(frag5, "sombrero");
  char* frag6 = charmander.alloc_chars(3);
  strcpy(frag6, "hat");

  charmander.print_buffer(20);
  charmander.draw_buffer();

  return 0;
}

