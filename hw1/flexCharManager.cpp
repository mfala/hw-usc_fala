#include "flexCharManager.h"
#include <iostream>

flexCharManager::flexCharManager(){
	active_requests = 0;
 	used_memory = new Mem_Block*[2];
 	used_mem_size = 2;

}

flexCharManager::~flexCharManager(){
	for (int i = 0; i < active_requests; i++) {
		// call deconstructor of each memblock
		delete used_memory[i];
	}

	// delete full Mem_Block array
	delete [] used_memory;
}
             
char* flexCharManager::alloc_chars(int n){

	// Check for invalid length
	if (n <= 0) {
		std::cerr << "Error: invalid allocation length" << std::endl;
		return 0;
	}

	// get free buffer slot index and block location
	int next_free = free_slot_start(n);

	// check if there is enough buffer space
	if (next_free == -1) {
		std::cerr << "Error: unable to allocate memory. buffer has run out of defragmented space" << std::endl;
		return 0;
	}

	int my_block_index = new_block_index(next_free);

	// create new memory block
	new_mem_block(next_free, my_block_index, n);
    return used_memory[my_block_index]->physical_location;
}

void flexCharManager::free_chars(char* p){
	// Possible to implement a binary search
	// instead -> choose linear

	// check for impropperly allocated memory
	if (p <= 0) {
		std::cerr << "Error: attempting to free an impropperly allocated memory address" << std::endl;
		return;
	}

	// search memory blocks for address
	for (int i = 0; i < active_requests; i++) {
		if (used_memory[i]->physical_location == p) {
			remove_mem_block(i);
			return;
		}
	}

	// if memory block not found
	std::cerr << "Error: free_chars method could not find any memory block associated with the address provided." << std::endl;
	return;
}         


// Private members
// Returns first free memory slot if availible
// Returns -1 if not availible
int flexCharManager::free_slot_start(int n) {

	int found_slot = -1;
	int block_i = 0;

	// if no request elements
	if (active_requests == 0) {
		// check if buffer can fit request
		
		if (n <= BUF_SIZE) {
			return 0; 
		}
		else {
			return -1;
		}

	// parse request elements
	} else {

		// first check: start to block 1
		int buf_gap = block_to_buf_start_index(0);
		if (buf_gap - 0 >= n) {
			return 0;
		} 

		// second check: block_end to block_start
		for (int i = 0; i < active_requests-1; i++) {
			int after_b1 = block_to_buf_start_index(i) + used_memory[i]->size;
			int buf_gap = block_to_buf_start_index(i+1) - after_b1;
			if (buf_gap >= n){
				return after_b1;
			}
		}

		// third check: final block end to end of buf
		int after_bfinal = block_to_buf_start_index(active_requests-1) + used_memory[active_requests-1]->size;
		int after_last_el = (BUF_SIZE);
		buf_gap = after_last_el - after_bfinal;
		if (buf_gap >= n) {
			return after_bfinal;
		}

		// no space, buffer needs defrag or deletion
		//std::cerr << "Error: buffer has run out of defragmented space" << std::endl;
		return -1;

	}
}

// Already verified that the block fits
// Find where to place block in the buffer order
int flexCharManager::new_block_index(int buf_index) {
	// check if before any existing block
	for (int i = 0; i < active_requests; i++) {
		if  (buf_index < block_to_buf_start_index(i))  {
			// insert before block i
			return i; 
		}
	}
	// insert after all blocks
	return active_requests;
}

int flexCharManager::block_to_buf_start_index(int block_index) {

	// check if block index is within bounds
	if (block_index >= active_requests || block_index < 0) {
		std::cerr << "Error: trying to access memory block buffer index outside of bounds" << std::endl;
		return -1;
	}
	// get the starting block address
	char* start_address = buffer;
	char* tar_address = used_memory[block_index] -> physical_location;

	// get the index
	int charlen_x_ind = (int)(tar_address - start_address);

	return charlen_x_ind / sizeof(char);
}

char* flexCharManager::get_buf_indx_address(int buf_index) {
	return buffer + buf_index;
}

void flexCharManager::new_mem_block(int buf_index, int store_index, int size) {

	// create the new memory block
	char* buf_address = get_buf_indx_address(buf_index);
	Mem_Block* new_block = new Mem_Block(size, buf_address);

	// if space is not availible
	if (active_requests >= used_mem_size) {
		// double memory
		resize_used_memory(used_mem_size*2);
	}

	// move end elements back
	for (int i = active_requests-1; i >= store_index; i--) {
		used_memory[i+1] = used_memory[i];
	}

	// insert new block
	used_memory[store_index] = new_block;
	active_requests++;

	return;
}

