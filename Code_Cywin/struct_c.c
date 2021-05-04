#include<stdio.h>
#include<stdlib.h>


/*===========================================================================
*								STRUCT
============================================================================*/
struct person
{
	char *first_name;
	char *last_name;

	int age;
} /* p1, *p2..*/;

#pragma pack(1)  // mormal the value is 4, 1, 2, 8
struct struct_laptringaz
{
	char a;
	int b;
	char c;
	int d;
};


/*===========================================================================
*								MAIN
============================================================================*/
int main( void )
{
	struct person per, per_02,*perptr;

	// bien thuong: .
	per.first_name 	= "Hoa";
	per.last_name 	= "Nguyen";
	per.age 		= 20;

	printf("\nInf person\nFirstName: %s\nLastName: %s\nAge: %d", 
			per.first_name, per.last_name, per.age );

	// bien con tro: ->
	perptr = &per;
	printf("\n\n\nInf person\nFirstName: %s\nLastName: %s\nAge: %d", 
			perptr->first_name, perptr->last_name, perptr->age );


	/* toan tu*/
	per_02 = per;

	int size = sizeof(per);
	printf("\n\nSize of per: %d\n", size);


	struct struct_laptringaz size_s;
	printf("\n\nSize of the laptrinhaz structure: %d\n", sizeof(size_s));
	return 0;
}
