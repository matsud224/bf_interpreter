#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

using namespace std;

struct inst{
	char inst;
	struct inst *ptr;
};

char tape[30000];
char *ptr = tape;

struct inst code[50000];
struct inst *pc;

int main(void)
{
	int index = 0;

    stack<int32_t> lbrackets;

	char c;
    while((c=getchar()) != EOF){
		switch(c){
		case '>':
		case '<':
		case '+':
		case '-':
		case ',':
		case '.':
			code[index].inst = c;
			index++;
			break;
		case '[':
			code[index].inst = c;
			lbrackets.push(index);
			index++;
			break;
		case ']':
			if(lbrackets.empty()){
				fprintf(stderr, "error: no matching rbracket!");
				return -1;
			}

			uint32_t lb_index = lbrackets.top();
			lbrackets.pop();
			code[lb_index].ptr=&code[index+1];
			code[index].inst = c;
			code[index].ptr = &code[lb_index+1];

			index++;
			break;
		}
    }

    code[index].inst = '\0';

    if(!lbrackets.empty()){
		fprintf(stderr, "error: no matching lbracket!");
		return -1;
	}

	pc=code;
	while(pc->inst!='\0'){
		switch(pc->inst){
		case '>':
			ptr++;
			pc++;
			break;
		case '<':
			ptr--;
			pc++;
			break;
		case '+':
			(*ptr)++;
			pc++;
			break;
		case '-':
			(*ptr)--;
			pc++;
			break;
		case ',':
			*ptr=getchar();
			pc++;
			break;
		case '.':
			putchar(*ptr);
			pc++;
			break;
		case '[':
			if(!(*ptr))
				pc=pc->ptr;
			else
				pc++;

			break;
		case ']':
			if(*ptr)
				pc=pc->ptr;
			else
				pc++;

			break;
		}
    }

    return 0;
}
