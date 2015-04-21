c===============================================================================
c===================================================== Programa DerivarPolinomio
c===============================================================================
c
c     --------------------------------------------------------------------------
c                                                      2           n
c     Dado el polinomio           P (x) = a + a x + a x + ... + a x
c                                  n       0   1     2           n
c
c     y el punto de calculo       z
c
c                                                              2               n
c     realiza el cambio de base   P (x) = b + b (x-z) + b (x-z) + ... + b (x-z)
c                                  n       0   1         2               n
c
c                                          (i      |
c                                         d  P (x) |
c                                             n    |
c     y calcula las derivadas     c(i) =  -------- |
c                                             (i   |
c                                          d x     |x = z
c
c     --------------------------------------------------------------------------

      parameter (MX=100)                          !MX=grado maximo del polinomio
      implicit real*8 (a-h,o-z)
      dimension a(0:MX),b(0:MX),c(0:MX)

c.....LECTURA DE DATOS
    1 write(6,100) MX+1
  100 format(/' Introduzca GRADO del polinomio [n < ',i6,'] = ',$)
      read(5,*) n
      if (n.lt.0.or.n.gt.MX) goto 1
      write(6,200)
  200 format(/' Introduzca PUNTO de calculo             [z] = ',$)
      read(5,*) z
      call LeerCoeficientes(n,a)

c.....CAMBIO DE BASE POR DIVISION SINTETICA
      call DivisionSintetica(n,z,a,b)

c.....CALCULO DE DERIVADAS
      call CalcularDerivadas(n,b,c)

c.....ESCRITURA DE RESULTADOS
      call EscribirResultados(n,z,a,b,c)

      read(5,'()')
      call exit(0)

      end


c_______________________________________________________________LeerCoeficientes
      Subroutine LeerCoeficientes(n,a)
      implicit real*8 (a-h,o-z)
      dimension a(0:n)

      write(6,300)
  300 format(/' Introduzca COEFICIENTES del polinomio:'/)
      do i=0,n
        write(6,302) i
  302   format(16x,'a(',i5,') = ',$)
        read(5,*) a(i)
      enddo

      return
      end


c______________________________________________________________DivisionSintetica
      Subroutine DivisionSintetica(n,z,a,b)
      implicit real*8 (a-h,o-z)
      dimension a(0:n),b(0:n)

      do i=0,n
       b(i)=a(i)
      enddo

      do k=n,1,-1
        do i=n-1,n-k,-1
          b(i)=b(i)+b(i+1)*z
        enddo
      enddo

      return
      end


c______________________________________________________________CalcularDerivadas
      Subroutine CalcularDerivadas(n,b,c)
      implicit real*8 (a-h,o-z)
      dimension b(0:n),c(0:n)

      do i=0,n
        c(i)=b(i)
      enddo

      fact=1.d+00
      do i=2,n
        fact=fact*dble(i)
        c(i)=c(i)*fact
      enddo

      return
      end


c_____________________________________________________________EscribirResultados
      Subroutine EscribirResultados(n,z,a,b,c)
      implicit real*8 (a-h,o-z)
      dimension a(0:n),b(0:n),c(0:n)

      write(6,1000)
 1000 format(///' RESULTADOS'/,' ==========',/)

      write(6,1100) n
 1100 format(/' Grado del polinomio [n] = ',i5)
      write(6,1200) z
 1200 format(/' Punto de calculo    [z] = ',d20.9)

      write(6,1300)
 1300 format(/' Coeficientes en la base {1,x,...,x^n}:'/)
      do i=0,n
        write(6,1302) i,a(i)
 1302   format(16x,'a(',i5,') = ',d20.9)
      enddo

      write(6,1400)
 1400 format(/' Coeficientes en la base {1,(x-z),...(x-z)^n}:'/)
      do i=0,n
        write(6,1402) i,b(i)
 1402   format(16x,'b(',i5,') = ',d20.9)
      enddo

      write(6,1500)
 1500 format(/' Funcion y derivadas en el punto x = z:'/)
      do i=0,n
        write(6,1502) i,c(i)
 1502   format(16x,'c(',i5,') = ',d20.9)
      enddo

      write(6,1600)
 1600 format(/)

      return
      end

