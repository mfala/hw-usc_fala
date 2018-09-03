#ifndef FLEXCHARMANAGER_H
#define FLEXCHARMANAGER_H


#include <cstddef>
#include "simpleCharManager.h"

typedef struct Mem_Block {
      int size;
      char* physical_location;
      Mem_Block(){size = 0; physical_location = NULL;};
      Mem_Block(int s,char *p){size = s; physical_location = p;};
} Mem_Block;


class flexCharManager: public simpleCharManager
{
	public:
                flexCharManager();
                ~flexCharManager();
             
                char* alloc_chars(int n);
                void free_chars(char* p);

                void tests(); 
                void draw_buffer();
                void print_buffer(int n);         

	protected:
/*Dynamically maintain an array of pointers to Mem_Blocks sorted by physical address which they manage in order to keep
track of active requests */
           
            Mem_Block** used_memory;
/* memory available in the buffer */
            // int free_mem;
/* memory blocks in use */
            int active_requests;
/* memory blocks available in array of memory blocks*/
            int used_mem_size;

            // returns the index of the start location of a free slot with n availible memory
            int free_slot_start(int n);
            int block_to_buf_start_index(int block_index);
            int new_block_index(int buf_index);
            char* get_buf_indx_address(int buf_index);


            void new_mem_block(int buf_index, int store_index, int size);
            void remove_mem_block(int block_index);
            void resize_used_memory(int new_size);


};





#endif
