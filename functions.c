#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "functions.h"


void decimalEqual(number *a, number *b) {


    if(a->dec>b->dec)
    {
        for(int i=0;i<(a->dec-b->dec);i++)
            {
                addDigit(b,'0');
                b->dec++;
            }
            return;
    }
    else if(b->dec>a->dec)
    {
        for(int j=0;j<(b->dec-a->dec);j++)
            {
                addDigit(a,'0');
                a->dec++;
            }
            return;
    }
    else
        return;
}


void lengthofnumberEqual(number *a, number *b) {
	node*p=a->head;
    node*q=b->head;
    int len1=0,len2=0;
    while(p)
    {
        len1++;
        p=p->next;
    }
    while(q)
    {
        len2++;
        q=q->next;
    }
    if(len1>len2)
        while(len1>len2)
            {
                pushdigit(b,0);
                len2++;
            }
    else if(len2>len1)
    {

        while(len2>len1)
            {
                pushdigit(a,0);
                len1++;
            }
    }


    return;
}


int zeroNumber(number a) {
	int i, count = 0;
	node *p = a.head;
	for(i = 0; i < lengthofnumber(a); i++) {
		if(p->num != 0)
			count = 1;
		 p = p->next;
	}
	return count;
}


number *add(number *a, number *b) {
	 number *result;
    result=(number*)malloc(sizeof(number));
    initNumber(result);
    decimalEqual(a,b);
    lengthofnumberEqual(a,b);
    node*last1=a->tail;
    node*last2=b->tail;
    result->dec=a->dec;

    int carry=0,sum=0;
    while(last1&&last2)
    {

        sum=last1->num+last2->num+carry;
        carry=sum/10;
        sum=sum%10;
        pushdigit(result,sum);
        last2=last2->prev;
        last1=last1->prev;
    }
    if(carry)
        pushdigit(result,carry);


    return result;

}


int compareEqual(number a, number b) {
	lengthofnumberEqual(&a, &b);
	decimalEqual(&a, &b);
	node *p, *q;
	int len;
	int i;
	len = lengthofnumber(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++) {
		if(p->num > q->num)
			return 1;
		else if(p->num < q->num)
			return -1;
		p = p->next;
		q = q->next;
	}
	return 0;
}

