#include<stdio.h>


void change_tham_tri( int x);
void change_tham_chieu( int *x);


int b = 0;

int main( void )
{
	int a = 0;
	int *p1;
	char *p2;

	printf("\n\n USE THAM TRI\n");
	change_tham_tri(a);
	change_tham_tri(b);
	printf("a value: %d\n", a);
	printf("b value: %d\n", b);



	printf("\n\n USE THAM CHIEU\n\n");
	change_tham_chieu(&a);
	change_tham_chieu(&b);
	printf("a value: %d\n", a);
	printf("b value: %d\n\n\n", b);
	


	printf("Size of pointer\n");
	printf("size of int pointer: %d\n", sizeof(p1));
	printf("size of char pointer: %d\n\n\n", sizeof(p2));


	return 0;
}


void change_tham_tri( int x)
{
	x = 123;
}

void change_tham_chieu( int *x)
{
	*x = 456;
}