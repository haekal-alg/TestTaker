#define SIZE 256 // besarnya buffer untuk struct
#define ESC 27
#define RED 12
#define WHITE 15

// untuk mempermudah penamaan, 
// kumpulan soal dan jawaban dinamakan section
struct Soal_N_Jawaban{ 
	char soal[SIZE];	   
	char jawaban_a[SIZE];
	char jawaban_b[SIZE];
	char jawaban_c[SIZE];
	char jawaban_d[SIZE];
};

// menghitung banyaknya line pada file
int count_lines(char filename[]){
	char c;
	int count = 1;
	FILE *file = fopen(filename, "r"); 
	
	if (file == NULL){
        printf("Gagal untuk membuka %s.\n", filename);
        exit(0);
    }
    
	for (c = getc(file); c != EOF; c = getc(file)){
		// jika menemukan newline maka increment
		if (c == '\n') count++;
	}
    fclose(file);
	return count;	
}

// fungsi ini mengkopi section ke-n dari file yang telah ditentukan ke struct
void section_to_struct(struct Soal_N_Jawaban *pointer_section, char filename[], int section_num){
	struct Soal_N_Jawaban temp;
	
	temp = *pointer_section;
	FILE *file = fopen(filename, "r"); 

	if (file == NULL){
        printf("Gagal untuk membuka %s.\n", filename);
        exit(0);
    }
    
	// tiap section mempunyai 5 bagian. point ke section n berarti
	// read 5 line mulai dari (section_num-1)*5+1
	int n = (section_num - 1) * 5 + 1;  // batas bawah
	int m = n + 5;	   				    // batas atas
	int max_section = count_lines(filename)/5;

	// kembalikan null jika jumlah section tidak sesuai dengan yang ada di file
	if (section_num < 0 || section_num > max_section){
		temp.soal[0] = '\0';
		temp.jawaban_a[0] = '\0';
		temp.jawaban_b[0] = '\0';
		temp.jawaban_c[0] = '\0';
		temp.jawaban_d[0] = '\0';
	}
	else{
		char line[SIZE];
		int line_num = 1;
		int rem;
		
		while (fgets(line, sizeof(line), file)){
			if (line_num == m){
				break;
			}
			if (line_num >= n && line_num < m){
				rem = line_num % 5;
				if (rem == 1) strcpy(temp.soal, line);
				else if (rem == 2) strcpy(temp.jawaban_a, line);
				else if (rem == 3) strcpy(temp.jawaban_b, line);
				else if (rem == 4) strcpy(temp.jawaban_c, line);
				else if (rem == 0){ 
					// tambah newline pada baris terakhir di file
					strcpy(temp.jawaban_d, line);
					if (line_num == max_section*5) strcat(temp.jawaban_d, "\n");
				}
			}	
			line_num++;
		}
	}

	*pointer_section = temp;
	fclose(file);
}

int is_file_valid(char filename[]){
	/* 
	Syarat file text valid:
	1. Terdiri dari 5*n baris.
	2. Baris dari awal section berupa soal 1 baris diikuti 4 baris jawaban,
	   4 baris jawaban diawali dengan "A.", "B.", "C." dan "D."
	*/
	FILE *file = fopen(filename, "r"); 
	int num_lines = count_lines(filename);
	
	if (file == NULL){
        printf("Gagal untuk membuka %s.\n", filename);
        exit(0);
    }
	
	if (num_lines % 5 != 0){
		printf("[-] File tidak valid! Pastikan nomor baris benar!\n");
		printf("[*] Nomor baris %d.", num_lines);
		return 0;
	}
	else{
		int i, j;
		int max_section = num_lines/5;
		struct Soal_N_Jawaban section;
		
		char *token; 
		char cmp_jawaban[4][3] = {{"A."}, {"B."}, {"C."}, {"D."}};
		char temp_jawaban[4][3];
		
		// cek tiap baris jawaban apakah sesuai dengan syarat
		for (i = 1; i <= max_section; i++){
			section_to_struct(&section, filename, i);
			
			token = strtok(section.jawaban_a, " ");
			strcpy(temp_jawaban[0], token);
			
			token = strtok(section.jawaban_b, " ");
			strcpy(temp_jawaban[1], token);
			
			token = strtok(section.jawaban_c, " ");
			strcpy(temp_jawaban[2], token);
			
			token = strtok(section.jawaban_d, " ");
			strcpy(temp_jawaban[3], token);
			
			for (j = 0; j < 4; j++){
				if (strcmp(temp_jawaban[j], cmp_jawaban[j]) != 0){
					printf("[-] File tidak valid! Pastikan format soal benar!\n");
					printf("[*] Cek baris %d.", (i-1)*5 + j + 1);
					return 0;
				}
			}		
		}	
	}		
}

