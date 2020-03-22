
#include "dictionary.h"

#include "memory.h"

#include <stdlib.h>
#include <stdbool.h>

static dictionary_functions dictf;
static dict* _dict = NULL;

void* alloc(int size, int count) {
	if (_dict == NULL) {
		setup_dictionary_functions_struct(&dictf);
		_dict = dictf.create();
	}
	pointer* ptr = calloc(1, sizeof(pointer));
	ptr->count = count;
	ptr->size = size;
	ptr->retain = 1;
	ptr->ptr = calloc(count, size);
	dictf.add(_dict, ptr->ptr, ptr, NULL);
	return ptr->ptr;
}

void* re_alloc(void* ptr, int add) {
	pointer* _ptr = dictf.get(_dict, ptr, NULL);
	if (_ptr == NULL) {
		return NULL;
	}
	else {
		_ptr->ptr = realloc(_ptr->ptr, _ptr->size * (_ptr->count + add));
		_ptr->count = _ptr->count + add;
		return _ptr->ptr;
	}
}

int retain(void* ptr) {
	pointer* _ptr = dictf.get(_dict, ptr, NULL);
	if (!_ptr)
		return -1;
	_ptr->retain++;
	return _ptr->retain;
}

int release(void** ptr) {
	pointer* _ptr = dictf.get(_dict, *ptr, NULL);
	if (!_ptr)
		return -1;
	_ptr->retain--;
	if (_ptr->retain <= 0) {
		dictf.remove(_dict, _ptr->ptr, NULL, true);
        *ptr = 0;
		return 0;
	}
	return _ptr->retain;
}

bool mem_exists(void* ptr) {
	pointer* _ptr = dictf.get(_dict, ptr, NULL);
	if (_ptr)
		return true;
	return false;
}

bool mem_isValid(void* ptr) {
	pointer* _ptr = dictf.get(_dict, ptr, NULL);
	if (_ptr)
		if (_ptr->retain > 0)
			return true;
	return false;
}

int retains(void* ptr) {
	pointer* _ptr = dictf.get(_dict, ptr, NULL);
	if (_ptr)
		return _ptr->retain;
	return -1;
}



void setup_memory_functions(memory_functions* memf) {
	memf->alloc = &alloc;
	memf->exists = &mem_exists;
	memf->isValid = &mem_isValid;
	memf->realloc = &re_alloc;
	memf->release = &release;
	memf->retain = &retain;
	memf->getRetains = &retains;
}
