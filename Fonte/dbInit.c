#include "buffend.h"

void dbInit() {
	if(system("mkdir data > /dev/null 2>&1") == -1)
		printf("ERROR: It was not possible to initialize ibtres\n");;
	createDB("ibetres");
}