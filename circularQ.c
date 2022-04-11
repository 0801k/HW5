#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; // char 형 element를 생성한다
typedef struct { // 구조체를 선언한다
	element queue[MAX_QUEUE_SIZE]; 
	int front, rear; // front 와 rear을 생성한다
}QueueType;

QueueType *createQueue(); // 큐를 초기화한다
int freeQueue(QueueType *cQ); // 공간을 해제한다
int isEmpty(QueueType *cQ); // 공백상태인 큐
int isFull(QueueType *cQ); // 포화상태인 큐
void enQueue(QueueType *cQ, element item); // cQ에 queue에 넣는다
void deQueue(QueueType *cQ, element* item); // cQ에 queue를 뺀다
void printQ(QueueType *cQ); // 큐의 현재 상태를 출력한다
void debugQ(QueueType *cQ); // 큐 안의 값을 출력한다
element getElement(); // 사용자로부터 데이터를 입력받는다


int main(void)
{
    printf("[----- [노관범]  [2020039102] -----]\n");

	QueueType *cQ = createQueue(); // 큐를 생성한다
	element data; // stack 영역에 char형 변수 data를 생성한다

	char command; // 변수 command

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령어를 입력받는다

		switch(command) {  
		case 'i': case 'I': //  i 또는 I 일 경우
			data = getElement(); // 데이터를 입력받아 data에 할당한다
			enQueue(cQ, data); // enQueue() 함수 호출
			break;
		case 'd': case 'D': // d 또는 D 일 경우
			deQueue(cQ,&data); // deQueue() 함수 호출
			break;
		case 'p': case 'P': // p 또는 P 일 경우
			printQ(cQ); // printQ() 함수 호출
			break;
		case 'b': case 'B': // b 또는 B 일 경우
			debugQ(cQ); // debugQ() 함수 호출
			break;
		case 'q': case 'Q': // q 또는 Q 일 경우
			break;

		default: // 이외의 명령어 입력시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 경고문구 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // q와 Q를 입력받지 않았을 때 반복한다
	return 1;
}

QueueType *createQueue() // 원형 큐를 초기화한다
{
	QueueType *cQ; // QueueType의 포인터 = cQ
	cQ = (QueueType *)malloc(sizeof(QueueType));  // cQ 에 QueueType으로 주소를 할당한다
	cQ->front = 0; //front를 0으로 재설정 한다
	cQ->rear = 0; // rear을 0으로 재설정 한다
	return cQ; // cQ 주소 반환
}

element getElement()
{
	element item; // element 로 변수 item을 선언한다
	printf("Input element = ");
	scanf(" %c", &item); // item 값을 받는다
	return item; // item을 반환한다
}

int isEmpty(QueueType *cQ) // 공백상태인 큐 인지 검사한다
{
	if (cQ->front == cQ->rear){ // front 값과 rear 값이 같다면
		printf("Circular Queue is empty!"); // 원형큐가 비어있다는 문구 출력
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ) // 포화상태인 큐 인지 검사한다
{
     
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) // rear의 값을 1만큼씩 증가한다 rear=front가 되면 포화상태라면
    {
		printf(" Circular Queue is full!"); // 원형큐가 가득 차있다는 문구를 출력한다
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item) // queue에 item 할당한다
{
	if(isFull(cQ)) return; // 큐가 포화 됐을시 중단한다
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
        // rear에 (rear+1)%MAX_QUEUE_SIZE 연산을 한 후 그 결과를 할당한다
		cQ->queue[cQ->rear] = item; 
        // cQ[rear] 에 item을 삽입한다
	}
}

void deQueue(QueueType *cQ, element *item) 
// cQ가 가리키는 곳에서 queue[front] 를 빼낸다
{
	if(isEmpty(cQ)) exit(1); // 공백의 큐 인지 검사한다
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; 
        // 나머지 연산자를 이용해 front 변수를 이동한다 front = front + 1
		cQ->queue[cQ->front]; // item이 가리키는 곳에 front를 할당한다
		return;
	}
}

void printQ(QueueType *cQ) // queue에서 들어있는 값을 출력한다
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
     // MAX_QUEUE_SIZE 값을 cQ->first에 할당한다
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
    // MAX_QUEUE_SIZE 값을 last에 할당한다

	printf("Circular Queue : ["); // queue에서 들어있는 인덱스를 출력한다

	i = first; // i에 first의 값을 할당한다
	while(i != last){ // i 값이 last 가 아닐 경우 출력한다
		printf("%3c", cQ->queue[i]); // queue의 요소를 출력한다
		i = (i+1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ) // 큐 안의 값을 출력한다
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // MAX_QUEUE_SIZE 만큼 반복한다
	{
		if(i == cQ->front) // i가 cQ의 front와 일치한다면
        {
			printf("  [%d] = front\n", i); // i를 출력한다
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //queue의 요소들을 출력한다
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // cQ의 front와 rear을 출력한다
}