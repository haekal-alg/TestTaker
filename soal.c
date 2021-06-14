#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProsesSoal.h"

int main(){
	struct Soal_N_Jawaban section; 
	
	section_to_struct(&section, "sample.txt", 4);
	
	printf("%s", section.soal);
	printf("%s", section.jawaban_a);
	printf("%s", section.jawaban_b);
	printf("%s", section.jawaban_c);
	printf("%s", section.jawaban_d);
	
	return 0;
}

