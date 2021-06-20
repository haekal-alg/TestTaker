#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "ProsesSoal.h"
#include "WriteAndGrade.h"
#define SIZE1 5 //jumlah soal ujian yang akan ditampilkan

void display(char jwb_sementara[SIZE1][SIZE1], char filename[]); //function prototype

int main(){
	struct Soal_N_Jawaban section; 
	char filename[] = "sample.txt";
	int nilai = 0;
	int front = 0, back = 0;
	char jawaban[SIZE1]
	char jwb_sementara[SIZE1][SIZE1];
	
	if (is_file_valid(filename)){
		// proses
		display(jwb_sementara, filename); //memanggil fungsi display
	}

	return 0;
}

//fungsi untuk menampilkan soal sekaligus menerima jawaban, berfungsi juga sebagai navigasi soal (berpindah dari satu soal ke soal yang lain)
void display(char jwb_sementara[SIZE1][SIZE1], char filename[]){
	struct Soal_N_Jawaban section;
	int i;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//looping sebanyak jumlah soal
	for(i=1; i<=SIZE1; i++){
	
		section_to_struct(&section, "sample.txt", i);
		
		//menampilkan soal sekaligus meminta input dari user berupa jawaban
		printf("%s", section.soal);
		printf("%s", section.jawaban_a);
		printf("%s", section.jawaban_b);
		printf("%s", section.jawaban_c);
		printf("%s", section.jawaban_d);
		printf("\nJawaban: ");
		scanf("%s", &jwb_sementara[i]);
		
		while(strcmpi(jwb_sementara[i], "A") != 0 && strcmpi(jwb_sementara[i], "B") != 0 && strcmpi(jwb_sementara[i], "C") != 0 && strcmpi(jwb_sementara[i], "D") != 0){
			printf("\nJAWABAN TIDAK VALID!!");
			printf("\nMasukkan kembali jawaban: ");
			scanf("%s", &jwb_sementara[i]);
		}//error handling
		
		//mengecek setiap jawaban user, jawaban yang dipilih oleh user akan dihighlight
		if(strcmpi(jwb_sementara[i], "A") == 0){
			system("cls");
			printf("%s", section.soal);
			
			SetConsoleTextAttribute(h,12);
			printf("%s", section.jawaban_a);
			
			SetConsoleTextAttribute(h,7);
			printf("%s", section.jawaban_b);
			printf("%s", section.jawaban_c);
			printf("%s", section.jawaban_d);
		}
		
		else if(strcmpi(jwb_sementara[i], "B") == 0){
			system("cls");
			printf("%s", section.soal);
			printf("%s", section.jawaban_a);
			
			SetConsoleTextAttribute(h,12);
			printf("%s", section.jawaban_b);
			
			SetConsoleTextAttribute(h,7);
			printf("%s", section.jawaban_c);
			printf("%s", section.jawaban_d);
		}
		
		else if(strcmpi(jwb_sementara[i], "C") == 0){
			system("cls");
			printf("%s", section.soal);
			printf("%s", section.jawaban_a);
			printf("%s", section.jawaban_b);
			
			SetConsoleTextAttribute(h,12);
			printf("%s", section.jawaban_c);
			
			SetConsoleTextAttribute(h,7);
			printf("%s", section.jawaban_d);
		}
		
		else if(strcmpi(jwb_sementara[i], "D") == 0){
			system("cls");
			printf("%s", section.soal);
			printf("%s", section.jawaban_a);
			printf("%s", section.jawaban_b);
			printf("%s", section.jawaban_c);
			
			SetConsoleTextAttribute(h,12);
			printf("%s", section.jawaban_d);
			
			SetConsoleTextAttribute(h,7);
		}
		
		printf("\n<<<<\t\t\t\t\t\t\t\t\t\t\t\t\t\t>>>>\n");
		
		int cek = 0;
		int ch1;
		
		//navigasi soal berupa pilihan untuk pindah ke soal berikutnya atau pindah ke soal sebelumnya
		while(cek == 0){
			printf("\n\tTekan Angka 1 Untuk Lanjut Ke Soal Berikutnya Atau Tekan Angka 0 untuk Kembali Ke Soal Sebelumnya\n\t");
			ch1 = getch();
			switch(ch1){
				case 49:
					cek = 1;
					break;
				case 48:
					i = i - 2;
					cek = 1;
					break;
				default:
					printf("INVALID INPUT!!\n");
					break; //error handling
			}
		}
		
		system("cls"); //membersihkan layar sebelum berganti ke soal berikutnya
	}
}
