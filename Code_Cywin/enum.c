/*============================================
*
==============================================*/
/* Enum is the rally of all value in a property*/
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

/*============================================
*
==============================================*/
typedef enum 
{
	ERROR_INPUT		= 0U,
	OK,
}div_status;


typedef enum
{
	add = 0u,
	sub,
}mode;



/*============================================
*
==============================================*/
div_status div_s( int8_t a, int8_t b, mode c );

/*============================================
*
==============================================*/
int main( void)
{

	div_s( 1,2, add);
	
	div_s( 1,0, add);
	return 0;
}

/*============================================
*
==============================================*/
div_status div_s( int8_t a, int8_t b , mode c)
{
	if(b == 0)
	{
		return ERROR_INPUT;
	}
	else
		if(c == add)
			printf("\nadd result: %f\n",(float)a+b );
		else if( c == sub)
			printf("\nsub result: %f\n",(float)a-b );
		else
			return ERROR_INPUT;
}