void SetCursorPosition(int XPos, int YPos){
	COORD coord;
	coord.X = XPos; 
	coord.Y = YPos;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void timer(int time, int *flag_ujian){
	int minutes, seconds, count = 0;
	int sleep_interval = 50;
	int REFRESH_RATE = 1000/sleep_interval; // 20 fps
	
	while (time >= 0 && *flag_ujian){
		minutes = time / 60;
		seconds = time % 60;
		
		// adjust cursor position as necessary
		SetCursorPosition(0, 0);
		printf("  TIMER %02d:%02d", minutes, seconds);
		SetCursorPosition(0, 2);
		
		if (count == REFRESH_RATE){
			time -= 1;
			count = 0;	
		}
		count += 1; 			// perbesar refresh rate (perkecil interval sleep)
		Sleep(sleep_interval);  // agar timer lebih smooth
	}
	*flag_ujian = 0;
	
	// show grade here
	system("cls");
	#pragma omp critical
	printf("SHOW GRADE HERE");
}

// fungsi untuk menampilkan soal sekaligus menerima jawaban,
// berfungsi juga sebagai navigasi soal (berpindah dari satu soal ke soal yang lain)
void display_test(char filename[], int *flag_ujian){
	int i, j;
	int num = 1;  // nomor soal sekarang;
	char ch, container_jawaban[4][SIZE]; // soal yang ada di struct dipindahkan
										 // ke container agar bisa di loop
	struct Soal_N_Jawaban section;
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// jumlah soal ujian yang akan ditampilkan
	int banyak_soal = count_lines(filename)/5; 
	int jwbn_sementara[banyak_soal];
	
	for (j = 0; j < banyak_soal; j++) jwbn_sementara[j] = 0; 

	while(*flag_ujian){
		section_to_struct(&section, filename, num);
		strcpy(container_jawaban[0], section.jawaban_a); 
		strcpy(container_jawaban[1], section.jawaban_b);
		strcpy(container_jawaban[2], section.jawaban_c); 
		strcpy(container_jawaban[3], section.jawaban_d); 
		
		printf("  Question %d out of %d\n", num, banyak_soal);
		printf("  %s", section.soal);
		for (i = 0; i < 4; i++){
			// cek yang telah dipilih sebelumnya 
			// jika ada yang telah dijawab maka akan dihighlight
			int is_highlight = (jwbn_sementara[num] != 0 && jwbn_sementara[num] == i+1);
			
			if (is_highlight) SetConsoleTextAttribute(h, RED);
			printf("     %s", container_jawaban[i]);			
			if (is_highlight) SetConsoleTextAttribute(h, WHITE);
				
		}
		printf("\n  <<<(1)");
		for (i = 0; i < strlen(section.soal)-13; i++) printf(" ");
		printf("(0)>>>\n")	;

		// =============== NAVIGASI SOAL ===============
		ch = getch();
		//printf("%s", flag_ujian);
		// jika ditekan ESC maka konfirmasi test selesai
		if (ch == ESC){
			SetCursorPosition(0, 11);
			printf("Apakah anda yakin ingin menyelesaikan ujian? <Y/N>");
			
			ch = getch();
			if (ch == 'y' || ch == 'Y') *flag_ujian = 0;
			else{
				system("cls");
				continue;	
			} 
		}
		
		// lakukan navigasi jika dideteksi 1 atau 0
		if (ch == 49)      // jika angka 1 ditekan maka program akan menampilkan soal sebelumnya
			num--;         
		else if (ch == 48) // jika angka 0 ditekan maka program akan menampilkan soal selanjutnya 
			num++;         
		
		// limit agar tidak bisa berpindah kurang dari 1 
		// atau melewati batas maks soal
		if (num < 1) num = 1;
		else if (num > banyak_soal) num = banyak_soal;
		
		// =============== INPUT JAWABAN ===============
		// mengecek setiap jawaban user
		if ((ch >= 'a' && ch <= 'd') || (ch >= 'A' && ch <= 'D')){
			if (ch == 'a' || ch == 'A') jwbn_sementara[num] = 1;
			else if (ch == 'b' || ch == 'B') jwbn_sementara[num] = 2;	
			else if (ch == 'c' || ch == 'C') jwbn_sementara[num] = 3;
			else if (ch == 'd' || ch == 'D') jwbn_sementara[num] = 4;
		}
					
		if (*flag_ujian) system("cls");
		SetCursorPosition(0, 2);
	}
}