number *sub(number *a, number *b) {
	number *result;
	result = (number *)malloc(sizeof(number));
	initNumber(result);
	decimalEqual(a, b);
	lengthofnumberEqual(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			result = add(a, b);
			result->sign = MINUS;
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			result = add(a, b);
			result->sign = PLUS;
		}
	}
	else if(a->sign == b->sign) {
		if(a->sign == MINUS) {
			a->sign = b->sign = PLUS;
			result = sub(b, a);
		}
		else if(a->sign == PLUS) {
			int n1, n2, diff, borrow = 0, i, len;
			node *t1 = a->tail;
			node *t2 = b->tail;
			len = lengthofnumber(*b);
			if(compareEqual(*a, *b) == 1) {
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n1 = n1 - borrow;
					if(n1 >= n2) {
						diff = n1 - n2;
						borrow = 0;
						pushdigit(result, diff);
					}
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						pushdigit(result, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(compareEqual(*a, *b) == -1) {
				result->sign = MINUS;
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						pushdigit(result, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						pushdigit(result, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else {
				if(compareEqual(*a, *b) == 0) {
					pushdigit(result, 0);
				}
			}
		}
	}
	result->dec = a->dec;
	return result;
}

number *multiply(number *a, number *b) {
	number *result = (number *)malloc(sizeof(number));
	initNumber(result);

	if((zeroNumber(*a) == 0) || (zeroNumber(*b) == 0)) {
		addDigit(result, '0');
		return result;
	}
	int lengthofnumberdiff;
	if(a->sign == b->sign) {
		result->sign = PLUS;
		a->sign = b->sign = PLUS;
	}
	else {
		result->sign = MINUS;
		a->sign = b->sign = PLUS;
	}
	lengthofnumberdiff = lengthofnumber(*a) - lengthofnumber(*b);
	if(lengthofnumberdiff < 0) {
		result = multiply(b, a);
		return result;
	}
	else {
		node *t1, *t2;
		int len_a = lengthofnumber(*a);
		int len_b = lengthofnumber(*b);
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_a];
		for(i = 0; i < 2 *len_a; i++)
			tempresult[i] = 0;
		int k = 2 * len_a - 1;
		t2 = b->tail;
		for(i = 0; i < len_b; i++) {
			t1 = a->tail;
			int carry1 = 0, carry2 = 0;
			for(j = k - i; j > len_a - 2; j--) {
				if(t1 != NULL && t2 != NULL) {
					n1 = t1->num * t2->num + carry1;
					t1 = t1->prev;
					carry1 = n1 / 10;
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + carry2;
					carry2 = n2 / 10;
					n2 = n2 % 10;
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}
			tempresult[j] = carry1 + carry2 + tempresult[j];
			len_a--;
			t2 = t2->prev;
		}
		for(i= k; i >= len_a - 1 && i >= 0; i--) {
			pushdigit(result, tempresult[i]);
		}
		result->dec = a->dec + b->dec;
		return result;
	}
}

number *division(number *m, number *n){
	if(zeroNumber(*n) == 0) {
		printf("Dividing by Zero is not defined.\n");
		return NULL;
	}

	int k = m->dec > n->dec ? m->dec : n->dec;
	int i = 0;

	while(i < k) {
		if(m->dec > 0)
			m->dec--;
		else
			addDigit(m, '0');
		if(n->dec > 0)
			n->dec--;
		else
			addDigit(n, '0');
		i++;
	}
	i = 9;
	number *c, *d, *result, *q, *product;
	c = (number *)malloc(sizeof(number));
	d = (number *)malloc(sizeof(number));
	result = (number *)malloc(sizeof(number));
	product = (number *)malloc(sizeof(number));
	q = (number *)malloc(sizeof(number));

	initNumber(result);
	initNumber(c);
	initNumber(q);
	initNumber(d);
	if(m->sign == n->sign) {
		q->sign = PLUS;
		m->sign = n->sign = PLUS;
	}
	else {
		q->sign = MINUS;
		m->sign = n->sign = PLUS;
	}
	node *p = m->head;
	char ch = p->num + '0';
	addDigit(d, ch);
	while(q->dec < SCALE){
		while(i >= 0){
			pushdigit(c, i);
			product = multiply(n, c);
			result = sub(d, product);
			if(result->sign != MINUS) {
				addDigit(q, i + '0');
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			else{
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--;
			}
		}
		d = result;
		if(p->next != NULL) {
			p = p->next;
			ch = p->num + '0';
			addDigit(d, ch);
		}
		else{
			q->dec++;
			addDigit(d, '0');
		}
		i = 9;
		node *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	q->dec--;
	return q;
}


number *modulus(number *a, number *b) {
	if(zeroNumber(*b) == 0) {
		printf("ERROR : Modulo by Zero is not allowed.\n");
		return NULL;
	}
	int tempsign;
	if(a->sign == MINUS) {
		tempsign = MINUS;
		a->sign = b->sign = PLUS;
	}
	else {
		tempsign = PLUS;
		a->sign = b->sign = PLUS;
	}
	decimalEqual(a, b);
	int a_dec = a->dec;
	number *result = (number *)malloc(sizeof(number));
	number *temp = (number *)malloc(sizeof(number));
	initNumber(result);
	initNumber(temp);
	temp = division(a, b);
	if(temp->dec != 0) {
		int pos = lengthofnumber(*temp) - 1;
		while(temp->dec != 0) {
			removedigit(temp, pos);
			temp->dec--;
			pos--;
		}
	}
	temp = multiply(temp, b);
	result = sub(a, temp);
	result->sign = tempsign;
	result->dec = a_dec;
	return result;
}
