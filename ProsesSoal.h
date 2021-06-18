#define SIZE 256 // besarnya buffer untuk struct

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
				else if (rem == 0) strcpy(temp.jawaban_d, line);
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
		printf("[-] Nomor baris %d.", num_lines);
		return 0;
	}
	else{
		int i, j;
		int max_section = num_lines/5;
		struct Soal_N_Jawaban section;
		
		char *token; 
		char cmp_jawaban[4][3] = {{"A."}, {"B."}, {"C."}, {"D."}};
		char temp_jawaban[4][3];
		
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
					printf("[-] Cek baris %d.", (i-1)*5 + j + 1);
					return 0;
				}
			}		
		}	
	}		
}








