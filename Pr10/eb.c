#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define UNO 1.0e+00
int main(int argc, char *argv[])
{
    int n = 0;
    double e;
    if (argc == 1) {
	printf("%s: Error, write /? to know how to use the command.\n",*argv);
	exit(1);
    }
    else if (argc == 2) {
	if (strcmp(*(argv+1),"/?") == 0) {
	    printf("HowToUse: write /n i. Where i is the number of interations\n");
	    exit(0);
	}
	else 
	    n = atoi(argv[1]);
    }
    else if (argc == 3) {
	if (strcmp(*(argv+1),"/n") == 0)
	    n = atoi(argv[2]);
	else {
	    printf("%s: Error, write /? to know how to use the command.\n",*argv);
	    exit(1);
	}
    }
    if(n == 0){
	printf("%s: Error, n > 0.\n",*argv); 
	exit(2);
    }

    e = UNO;
    
    int i; //counter variable
    for(i = n; i > 0 ; i--)
	e = UNO + e/(double)i;
    
    printf(" n = %d;      -> e = %24.15le",n,e);
    
    fflush(stdin);
    getchar();
    return 0;
}
