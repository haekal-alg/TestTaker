//fungsi untuk menghitung nilai user berdasarkan jumlah benar dan total soal
float get_grade(char jawaban_sementara[]){
  
  FILE *fptr = fopen("jawab.txt", "r");
  char answer[150];
  fgets(answer, 150, fptr);

  int banyak_soal = strlen(answer); 
  int correctAns = 0;
  float grade = 0;
  int i;

  for(i=0; i < banyak_soal; i++){
		if(jawaban_sementara[i] == answer[i]){
			correctAns ++;
		}
	}
	grade = (float)correctAns/banyak_soal;
	fclose(fptr);
	return grade;

}


//fungsi untuk menampilkan nilai user setelah menjawab soal
void display_grade(float nilai){
	printf("Your final grade is %.2f\n", grade);
}


//fungsi untuk menyimpan hasil dari ujian ke dalam teks file
void write_jawaban(char nama[], int npm, char jawaban_sementara[], float nilai)
{
	time_t currentTime;
	time(&currentTime);
	struct tm *myTime = localtime(&currentTime);
	
	FILE *fptr = fopen(file_data_dan_jawaban, "a");
	fprintf(fptr, "%s-%s-%s-%.2f-%i/%i/%i, %i:%i", nama, npm, jawaban_sementara, nilai, myTime->tm_mday, myTime->tm_mon + 1, myTime->tm_year + 1900, myTime->tm_hour,
	        myTime->tm_min);
	fclose(fptr);
}

//struct untuk node 
struct node
{
    char data;
    struct node *next;
};
typedef struct node node;
//struct untuk front back dan count
struct queue
{
    int count;
    node *front;
    node *back;
};
typedef struct queue queue;
//inisialisasi nilai front, back, dan count 0
void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->back = NULL;
}
//cek jika queue kosong
int isempty(queue *q)
{
    return (q->back == NULL);
}
//fungsi untuk menambahkan char ke queue
void enqueue(queue *q, char value, int banyak_soal)
{
    if (q->count < banyak_soal)
    {
        node *tmp;
        tmp = malloc(sizeof(node));
        tmp->data = value;
        tmp->next = NULL;
        if(!isempty(q))
        {
            q->back->next = tmp;
            q->back = tmp;
        }
        else
        {
            q->front = q->back = tmp;
        }
        q->count++;
    }
    else
    {
        printf("Jawaban penuh\n");
    }
}
//fungsi untuk menghapus char dengan prinsip FIFO
char dequeue(queue *q)
{
    node *tmp;
    char n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return(n);
}



