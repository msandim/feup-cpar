
public class ex1 {
	
	private static void OnMult(int n_a, int n_b) 
	{
		double temp;
		int i, j, k;
		int c_lin = n_a;
		int c_col = n_b;
		
		//Create arrays
		double a[] = new double[n_a*n_a];
		double b[] = new double[n_b*n_b];
		double c[] = new double[c_lin*c_col];

		//Initialize array a
		for(i=0; i<n_a*n_a; i++)
			a[i] = (double)1.0;

		//Initialize array b
		for(i=0; i<n_b*n_b; i++)
			b[i] = (double)(i/n_b+1);

		//Matrix Multiplication
		for(i=0; i<n_a; i++)
			for( j=0; j<n_b; j++) {
				temp = 0;
				for( k=0; k<n_a; k++)
					temp += a[i*n_a+k] * b[k*n_b+j];
				c[i*n_a+j]=temp;
			}

		//Print Result Matrix
		System.out.println("Result matrix:");
		for(i=0; i< Math.min(c_lin*c_col, 10); i++)
			System.out.print(c[i] + " ");
		System.out.println();
	}
	
	private static void OnMultLine(int n_a, int n_b) 
	{
		int i, j, k;
		int c_lin = n_a;
		int c_col = n_b;
		
		//Create arrays
		double a[] = new double[n_a*n_a];
		double b[] = new double[n_b*n_b];
		double c[] = new double[c_lin*c_col];

		//Initialize array a
		for(i=0; i<n_a*n_a; i++)
			a[i] = (double)1.0;

		//Initialize array b
		for(i=0; i<n_b*n_b; i++)
			b[i] = (double)(i/n_b+1);
		
		//Initialize array c
		for(i=0; i<c_lin*c_col; i++)
			c[i] = (double)0.0;

		//Matrix multiplication
		for(i=0; i<n_a; i++)
			for( k=0; k<n_b; k++)
				for( j=0; j<n_b; j++)
					c[i*n_a+j] += a[i*n_a+k] * b[k*n_b+j];

		//Print Result Matrix
		System.out.println("Result matrix:");
		for(i=0; i< Math.min(c_lin*c_col, 10); i++)
			System.out.print(c[i] + " ");
		System.out.println();
	}
	
	public static void main(String[] args) {
		long start, end, t1, t2;
		
		start = System.currentTimeMillis();
		OnMult(1000, 1000);
		end = System.currentTimeMillis();
		t1 = end - start;
		
		start = System.currentTimeMillis();
		OnMultLine(1000, 1000);
		end = System.currentTimeMillis();
		t2 = end - start;
		
		System.out.println("OnMult time:" + t1);
		System.out.println("OnMultLine time:" + t2);
	}
}
