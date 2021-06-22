// struct untuk node 
struct node{
    char data;
    struct node *next;
};
typedef struct node node;

// struct untuk front back dan count
struct queue{
    int count;
    node *front;
    node *back;
};
typedef struct queue queue;

// inisialisasi nilai front, back, dan count 0
void initialize(queue *q){
    q->count = 0;
    q->front = NULL;
    q->back = NULL;
}

// cek jika queue kosong
int isempty(queue *q){
    return (q->back == NULL);
}

// fungsi untuk menambahkan char ke queue
void enqueue(queue *q, char value, int banyak_soal){
    if (q->count < banyak_soal){
        node *tmp;
        tmp = malloc(sizeof(node));
        tmp->data = value;
        tmp->next = NULL;
        
        if(!isempty(q)){
            q->back->next = tmp;
            q->back = tmp;
        }
        else{
            q->front = q->back = tmp;
        }
        q->count++;
    }
    else
        printf("Jawaban penuh\n");
}

// fungsi untuk menghapus char dengan prinsip FIFO
char dequeue(queue *q){
    node *tmp;
    char n = q->front->data;
    
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    
    return(n);
}

// fungsi untuk menghitung nilai user berdasarkan jumlah benar dan total soal
float grade_test(char jawaban_sementara[]){
	int i;
	float grade;
	int correctAns = 0;
	
	char filename[] = "sample.txt";
	int banyak_soal = count_lines(filename)/5; 
	
	// answer start from 1
	char answer[] = "adbdbacbab";

	for(i = 0; i < banyak_soal; i++){
		if (jawaban_sementara[i] == answer[i]){
			correctAns++;
		}
	}
	
	grade = ((float)correctAns/banyak_soal)*100;
	
	return grade;
}

// fungsi untuk menyimpan hasil dari ujian ke dalam teks file
void write_jawaban_to_file(char username[], char jawaban_sementara[]){
	time_t currentTime;
	time(&currentTime);
	
	char filename[] = "credential/skor.txt";
	
	FILE *file = fopen(filename, "a");
	
	if (file == NULL){
        printf("Gagal untuk membuka %s.\n", filename);
        exit(0);
    }
	
	// DATE
	struct tm *myTime = localtime(&currentTime);
	fprintf(file, "%d/%d/%d, ", myTime->tm_mday, myTime->tm_mon+1, myTime->tm_year+1900);
	fprintf(file, "%02d:%02d; ",  myTime->tm_hour, myTime->tm_min);
	
	// biodata dan nilai
	float nilai = grade_test(jawaban_sementara);
	fprintf(file, "%s; %s; %.2f\n", username, jawaban_sementara, nilai);
											    
	fclose(file);
}