void flexCharManager::remove_mem_block(int block_index) {

	// check if index is out of bounds
	if (block_index > active_requests-1) {
		std::cerr << "Error: Cannot remove memory block whose index is out of bounds" << std::endl;
		return;
	}
	// overwrite block to 0 in buffer
	int overwrite_start = block_to_buf_start_index(block_index);
	int overwrite_last  = overwrite_start + used_memory[block_index]->size - 1;
	for (int i = overwrite_start; i <= overwrite_last; i++) {
		buffer[i] = 0;
	}

	// delete block
	delete used_memory[block_index];

	// remove block from used_memory
	for (int i = block_index; i<(active_requests-1); i++){
		used_memory[i] = used_memory[i+1];
	}
	active_requests--;

	// check if scale down is needed
	if (used_mem_size != 2 && used_mem_size > 4*active_requests) {
		resize_used_memory(used_mem_size/2);
	}
}

void flexCharManager::resize_used_memory(int new_size) {

	// debug output
	//std::cout << "Resizing array from: " << used_mem_size << " to size: " << new_size << std::endl;

	// check not destroying memory
	if (active_requests > new_size) {
		std::cerr << "Error: attempting to resize used_memory to a size which cannot contain all memory blocks";
		return;
	}

	if (new_size == used_mem_size) {
		return;
	}

	// make new block holder
	Mem_Block** new_used_mem = new Mem_Block*[new_size];

	// copy blocks over
	for (int i = 0; i < active_requests; i++) {
		new_used_mem[i] = used_memory[i];
	}


	// delete block holder, blocks are preserved
	delete [] used_memory;


	used_memory = new_used_mem;
	used_mem_size = new_size;

	return;

}

void flexCharManager::draw_buffer() {

	std::cout << "		Buffer: [[[ ";

	// check if there are memory blocks allocated
	if (active_requests > 0) {
		int last_buffer_index =  block_to_buf_start_index(active_requests-1);
		int buf_cursor = 0;

		for (int i = 0; i < active_requests; i++) {
			while (buf_cursor < block_to_buf_start_index(i)) {
				std::cout << "_";
				buf_cursor++;
			}

			while (buf_cursor < block_to_buf_start_index(i)+used_memory[i]->size) {
				std::cout << "X";
				buf_cursor++;
			}
		}
	}

	std::cout << " ]]]" << std::endl;
}

void flexCharManager::print_buffer(int n) {

	std::cout << "		Buffer: [[[ ";

	// check if there are memory blocks allocated
	for (int i = 0; i < n; i ++) {
		if (buffer[i] == 0) {
			std::cout << "_";
		} else if (buffer[i] == '\n') {
			std::cout << "/n";
		} else {
			std::cout << buffer[i];
		}

	}

	std::cout << " ]]]" << std::endl;
}

void flexCharManager::tests() {

	
	char* text1 = alloc_chars(3);
	std::cout << "free slot start is at buffer index: " << free_slot_start(3) << std::endl;
	char* text2 = alloc_chars(5);
	std::cout << "free slot start is at buffer index: " << free_slot_start(3) << std::endl;
	char* text3 = alloc_chars(4);
	std::cout << "free slot start is at buffer index: " << free_slot_start(3) << std::endl;
	
	draw_buffer();

	free_chars(text1);
	draw_buffer();
	free_chars(text2);
	draw_buffer();

	char* text4 = alloc_chars(6);
	draw_buffer();
	char* text5 = alloc_chars(10);
	draw_buffer();
	free_chars(text3);
	draw_buffer();
	char* text6 = alloc_chars(6);
	draw_buffer();

	// Impropper free_chars
	char error = 5;
	free_chars(&error);

	

	int alloc_holder_len = 10;
	char** alloc_holder = new char*[alloc_holder_len];

	for (int i = 0; i < alloc_holder_len; i ++) {
		//std::cout << "free slot for "  << i << " length mem is at buffer index: " << free_slot_start(i) << std::endl;
		alloc_holder[i] = alloc_chars(i+1);
		draw_buffer();
	} 

	//std::cerr << "140 physical_location: " << (void*)used_memory[140]->physical_location << std::endl;

	for (int i = 0; i < alloc_holder_len; i ++) {
		free_chars(alloc_holder[i]);
		draw_buffer();
	} 

	delete [] alloc_holder;



  	//new_mem_block(7, 0, 3);
  	//remove_mem_block(0);
  	std::cout << "free slot start is at buffer index: " << free_slot_start(3) << std::endl;
  	//std::cout << block_to_buf_start_index(1) << std::endl;

  	
}

