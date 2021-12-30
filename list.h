#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#define PLUS 1
#define MINUS -1

typedef struct node {
	int num;
	struct node *next, *prev;
}node;
typedef struct number {
	int sign, dec;
	node *head, *tail;
}number;

void initNumber(number *a);
void addDigit(number *a, char ch);
void printNumber(number a);
void destroyNumber(number *a);
void pushdigit(number *a, int no);
int lengthofnumber(number a);
void removedigit(number *a, int pos);





#endif
