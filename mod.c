#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define NAME 'n'
#define MATH '1'
#define STACK '1'
#define VARIABLE '1'

int getop(char[]);
void push(double);
double pop(void);
void top(void);

size_t sp=0;
double val[MAXVAL];

#define BUFSIZE 100
char buf[BUFSIZE];
size_t bufp=0;

void clearsp(void){
  sp=0;
}

int getch_(void){
  return (bufp>0) ? buf[--bufp] : getchar();
}

void ungetch_(int c){
  if(bufp>=BUFSIZE)
    {fprintf(stderr, "ungetch: too many characters\n");
     return;}
  else
  buf[bufp++]=c;
}

int getop(char* s){
  int i,c;
  while((s[0]= c=getch_())==' '||c=='\t')
  s[1]='\0';

  if(!isdigit(c)&&c!='.'){return c;}
  i=0;
  if(isdigit(c)){ while (isdigit(s[++i]=c=getch_())){} }
  if(c=='.') {while(isdigit(s[++i]=c=getch_())){} }
  if (isalpha(c)){  i=0;  while (isalpha(s[i++] = c = getch_())){ }s[i]='\0';  return MATH;  }
  if (c=='='||c=='?'){  i=0;while(isalpha(s[++i]=c = getch_())){}s[i]='\0';return VARIABLE;}
  if(isalpha(s[++i]=c = getch_())){s[i]='\0';return STACK;  }
  s[i]='\0';
  if(c!=EOF){ungetch_(c);} return NUMBER;
}

void math(char* s){ //sin cos and pow options;
  double op1, op2, result =0;
  if(strcmp(s,"pow")==0)
   {
     op2=pop();
     op1=pop();
     printf("op1 = %f, op2 =%f\n",op1, op2);
     result=pow(op1,op2);
   }  else if (strcmp(s, "sin")==0) {result=sin(pop());
   }  else if (strcmp(s, "cos")==0){result = cos(pop());
   }  else if (strcmp(s, "sqrt")==0){result = sqrt(pop());
   }  else if (strcmp(s, "exp")==0){result = exp(pop());
   }
    push(result);
    printf("%.2f\n",result);
}

double pop(void){
  if(sp==0){fprintf(stderr,"stack underflow\n");
    return 0.0;
    }
  return val[--sp];
  }


void push(double f){
  if(sp==MAXVAL){fprintf(stderr,"stack overflow--can't push %g\n",f);
  return ;}
  val[sp++]=f;
}

void stack(char* s){
  double op1, op2;
  ++s;
  if(strcmp(s, "peek") == 0){

  }
  else if(strcmp(s, "swap")==0){
    op1=pop();
    op2=pop();
    push(op1);
    push(op2);
  }
  else if (strcmp(s, "clear")==0){
    clearsp();
  }
  else {
    printf("Uknown stack operation\n");

  }
}

void top(void){
  if(sp>0)
    printf("%.8g\n",  val[sp-1]);
  else{
    printf("error: stack emptyT\n");
  ;
  }
}

/*void variable(char* s){
  if(*s == '='){
    variables[*(s+1)-'A']=pop();
  }
  else if (*s == '?'){
    push(variables[*(s+1)-'A']);
  }
}*/

int main(int agrc,const char* argv[]){
  int type;
  double op1, op2, v;
  char s[MAXOP];
  char variable[26];

  while((type=getop(s))!=EOF){
    switch(type){
      case NUMBER:  push(atof(s));             break;
      case MATH:    math(s);                   break;
  //    case STACK:   stack(s);                  break;
   //case VARIABLE:variable(s);               break;

      case '+':     push(pop()+pop());           break;
      case '-':     op2=pop(); push(pop()-op2);  break;
      case '*':     push(pop()*pop());           break;
      case '%':     op2=pop(); op1=pop();
        if(op2!=0.0)
          push(op1-op2* (int) (op1/op2));
        else
          printf("zero division error\n");
        break;
      case '?': top();                        break;
      case '/':
      op2=pop();
        if (op2!=0.0)
        {
          push(pop()/op2);
        }
        break;
      case 'd': //duplicate getop
        op2= pop();
        push(op2);
        push(op2);
        break;
      case '~': ///swap top 2
        op1=pop();
        op2=pop();
        push(op1);
        push(op2);
        break;
      case 'z'://clear stack
        clearsp();
        break;
     case 's':
        push(sin(pop()));
        break;
      case 'c':
        push(cos(pop()));
        break;
      case 't':
        push(tan(pop()));
        break;
      case 'e':
        push(exp(pop()));
        break;
      case '^':
        op2=pop();
        push(pow(pop(), op2));
        break;
      case '\n':
        v= pop();
        printf("\t%.8g\n", v);
        break;
      default:
        if (type>='A'&& type<='Z')
          push(variable[type-'A']);
          else if(type=='v')
            push(v);
        printf("error: unkown command %s\n",s);
        break;
      }

    }
  return 0;
}
