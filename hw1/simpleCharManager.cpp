#include <cstddef>
#include <iostream>
#include "simpleCharManager.h"



simpleCharManager::simpleCharManager(){
	free_place = buffer;
	for (int i = 0; i<BUF_SIZE; i++) {
		buffer[i] = 0;
	}
}

simpleCharManager::~simpleCharManager(){

}
             
char* simpleCharManager::alloc_chars(int n){
	int max_alloc_len = ((int)( &(buffer[BUF_SIZE-1]) - 
		free_place) + (int)sizeof(char))/(int)sizeof(char);

	// alloc if space is availible in buffer
	if (n > 0 && n <= max_alloc_len) {
		char* alloc_ptr = free_place;
		free_place = free_place + n;
		return alloc_ptr;
	} else {
        return NULL;
	}
}

void simpleCharManager::free_chars(char* p){

	// check if p is within allocated memory
	if (p<free_place && p >= buffer) {
		char* old_free_place = free_place;
		free_place = p;
		while (free_place < old_free_place) {
			*free_place = 0;
			free_place ++;
		}
		free_place = p;

	}

	else {
	}
}         
