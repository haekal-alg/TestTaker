#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <omp.h>
#include "headers/ProsesSoal.h"
#include "headers/Login.h"
#include "headers/WriteAndGrade.h"
	
int main(){
	// ============== SETUP =================
	int TIME = 1*60 + 1%60; // M : S
	char filename[] = "sample.txt";
	// ======================================
	
	int ujian_berlangsung = 1;
	int *FLAG = &ujian_berlangsung;
	
	//float nilai;
	//queue *q;
    //q = malloc(sizeof(queue));
    //initialize(q);
        
	if (is_file_valid(filename))
	{
		#pragma omp parallel 
		{	
			// selesaikan dulu login baru lanjut ke proses selanjutnya
			#pragma omp single
			login_prompt(); 
		
			// jalankan timer dan test secara bersamaan
			#pragma omp single nowait
			{
				#pragma omp task
				{ 
		            timer(TIME, FLAG); 
		        }
		        #pragma omp task
		        { 
		        	// sleep sementara supaya timer di print duluan
		        	Sleep(100); 			
					display_test(filename, FLAG); 
	
		        }
			}
		}
		system("cls");
		printf("SHOW GRADE");		
	}
	return 0;
}

