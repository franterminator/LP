#include<stdio.h>
#include<stdlib.h>

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

int main(int argc, char *argv[])
{
    // Prototype
    int impresora (int,int);
    
    int input1, input2;
    int sel;
    
    printf("\nIntroduzca el primer valor a comparar:\n");
    fflush(stdin);
    scanf("%d",&input1);
    printf("               segundo valor a comparar:\n");
    fflush(stdin);
    scanf("%d",&input2);

    // AND
    printf("\n%d && %d? %d -> ",input1,input2,input1 && input2);
    if (input1 && input2) printf("T;\n");
    else printf("F;\n");

    // OR
    printf("\n%d || %d? %d ->",input1,input2,input1 || input2);
    if (input1 || input2) printf("T;\n");
    else printf("F;\n");

    // Disyuntive OR
    printf("\n%d ^ %d? %d -> ",input1,input2,input1^input2);
    if (input1 ^ input2) printf("T;\n");
    else printf("F;\n");

    // NOT
    printf("\n~%d? %d -> ",input1,~input1);
    if (~input1) printf("T; ");
    else printf("F; ");
    printf(" ~%d? %d ->",input2,~input2);
    if (~input2) printf("T;\n");
    else printf("F;\n");

    // Desea generar impresion de pantalla
    printf("Desea guardar una impresion de pantalla?\n 1) Si\n 2) No\n");
    fflush(stdin);
    scanf("%d",&sel);
    if (sel == 1) impresora(input1,input2);

    // Wait for the end of program
    fflush(stdin);
    getchar();
    return 0;
}

int impresora (int in1, int in2) {
    FILE *f = fopen("pantalla.txt","w");

    if (f == NULL) {printf("\nError al abrir el archivo");return 1;}

    //START
    fprintf(f,"\n---------------------------------------");

    fprintf(f,"\nIntroduzca el primer valor a comparar:\n%c",in1);
    fprintf(f,"\n               segundo valor a comparar:\n%c",in2);

     // AND
    fprintf(f,"\n%d && %d? %d ->",in1,in2,in1 && in2);
    if (in1 && in2) fprintf(f,"T;\n");
    else fprintf(f,"F;\n");

    // OR
    fprintf(f,"\n%d || %d? %d -> ",in1,in2,in1 || in2);
    if (in1 || in2) fprintf(f,"T;\n");
    else fprintf(f,"F;\n");

    // Disyuntive OR
    fprintf(f,"\n%d ^ %d? %d -> ",in1,in2,in1 ^ in2);
    if (in1 ^ in2) fprintf(f,"T;\n");
    else fprintf(f,"F;\n");

    // NOT
    fprintf(f,"\n~%d? %d -> ",in1,~in1);
    if (~in1) fprintf(f,"T; ");
    else fprintf(f,"F; ");
    fprintf(f," ~%d? %d ->",in2,~in2);
    if (~in2) fprintf(f,"T;\n");
    else fprintf(f,"F;\n");

    // END
    fprintf(f,"\n---------------------------------------");
    printf("\nSe ha imprimido correctamente.");

    return 0;
}
    
