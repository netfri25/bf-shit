#include <stdio.h>
#include <stdlib.h>
int main() {char* p=(char*)malloc(30000);*p=getchar();p++;p++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;while(*p){(*p)--;p--;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;p++;}p--;while(*p){(*p)--;p--;(*p)--;p++;}*p=getchar();*p=getchar();p++;p++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;while(*p){(*p)--;p--;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;p++;}p--;while(*p){(*p)--;p--;(*p)--;p++;}p--;while(*p){(*p)--;p--;(*p)++;p++;}p--;p++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;while(*p){(*p)--;p--;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;(*p)++;p++;}p--;putchar(*p);putchar(10);}