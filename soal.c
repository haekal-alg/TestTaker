#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ProsesSoal.h"

int main(){
	char filename[] = "sample.txt";
	
	if (is_file_valid(filename)){
		display_test(filename);
	}
	
	return 0;
}

