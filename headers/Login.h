// Muhammad Haekal Al Ghifary <2006577605>
struct Credential{ 
	char username[SIZE];
	char password[SIZE];   
};

// hide cursor agar blinking tidak keliatan
void HideCursor(){
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}

int login_comparison(char user_input[], char login_info[], int *flag, int *iterator){
	if (strcmp(user_input, login_info) == 0){
		*flag = 1;
		*iterator = count_lines("credential/login.txt");
	}
}

int is_login_valid(struct Credential input_cred){
	int i;
	int FOUND = 0;
	char filename[] = "credential/login.txt";
	FILE *file = fopen(filename, "r"); 
	
	if (file == NULL){
        printf("Gagal untuk membuka %s.\n", filename);
        exit(0);
    }
    
	char combine_cred[SIZE];
	strcpy(combine_cred, input_cred.username);
	strcat(combine_cred, ":");
	strcat(combine_cred, input_cred.password);
	strcat(combine_cred, "\n");
	
	char file_login[SIZE];
	int lines = count_lines(filename);

	#pragma omp parallel num_threads(4) 
	{	// cari login info secara parallel
		#pragma omp for 
		for(i = 0; i < lines; i++){
	        fgets(file_login, sizeof(file_login), file);

			#pragma omp critical
			login_comparison(combine_cred, file_login, &FOUND, &i); 	
	    }
	}

	fclose(file);
    return FOUND;
}

void login_prompt(char **user){
	int i = 0;
	char char_pass;
	struct Credential login_info;
	
	while(1){
		printf("Username:\n");
		printf("Password: ");
		
		strcpy(login_info.username, "");
		SetCursorPosition(10, 0);
		scanf("%s", login_info.username);
		SetCursorPosition(10, 1);
		
		// hide password with asterisk
		i = 0;
		strcpy(login_info.password, ""); // flush the last password
		while(1){
			char_pass = getch();
			if (char_pass == 13) break;
			
			login_info.password[i] = char_pass;
			printf("*");
			i++;
		}
		
		system("cls");
		if (is_login_valid(login_info)){
			HideCursor();
			
			// pisah @gmail.com dan pass ke parameter user
			char *token;
			*user = malloc(SIZE * sizeof(char));
			token = strtok(login_info.username, "@");
			strcpy(*user, token);
			
			break;
		}
		else{
			SetCursorPosition(0, 2);
			printf("\nUsername dan password tidak ditemukan!");
			SetCursorPosition(0, 0);
		}	
	}	
}
