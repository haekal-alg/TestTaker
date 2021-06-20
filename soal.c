#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "ProsesSoal.h"
#include "WriteAndGrade.h"

#define SIZE1 5 //jumlah soal ujian yang akan ditampilkan

void display(char jwb_sementara[SIZE1][SIZE1], char filename[]); //function prototype

int main(){
	char filename[] = "sample.txt";
	int nilai = 0;
	int front = 0, back = 0;
	char jawaban[SIZE1]
	char jwb_sementara[SIZE1][SIZE1];
	
	if (is_file_valid(filename)){
		display_test(filename);
	}
	
	return 0;
}