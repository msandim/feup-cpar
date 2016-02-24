function OnMult(n_a, n_b)
	integer, intent(in) :: n_a
	integer, intent(in) :: n_b

	integer :: i, j, k
	real :: temp

	!Create arrays
	real, dimension(n_a*n_a) :: a
	real, dimension(n_b*n_b) :: b
	real, dimension(n_a*n_b) :: c
	
  	!Initialize array a
	do i=1,n_a*n_a
		a(i) = 1
	end do

	!Initialize array b
	do i=1,n_b*n_b
		b(i) = i/n_b+1
	end do

	!Matrix Multiplication
	do i=1,n_a
		do j=1,n_b
			temp = 0
			do k=1,n_a
				temp = temp + a((i-1)*n_a+k) * b((k-1)*n_b+k)
			end do
			c((i-1)*n_a+j) = temp
		end do
	end do
	
	!Print Result Matrix
	print *, "Result matrix: "
	do i=1,min(n_a*n_b, 10)
		print *, c(i)
	end do

 end function 

function OnMultLine(n_a, n_b)
	integer, intent(in) :: n_a
	integer, intent(in) :: n_b

	integer :: i, j, k

	!Create arrays
	real, dimension(n_a*n_a) :: a
	real, dimension(n_b*n_b) :: b
	real, dimension(n_a*n_b) :: c
	
  	!Initialize array a
	do i=1,n_a*n_a
		a(i) = 1
	end do

	!Initialize array b
	do i=1,n_b*n_b
		b(i) = i/n_b+1
	end do

	!Initialize array b
	do i=1,n_a*n_b
		c(i) = 0
	end do
					
	!Matrix Multiplication
	do i=1,n_a
		do k=1,n_b
			do j=1,n_b
				c((i-1)*n_a+j) = c((i-1)*n_a+j) + a((i-1)*n_a+k) * b((k-1)*n_b+j)
			end do
		end do
	end do
	
	!Print Result Matrix
	print *, "Result matrix: "
	do i=1,min(n_a*n_b, 10)
		print *, c(i)
	end do

 end function 


program ex1
	print *, OnMultLine(10,10)
end program ex1
