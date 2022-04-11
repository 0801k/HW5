#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum				
{
	lparen = 0, /* ( ���� ��ȣ            
	���� �ۿ����� ���� ��ȣ�� �켱������ ���� ������, ���� �ȿ����� ���� ��ȣ�� �켱������ ���ٰ� ����Ѵ�.*/
	rparen = 9, /* ) ������ ��ȣ*/
	times = 7,	/* * ���� */
	divide = 6, /* / ������ */
	plus = 5,	/* + ���� */
	minus = 4,	/* - ���� */
	operand = 1 /* �ǿ����� */  
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];	  /* ���� ǥ�⸦ ������ �迭 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* ���� ǥ�⸦ ���� ǥ��� ��ȯ�� ���� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	  /* ����ǥ����� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		  /* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1; /* postfixStack�� top,  ������ ������� �� -1 */
int evalStackTop = -1;	  /* evalStack�� top, ������ ������� �� -1 */

int evalResult = 0; /* ��� ����� ������ ���� */

void postfixpush(char x); 
char postfixPop(); 
void evalPush(int x); 
int evalPop();  
void getInfix(); 
precedence getToken(char symbol); 
precedence getPriority(char x);	
void charCat(char *c); 
void toPostfix(); 
void debug(); 
void reset();							
/* infixExp, postfixExp, postfixStack�� ����, postfixStackTop�� evalStackTop�� -1�� �ʱ�ȭ�Ѵ�.
 ��, evalResult�� 0���� �ʱ�ȭ�Ѵ�. */
void evaluation(); 

int main()
{
	char command; // char�� commandn �� �����Ѵ�

	printf("[----- [�����] [2020039102] -----]\n");

	do
	{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);	//��ɾ �Է¹޴´�

		switch (command)
		{
		case 'i': // i �Ǵ� I�� �Է� ���� ���
		case 'I':		
			getInfix(); // ������ �Է� �޴´�
			break;
		case 'p': // p �Ǵ� P�� �Է� ���� ���
		case 'P':
			toPostfix(); // ���� ǥ�� -> ����ǥ��
			break;
		case 'e': // e �Ǵ� E�� �Է� ���� ���
		case 'E':
			evaluation(); // ����ǥ��� �ٲ� ������ ����Ѵ�
			break;
		case 'd': // d �Ǵ� D�� �Է� ���� ���
		case 'D':
			debug(); 
			break;
		case 'r': // r �Ǵ� R�� �Է� ���� ���
		case 'R':
			reset();
			
			break;
		case 'q': // q �Ǵ� Q�� �Է� ���� ���
		case 'Q':
			break; 
		default: // �̿��� ��ɾ �Է��ϸ�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // ����� ���
			break;
		}

	} while (command != 'q' && command != 'Q'); // q�� Q�� �Է¹��� ���� ���� �ݺ��Ѵ�

	return 1;
}

void postfixPush(char x) // postfixStack�� push 
{
	postfixStack[++postfixStackTop] = x; // postfixStack[postfixStackTop]�� x�� �ִ´�
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1) // postfixStackTop�� -1 �� ����ִ� ����
		return '\0'; // NULL ��ȯ
	else
	{
		x = postfixStack[postfixStackTop--];  // postfixStackTop�� 1 ���ҽ�Ų��
	}
	return x;	// x ��ȯ
}

void evalPush(int x) // evalStack�� push
{
	evalStack[++evalStackTop] = x; // evalStack[evalStackTop]�� x�� �ִ´�
}

int evalPop()
{
	if (evalStackTop == -1) // evalStackTop�� -1 �� ����ִ� ����
		return -1;		// -1 ��ȯ
	else
		return evalStack[evalStackTop--];  // evalStackTop�� 1 ���ҽ�Ų��
}

void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp); // ������ infixExp�� �����Ѵ�
}

precedence getToken(char symbol) // �켱������ precedence���� ���Ѵ�
{
	switch (symbol) 
	{
	case '(':		
		return lparen; // lparen ��ȯ - 0 
	case ')':				
		return rparen; // rparen ��ȯ - 9 
	case '+':			
		return plus; // plus ��ȯ - 5 
	case '-':				
		return minus; // minus ��ȯ - 4 
	case '/':				
		return divide; // divide ��ȯ - 6 
	case '*':				
		return times; // times ��ȯ - 7 
	default:				
		return operand;	// operand ��ȯ - 1 
	}
}

