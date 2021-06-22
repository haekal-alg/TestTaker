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
	int i;
	char *username;
	int banyak_soal = count_lines(filename)/5;
	
	int *jawaban;
	jawaban = (int*)calloc(banyak_soal, sizeof(int));
	
	if (is_file_valid(filename))
	{
		int ujian_berlangsung = 1;
		int *FLAG = &ujian_berlangsung;
		#pragma omp parallel 
		{	
			// selesaikan dulu login baru lanjut ke proses selanjutnya
			#pragma omp single
			login_prompt(&username); 
		
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
					display_test(filename, FLAG, jawaban); 
	
		        }
			}	
		}
		// block penilaian
		system("cls");
		// ubah 1-4 ke a-d
		char jawaban_converted[banyak_soal];
		for (i = 0; i < banyak_soal; i++){
			if (jawaban[i] == 0) jawaban_converted[i] = '-';
			else jawaban_converted[i] = (char)(96+jawaban[i]);
		} 
		jawaban_converted[banyak_soal] = '\0';
		free(jawaban);
		
		float nilai = grade_test(jawaban_converted);
		write_jawaban_to_file(username, jawaban_converted, nilai);
	}
	
	return 0;
}

