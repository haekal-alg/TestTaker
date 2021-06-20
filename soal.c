#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "ProsesSoal.h"
#define SIZE1 10 //jumlah soal ujian yang akan ditampilkan

void display(char jwb_sementara[SIZE1][SIZE1], char filename[]); //function prototype

int main(){
	struct Soal_N_Jawaban section; 
	char filename[] = "sample.txt";
	
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
		if(i == SIZE1){
			printf("\n");
		}
		printf("\nJawaban: ");
		scanf("%s", &jwb_sementara[i]);
		
		while(strcmpi(jwb_sementara[i], "A") != 0 && strcmpi(jwb_sementara[i], "B") != 0 && strcmpi(jwb_sementara[i], "C") != 0 && strcmpi(jwb_sementara[i], "D") != 0){
			printf("\nJAWABAN TIDAK VALID!!");
			printf("\nMasukkan kembali jawaban: ");
			scanf("%s", &jwb_sementara[i]);
		}//error handling
		
		//mengecek setiap jawaban user, jawaban yang dipilih oleh user akan dihighlight
		//jika jawaban yang diinput user adalah A maka pilihan jawaban A akan dihighlight
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
		
		//jika jawaban yang diinput user adalah B maka pilihan jawaban B akan dihighlight
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
		
		//jika jawaban yang diinput user adalah C maka pilihan jawaban C akan dihighlight
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
		
		//jika jawaban yang diinput user adalah D maka pilihan jawaban D akan dihighlight
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
		
		if(i == SIZE1){
			printf("\n");
		}
		printf("\n<<<<\t\t\t\t\t\t\t\t\t\t\t\t\t\t>>>>\n");
		
		int cek1 = 0; //variabel untuk looping dalam navigasi soal
		int cek2; //variabel untuk mengecek tombol yang ditekan oleh user
		
		//navigasi soal berupa pilihan untuk pindah ke soal berikutnya atau pindah ke soal sebelumnya
		while(cek1 == 0){
			printf("\n\tTekan Angka 1 Untuk Lanjut Ke Soal Berikutnya Atau Tekan Angka 0 untuk Kembali Ke Soal Sebelumnya\n\t");
			cek2 = getch();
			switch(cek2){
				case 49: //jika angka 1 pada keyboard ditekan maka akan keluar dari loop dan program akan menampilkan soal selanjutnya
					cek1 = 1;
					break;
				case 48: //jika angka 0 pada keyboard ditekan maka akan keluar dari loop dan program akan menampilkan soal sebelumnya karena nilai counter (i) berkurang
					i = i - 2;
					cek1 = 1;
					break;
				default:
					printf("INVALID INPUT!!\n");
					break; //error handling, jika user memberikan input selain angka 1 dan 0 maka looping akan terus berlanjut
			}
		}
		
		system("cls"); //membersihkan layar sebelum berganti ke soal berikutnya
	}
}
