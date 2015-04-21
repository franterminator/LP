/*______________________________________________________________________________
  Funcion Alterar, de dificil comprension y cuyo objetivo se desconoce
*/
#include <stdio.h>
void Alterar(int n, double v[])
{
	int    i, j;
	double vc;

	
BucleExterno: for(i=0;i<=n-1;i++)
        {
       BucleInterno: for(j=n-1;j>i;j--)
          {
            if (v[i] >= v [j]){
              vc   = v[i];
              v[i] = v[j];
              v[j] = vc;
            }
          }
        }
}