precedence getPriority(char x) // x�� �켱����
{
	return getToken(x);	// �켱���� ��ȯ
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char *c) // c�� ���� �ϳ��� postfixExp�� �����Ѵ�.
{
	if (postfixExp == '\0')	// postfixExp�� NULL �� �ִٸ�
		strncpy(postfixExp, c, 1);	// c�� ���� �ϳ��� postfixExp�� �����Ѵ�
	else 
		strncat(postfixExp, c, 1);	// c�� ���� �ϳ��� postfixExp�� �����Ѵ�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix() // ���� ǥ�� -> ���� ǥ��
{ 
	char *exp = infixExp; 
	char x; 

	
	while (*exp != '\0') // exp�� ����Ű�� infixExp�� NULL ����Ű�� ���� �� �ݺ��Ѵ�
	{
		if (getPriority(*exp) == operand) // �켱������ �ǿ����ڿ� �ش��ϸ�
		{
			x = *exp; // x�� exp�� ����Ű�� ���� �����Ѵ�
			charCat(&x); // postfixExp�� x�� �����Ѵ�
		}
		else if (getPriority(*exp) == lparen) // �켱������ ���� ��ȣ���
		{
			postfixPush(*exp); 
		}
		else if (getPriority(*exp) == rparen) // �켱������ ������ ��ȣ���
		{
			while ((x = postfixPop()) != '(') // x�� "(" �ƴϸ� �ݺ�
			{
				charCat(&x); // postfixExp�� x�� �����Ѵ�.
			}
		}
		else 
		{
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
			{
				x = postfixPop(); // pop�� ���� �Ҵ�
				charCat(&x); // postfixExp�� x�� �����Ѵ�.
			}
			postfixPush(*exp); // exp�� ����Ű�� �� push
		}
		exp++; 
	}

	while (postfixStackTop != -1) // postfixStack�� ���� ������� ���� �ݺ�
	{
		x = postfixPop(); // pop�� ���� x�� �Ҵ��Ѵ�.
		charCat(&x); //  postfixExp���� x�� �����Ѵ�.
	}
}
void debug() // ����ǥ��
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); // infixExp ���
	printf("postExp =  %s\n", postfixExp); // postfixExp ���
	printf("eval result = %d\n", evalResult); // evalResult ���

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++) // MAX_STACK_SIZE�� �ݺ�
		printf("%c  ", postfixStack[i]); // postfixStack�� ��Ҹ� 0������ MAX_STACK_SIZE-1 ���� ����Ѵ�

	printf("\n");
}

void reset()
{
	infixExp[0] = '\0'; // infixExp�� NULL
	postfixExp[0] = '\0'; // postfixExp�� NULL

	for (int i = 0; i < MAX_STACK_SIZE; i++) // MAX_STACK_SIZE �� �ݺ�
		postfixStack[i] = '\0'; // postfixStack�� 0������ MAX_STACK_SIZE-1 ���� NULL

	postfixStackTop = -1; // postfixStackTop�� -1�� 
	evalStackTop = -1; // evalStackTop�� -1�� 
	evalResult = 0; // evalResult�� 0���� 
}

void evaluation() // ������ ����Ѵ�
{
	int opr1, opr2, i; // �ݺ����� ���� i�� �����Ѵ�.

	int length = strlen(postfixExp); // length�� postfixExp�� ���̸� �Ҵ�
	char symbol; // symbol ����
	evalStackTop = -1;

	for (i = 0; i < length; i++) // length �� �ݺ��Ѵ�
	{
		symbol = postfixExp[i];	// postfixExp�� i��° ��Ҹ� symbol��
		if (getToken(symbol) == operand) // symbol�� �켱������ operand�� ���ٸ�
		{
			evalPush(symbol - '0'); 	
			// 0 �� �ƽ�Ű �ڵ� ����ŭ ���ְ�, �� ���� evalStack�� push(�ִ´�)
		}
		else	
		{
			opr2 = evalPop(); //evalStack���� pop�� �� opr2 �Ҵ�
			opr1 = evalPop(); //evalStack���� pop�� �� opr1 �Ҵ�
			switch (getToken(symbol))
			{
			case plus: // plus�� ���
				evalPush(opr1 + opr2);	// opr1+opr2�� ���, ����� evalStack�� push 
				break; 
			case minus:	// minus�� ���
				evalPush(opr1 - opr2);	// opr1-opr2�� ���, ����� evalStack�� push
				break;					
			case times: // times�� ���
				evalPush(opr1 * opr2);	// opr1*opr2�� ���, ����� evalStack�� push
				break;					
			case divide: // divide�� ���
				evalPush(opr1 / opr2);	// opr1/opr2�� ���, ����� evalStack�� push
				break;					
			default: // ��ġ ���� �ʴ� �� ������
				break;
			}
		}
	}
	evalResult = evalPop(); 
	// ���������� ���� ���� evalResult�� �Ҵ��Ѵ�
}