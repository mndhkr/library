
typedef struct pointer {
	void* ptr;
	int retain;
	int size;
	int count;
} pointer;


typedef struct memory_functions {
	void* (*alloc)	(int size, int count);
	void* (*realloc)	(void* ptr, int add);
	int		(*retain)	(void* ptr);
	int		(*release)	(void** ptr);
	bool	(*exists)	(void* ptr);
	bool	(*isValid)	(void* ptr);
	int		(*getRetains)(void* ptr);
} memory_functions;


void setup_memory_functions(memory_functions* memf);


void* alloc(int size, int count);
void* re_alloc(void* ptr, int add);
int retain(void* ptr);
int release(void** ptr);
bool mem_exists(void* ptr);
bool mem_isValid(void* ptr);
int retains(void* ptr);

