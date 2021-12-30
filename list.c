#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initNumber(number *a) {
	a->head = a->tail = NULL;
	a->dec = 0;
	a->sign = PLUS;
}
void addDigit(number *a, char ch)
{
	node *newnode = (node *)malloc(sizeof(node));
	if(newnode == NULL)
		return;
	newnode->num = ch - '0';
	newnode->next = NULL;
	if((a->head == NULL) && (a->tail == NULL)) {
		newnode->prev = NULL;
		a->head = newnode;
		a->tail = newnode;
		return;
	}
	newnode->prev = a->tail;
	a->tail->next = newnode;
	a->tail = newnode;
	return;
}
int lengthofnumber(number c) {
	node *p;
    p = c.head;
	int count = 0;
	while(p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}
void pushdigit(number *c, int no) {
	node *newnode = (node *)malloc(sizeof(node));
	if(!newnode)
		return;
	newnode->num = no;
	newnode->prev = NULL;
	if((c->head == NULL) && (c->tail == NULL)){
		newnode->next = NULL;
		c->head = c->tail = newnode;
		return;
	}
	newnode->next = c->head;
	c->head->prev = newnode;
	c->head = newnode;
	return;
}
void removedigit(number *a, int pos){
	int i;
	node *p, *newnode;

	if(pos < 0 || pos >= lengthofnumber(*a))
		return;

	p = a->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(a->head == NULL) {
		return;
	}
	if(lengthofnumber(*a) == 1) {
		a->head = a->tail = p = NULL;
		return;
	}
	if(pos == 0) {
		p->next->prev = NULL;
		a->head = p->next;
		free(p);
		return;
	}
	if(pos == lengthofnumber(*a) - 1) {
		newnode = p->next;
		p->next = NULL;
		a->tail = p;
		free(newnode);
		return;
	}

	newnode = p->next;
	p->next = p->next->next;
	newnode->next->prev = p;
	free(newnode);
	return;
}

void printNumber(number c) {
	node *p;
	int pos = 0;
	p = c.head;
	if(c.sign == MINUS) {
		printf("-");
		c.sign = PLUS;
	}
	while(p != NULL) {
		pos++;
		if(pos == (lengthofnumber(c) - c.dec + 1))
			printf(".");
		printf("%d", p->num);
		p = p->next;
	}
	printf("\n");
}
