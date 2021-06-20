#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <omp.h>
#include "ProsesSoal.h"
//#include "WriteAndGrade.h"

int main(){
	//int nilai = 0;
	//int front = 0, back = 0;
	//char jawaban[SIZE1]
	//char jwb_sementara[SIZE1][SIZE1];
	
	int TIME = 2*60 + 2%60; // M : S
	char filename[] = "sample.txt";
	
	int ujian_berlangsung = 1;
	int *FLAG = &ujian_berlangsung;
	// current issue:
	// 1. (possible) racing antara timer dan proses ujian
	// 2. install clear screen pas enter di pencet
	if (is_file_valid(filename)){
		#pragma omp parallel sections 
		{
			#pragma omp section 
	        { 
	            timer(TIME, FLAG); 
	        }
	        #pragma omp section
	        { // ############ PROSES UJIAN ###############
	        	// sleep sementara supaya timer di print duluan
	        	Sleep(100); 			
				display_test(filename, FLAG); 
				//Sleep(50); 
				
	        } // ############ PROSES UJIAN ###############	
		}		
	}
	return 0;
}
