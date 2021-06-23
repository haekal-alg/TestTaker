// struct untuk node 
struct node{
    char data;
    struct node *next;
};
typedef struct node node;

// struct untuk front back dan count
struct queue{
    node *front;
    node *back;
};
typedef struct queue queue;

// Alvito Ikramu Walidain <2006577624>
// inisialisasi nilai front, back, dan count 0
void initialize(queue *q){
    q->front = NULL;
    q->back = NULL;
}

// Alvito Ikramu Walidain <2006577624>
// cek jika queue kosong
int isempty(queue *q){
    return (q->back == NULL);
}

// Alvito Ikramu Walidain <2006577624>
// fungsi untuk menambahkan char ke queue
void enqueue(queue *q, char value){
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
}
// Alvito Ikramu Walidain <2006577624>
// fungsi untuk menghapus char dengan prinsip FIFO
char dequeue(queue *q){
    node *tmp;
    char n = q->front->data;
    
    tmp = q->front;
    q->front = q->front->next;
    free(tmp);
    
    return(n);
}
// Alvito Ikramu Walidain <2006577624>
// fungsi untuk menghitung nilai user berdasarkan jumlah benar dan total soal
// dengan menggunakan queue
float grade_test(char jawaban[]){
	// init jawaban yang benar dengan queue	
	queue *answer;
    answer = malloc(sizeof(queue));
    initialize(answer);
    
    enqueue(answer, 'a'); // 1
    enqueue(answer, 'd'); // 2
    enqueue(answer, 'b'); // 3
    enqueue(answer, 'd'); // 4
    enqueue(answer, 'b'); // 5
    enqueue(answer, 'a'); // 6
    enqueue(answer, 'c'); // 7
    enqueue(answer, 'b'); // 8
    enqueue(answer, 'a'); // 9
    enqueue(answer, 'b'); // 10
    
    // ubah 1-4 ke a-d
    int i;
    char filename[] = "sample.txt";
    int banyak_soal = count_lines(filename)/5;
    
    // compare dengan jawaban user
	float correctAns = 0;
	for(i = 0; i < banyak_soal; i++){
		if (jawaban[i] == answer->front->data){
			correctAns++;	
		}
		dequeue(answer);
	}

	return (correctAns/banyak_soal)*100;
}
// Alvito Ikramu Walidain <2006577624>
// fungsi untuk menyimpan hasil dari ujian ke dalam teks file
void write_jawaban_to_file(char username[], char jawaban_sementara[], float nilai){
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
	fprintf(file, "%s; %s; %.2f\n", username, jawaban_sementara, nilai);
	
	printf("Submitted %d/%d/%d, ", myTime->tm_mday, myTime->tm_mon+1, myTime->tm_year+1900);	
	printf("%02d:%02d.\n",  myTime->tm_hour, myTime->tm_min);
	printf("Username: %s\n", username);
	printf("Grade = %.2f/100\n", nilai);
	fclose(file);
}


