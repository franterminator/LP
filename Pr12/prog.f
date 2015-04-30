c_______________________________________________________________________________
c_______________________________________________________________________________

      implicit real*8 (a-h,o-z)

      allocatable v1(:), v2(:)

    1 write(6,100) ' Introduce el numero de componentes: '
  100   format(/a,$)
        read(5,*) n
      if (n.lt.1) goto 1

      allocate (v1(n), STAT=ist)
      if(ist.ne.0)
     +call FError(0,'fallo indeterminado con el vector 1',2)
      allocate (v2(n), STAT=ist)
      if(ist.ne.0)
     +call FError(0,'fallo indeterminado con el vector 1',2)
      
      
      write(6,'(/a/)') ' Introduzca vector v1():'
      call LeerVector(n,'v1',v1)

      write(6,'(/a/)') ' Introduzca vector v2():'
      call LeerVector(n,'v2',v2)

      pe = ProductoEscalar(n, v1, v2);

      write(6,200) pe
  200 format(/' Producto escalar de v1() * v2() = ',d25.16/)  

      read(5,*)
      call exit(0);

      end


c_____________________________________________________________________LeerVector
      Subroutine LeerVector(n,nombre,v)
      implicit real*8 (a-h,o-z)

      character*(*) nombre
      dimension v(n)

      do i=1,n
        write(6,100) nombre, i
  100   format('       ',a,' (',i6,') = ',$)
        read(5,*) v(i)
      enddo

      return
      end
c________________________________________________________________ProductoEscalar
      function ProductoEscalar(n,v1,v2)
      implicit real*8 (a-h,o-z)

      dimension v1(n), v2(n)
      pe = 0.0d+00

      do i=1,n
         pe = pe + v1(i)*v2(i)
      enddo

      ProductoEscalar = pe
      end
c_________________________________________________________________________FError
      Subroutine FError(logerr,error,ierr)
      character*(*) error

      write(logerr,100) error
  100 format(/,' prueba:: Error: ',a)

      write(logerr,'(/a,$)')
     .      ' Fin de Ejecucion. Oprima RETURN para salir.'
      read(5,'()')
      call exit(ierr)

      return
      end
