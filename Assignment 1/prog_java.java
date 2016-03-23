
public class prog_java {
	
	private static void OnMult(int n_a, int debug) 
	{
		long start, end;
		double t1;

		double temp;
		int i, j, k;
		int c_lin = n_a;
		int c_col = n_a;
		
		// Create arrays:
		double a[] = new double[n_a*n_a];
		double b[] = new double[n_a*n_a];
		double c[] = new double[c_lin*c_col];

		// Initialize array a:
		for(i=0; i<n_a*n_a; i++)
			a[i] = (double)1.0;

		// Initialize array b:
		for(i=0; i<n_a*n_a; i++)
			b[i] = (double)(i/n_a+1);

		start = System.nanoTime();

		// Matrix Multiplication:
		for(i=0; i<n_a; i++)
			for( j=0; j<n_a; j++) {
				temp = 0;
				for( k=0; k<n_a; k++)
					temp += a[i*n_a+k] * b[k*n_a+j];
				c[i*n_a+j]=temp;
			}

		// Measure the time passed:
		end = System.nanoTime();
		t1 = (end - start) / 1000000000.0;

		// Output csv format into stdout:
		System.out.println("Java,Mult,0," + n_a + "," + t1 + ",0,0");

		// Print Result Matrix (DEBUG):
		if (debug == 1)
		{
			System.out.println("Result matrix:");
			for(i=0; i< Math.min(c_lin*c_col, 10); i++)
				System.out.print(c[i] + " ");
			System.out.println();
		}
	}
	
	private static void OnMultLine(int n_a, int debug) 
	{
		long start, end;
		double t1;

		int i, j, k;
		int c_lin = n_a;
		int c_col = n_a;
		
		// Create arrays:
		double a[] = new double[n_a*n_a];
		double b[] = new double[n_a*n_a];
		double c[] = new double[c_lin*c_col];

		// Initialize array a:
		for(i=0; i<n_a*n_a; i++)
			a[i] = (double)1.0;

		// Initialize array b:
		for(i=0; i<n_a*n_a; i++)
			b[i] = (double)(i/n_a+1);
		
		// Initialize array c:
		for(i=0; i<c_lin*c_col; i++)
			c[i] = (double)0.0;

		start = System.nanoTime();

		// Matrix multiplication:
		for(i=0; i<n_a; i++)
			for( k=0; k<n_a; k++)
				for( j=0; j<n_a; j++)
					c[i*n_a+j] += a[i*n_a+k] * b[k*n_a+j];

		// Measure the time passed:
		end = System.nanoTime();
		t1 = (end - start) / 1000000000.0;

		// Output csv format into stdout:
		System.out.println("Java,LineMult,0," + n_a + "," + t1 + ",0,0");
		
		//Print Result Matrix (DEBUG):
		if (debug == 1)
		{
			System.out.println("Result matrix:");
			for(i=0; i< Math.min(c_lin*c_col, 10); i++)
				System.out.print(c[i] + " ");
			System.out.println();
		}
	}
	
	public static void main(String[] args) {
		long start, end, t1, t2;
		
		if (args.length != 5)
		{
			System.out.println("Error expected 5 arguments: op initial final inc debug(1=on/0=off)");
			return;
		}
		
		int op = Integer.parseInt(args[0]);
		int initial = Integer.parseInt(args[1]);
		int finalSize = Integer.parseInt(args[2]);
		int inc = Integer.parseInt(args[3]);
		int debug = Integer.parseInt(args[4]);

		int matrix_size = initial;

		do {
			if (op == 0)
				OnMult(matrix_size, debug);
			else 
				OnMultLine(matrix_size, debug);

			// Increment matrix size:
			matrix_size += inc;
		} while (matrix_size <= finalSize);

	}
}
