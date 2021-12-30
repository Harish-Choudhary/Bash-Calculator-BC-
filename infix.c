#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"istack.h"
#include "functions.h"
#include <limits.h>

#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400

typedef struct token{
	int type;
	number *num;
	char op;
}token;
enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC };
token gettoken(char *expression, int *reset) {
	static int i = 0;
	number *a = (number *)malloc(sizeof(number));
	initNumber(a);
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;

	}
	while(1) {
		currchar = expression[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						addDigit(a, currchar);
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :

						nextstate = OP;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case DOT:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						addDigit(a, currchar);
						a->dec++;
						nextstate = DOT;
						currstate = nextstate;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :

						nextstate = OP;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						t.type = OPERATOR;
						t.op = expression[i - 1];
						nextstate = NUMBER;
						currstate = nextstate;

						return t;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
						nextstate = OP;
						t.type = OPERATOR;
						t.op = expression[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.op = expression[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.op = expression[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						t.type = OPERATOR;
						t.op = expression[i -1];
						currstate = nextstate;
						i++;
						return t;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expression[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':

						addDigit(a, currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :

						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;

					case '.':
						nextstate = DOT;
						i++;
						break;

					default:
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}

int precedance(char o) {
	switch(o) {
		case ')' :
			return 0;
			break;
		case '+' :
		case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
		case '(' :
			return 4;
			break;
		default :
			return 5;
			break;
	}
	return 5;
}
number *infix(char *exp) {
	token t;
	char curr_op, prev_op, ch;
	int cnt_ob = 0, cnt_cb = 0, reset  = 1, curr, prev;
	number *a, *b, *z;
	a = (number *)malloc(sizeof(number));
	b = (number *)malloc(sizeof(number));
	z = (number *)malloc(sizeof(number));
	initNumber(a);
	initNumber(b);
	initNumber(z);
	stack is;
	opstack cs;
	initnumstack(&is);
	initopstack(&cs);
	prev = ERR;
	while(1) {
		t = gettoken(exp, &reset);
		curr = t.type;
		if(curr == prev && prev == OPERAND) {

			return NULL;
		}
		if(t.type == OPERAND){
			pushnum(&is, t.num);
		}
		else if(t.type == OPERATOR){
			curr_op = t.op;
			if(curr_op == '(')
				cnt_ob++;
			if(curr_op == ')')
				cnt_cb++;
			if(cnt_cb > cnt_ob)

				return NULL;
			if(!isemptyopstack(&cs)) {
				prev_op = topop(&cs);

				while(precedance(prev_op) >= precedance(curr_op)) {
					prev_op = pop_op(&cs);
					if(!isemptynumstack(&is)) {
						a = popnum(&is);
					}
					else{
						pushop(&cs, prev_op);
						break;
					}
					if(!isemptynumstack(&is)) {
						b = popnum(&is);
					}
					else {
						pushop(&cs, prev_op);
						pushnum(&is, a);
						break;
					}
					switch (prev_op) {
						case '+' :

							z = add(a, b);
							pushnum(&is, z);
							break;
						case '-' :

							z = sub(b, a);
							pushnum(&is, z);
							break;
						case '*' :

							z = multiply(b, a);
							pushnum(&is, z);
							break;
						case '/' :

							z = division(b, a);
							pushnum(&is, z);
							break;
						case '%' :

							z = modulus(b, a);
							pushnum(&is, z);
							break;

						case '(' :
							pushop(&cs, prev_op);
							pushnum(&is, b);
							pushnum(&is, a);
							break;
						default :

							return NULL;
					}
					if (prev_op == '(')
						break;
					if(!isemptyopstack(&cs))
						prev_op = topop(&cs);
					else
						break;
				}
			}
			pushop(&cs, t.op);
			if(curr_op == ')') {
				ch = pop_op(&cs);
				cnt_cb--;
				ch = pop_op(&cs);
				cnt_ob--;
			}
		}
		else if(t.type == END) {
			if(cnt_ob == cnt_cb) {
				while(!isemptyopstack(&cs)) {
					if(!isemptynumstack(&is)) {
						a = popnum(&is);
					}
					else {
						printf("Error\n");
						return NULL;
					}
					if(!isemptynumstack(&is)) {
						b = popnum(&is);
					}
					else {
						printf("Error\n");
                        return NULL;
					}
					ch = pop_op(&cs);
					switch(ch) {
						case '+' :
							z = add(b, a);
							pushnum(&is, z);
							break;
						case '-' :
							z = sub(b, a);
							pushnum(&is, z);
							break;
						case '*' :
							z = multiply(b, a);
							pushnum(&is, z);
							break;
						case '/' :
							z = division(b, a);
							pushnum(&is, z);
							break;
						case '%' :
							z = modulus(b, a);
							pushnum(&is, z);
							break;
						default :

							return NULL;
							break;
					}
				}
			}
			else {
				printf("Error in expression\n");
				return NULL;
			}
			if(!isemptynumstack(&is)){
				z = popnum(&is);
				if(isemptynumstack(&is))
					return z;
				else {
                    printf("Error in expression\n");
                    return NULL;
                        	}
			}
			else {
				printf("Error in expression\n");
				return NULL;
			}
		}
		else if(t.type == ERR) {
			return NULL;
		}
		prev = curr;
	}
}


int getexpression(char *line, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			line[i++] = '\0';
			return i - 1;
		}
		else
			line[i++] = ch;
	}
	line[len - 1] = '\0';
	return len - 1;
}
