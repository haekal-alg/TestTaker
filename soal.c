#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <omp.h>
#include "headers/ProsesSoal.h"
#include "headers/Login.h"
//#include "WriteAndGrade.h"

int main(){
	//login_prompt(); 
	
	// ============== SETUP =================
	int TIME = 2*60 + 2%60; // M : S
	char filename[] = "sample.txt";
	// ======================================
	
	//int nilai = 0;
	//int front = 0, back = 0;
	//char jawaban[SIZE1]
	//char jwb_sementara[SIZE1][SIZE1];
	
	int ujian_berlangsung = 1;
	int *FLAG = &ujian_berlangsung;

	if (is_file_valid(filename))
	{
		#pragma omp parallel sections 
		{	
			#pragma single
			HideCursor();
			//login_prompt(); 
			
			#pragma omp section 
	        { 
	            timer(TIME, FLAG); 
	        }
	        #pragma omp section
	        { 
	        	// sleep sementara supaya timer di print duluan
	        	Sleep(100); 			
				display_test(filename, FLAG); 

	        } 
		}		
	}
	
	
	
	return 0;
}


