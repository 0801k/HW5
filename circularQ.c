#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; // char �� element�� �����Ѵ�
typedef struct { // ����ü�� �����Ѵ�
	element queue[MAX_QUEUE_SIZE]; 
	int front, rear; // front �� rear�� �����Ѵ�
}QueueType;

QueueType *createQueue(); // ť�� �ʱ�ȭ�Ѵ�
int freeQueue(QueueType *cQ); // ������ �����Ѵ�
int isEmpty(QueueType *cQ); // ��������� ť
int isFull(QueueType *cQ); // ��ȭ������ ť
void enQueue(QueueType *cQ, element item); // cQ�� queue�� �ִ´�
void deQueue(QueueType *cQ, element* item); // cQ�� queue�� ����
void printQ(QueueType *cQ); // ť�� ���� ���¸� ����Ѵ�
void debugQ(QueueType *cQ); // ť ���� ���� ����Ѵ�
element getElement(); // ����ڷκ��� �����͸� �Է¹޴´�


int main(void)
{
    printf("[----- [�����]  [2020039102] -----]\n");

	QueueType *cQ = createQueue(); // ť�� �����Ѵ�
	element data; // stack ������ char�� ���� data�� �����Ѵ�

	char command; // ���� command

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ��ɾ �Է¹޴´�

		switch(command) {  
		case 'i': case 'I': //  i �Ǵ� I �� ���
			data = getElement(); // �����͸� �Է¹޾� data�� �Ҵ��Ѵ�
			enQueue(cQ, data); // enQueue() �Լ� ȣ��
			break;
		case 'd': case 'D': // d �Ǵ� D �� ���
			deQueue(cQ,&data); // deQueue() �Լ� ȣ��
			break;
		case 'p': case 'P': // p �Ǵ� P �� ���
			printQ(cQ); // printQ() �Լ� ȣ��
			break;
		case 'b': case 'B': // b �Ǵ� B �� ���
			debugQ(cQ); // debugQ() �Լ� ȣ��
			break;
		case 'q': case 'Q': // q �Ǵ� Q �� ���
			break;

		default: // �̿��� ��ɾ� �Է½�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // ����� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); // q�� Q�� �Է¹��� �ʾ��� �� �ݺ��Ѵ�
	return 1;
}

QueueType *createQueue() // ���� ť�� �ʱ�ȭ�Ѵ�
{
	QueueType *cQ; // QueueType�� ������ = cQ
	cQ = (QueueType *)malloc(sizeof(QueueType));  // cQ �� QueueType���� �ּҸ� �Ҵ��Ѵ�
	cQ->front = 0; //front�� 0���� �缳�� �Ѵ�
	cQ->rear = 0; // rear�� 0���� �缳�� �Ѵ�
	return cQ; // cQ �ּ� ��ȯ
}

element getElement()
{
	element item; // element �� ���� item�� �����Ѵ�
	printf("Input element = ");
	scanf(" %c", &item); // item ���� �޴´�
	return item; // item�� ��ȯ�Ѵ�
}

int isEmpty(QueueType *cQ) // ��������� ť ���� �˻��Ѵ�
{
	if (cQ->front == cQ->rear){ // front ���� rear ���� ���ٸ�
		printf("Circular Queue is empty!"); // ����ť�� ����ִٴ� ���� ���
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ) // ��ȭ������ ť ���� �˻��Ѵ�
{
     
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) // rear�� ���� 1��ŭ�� �����Ѵ� rear=front�� �Ǹ� ��ȭ���¶��
    {
		printf(" Circular Queue is full!"); // ����ť�� ���� ���ִٴ� ������ ����Ѵ�
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item) // queue�� item �Ҵ��Ѵ�
{
	if(isFull(cQ)) return; // ť�� ��ȭ ������ �ߴ��Ѵ�
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
        // rear�� (rear+1)%MAX_QUEUE_SIZE ������ �� �� �� ����� �Ҵ��Ѵ�
		cQ->queue[cQ->rear] = item; 
        // cQ[rear] �� item�� �����Ѵ�
	}
}

void deQueue(QueueType *cQ, element *item) 
// cQ�� ����Ű�� ������ queue[front] �� ������
{
	if(isEmpty(cQ)) exit(1); // ������ ť ���� �˻��Ѵ�
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; 
        // ������ �����ڸ� �̿��� front ������ �̵��Ѵ� front = front + 1
		cQ->queue[cQ->front]; // item�� ����Ű�� ���� front�� �Ҵ��Ѵ�
		return;
	}
}

void printQ(QueueType *cQ) // queue���� ����ִ� ���� ����Ѵ�
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
     // MAX_QUEUE_SIZE ���� cQ->first�� �Ҵ��Ѵ�
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
    // MAX_QUEUE_SIZE ���� last�� �Ҵ��Ѵ�

	printf("Circular Queue : ["); // queue���� ����ִ� �ε����� ����Ѵ�

	i = first; // i�� first�� ���� �Ҵ��Ѵ�
	while(i != last){ // i ���� last �� �ƴ� ��� ����Ѵ�
		printf("%3c", cQ->queue[i]); // queue�� ��Ҹ� ����Ѵ�
		i = (i+1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

void debugQ(QueueType *cQ) // ť ���� ���� ����Ѵ�
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // MAX_QUEUE_SIZE ��ŭ �ݺ��Ѵ�
	{
		if(i == cQ->front) // i�� cQ�� front�� ��ġ�Ѵٸ�
        {
			printf("  [%d] = front\n", i); // i�� ����Ѵ�
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //queue�� ��ҵ��� ����Ѵ�
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // cQ�� front�� rear�� ����Ѵ�
}