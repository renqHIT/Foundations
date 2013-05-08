#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

void Change_Address( int **p, int **pt)
{
	//int *pp;
	//pp = *p;
	//*p = *pt;
	//*pt= pp;
	
	int ** pp;
	pp = p;
	p = pt;
	pt = pp;
}

int main(void)
{
	int a =3, b = 4, *p, *p1;
	p = &a; p1 = &b;    
	printf("Values Before interchange %d %d\n", *p, *p1);
	Change_Address(&p, &p1);
	printf("Values after interchange %d %d", *p, *p1);    
	getch();     
	return 0;
}
