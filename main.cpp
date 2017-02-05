#include <cstdio>
#include <cstdlib>
#include <cmath>

// Rovnici si prepiseme na -(1/sin(x) y')' - sin(x) y = 0
// Takze p(x) = 1/sin(x), , q(x) = -sin(x), alpha1=alpha2=0, beta1=-1, beta2=1
// gamma1 = alpha, gamma2=beta
// Viz stranka 15 ve skriptech

// Poc. a konc. bod rovnou tiskneme. Vychazime z posl. rce vynasob. -h^2.

int main(int argc, char ** argv)
{
	double a = M_PI/2;
	double b = 7.0*M_PI/8;
	
	double alpha = (argc > 1) ? atof(argv[1]) : 2.3;
	double beta = (argc > 2) ? atof(argv[2]) : 2.7;
	const int n = (argc > 3) ? atoi(argv[3]) : 100;
	
	double h = (b-a)/(n+1);
	
	double y[n];
	double pod[n-1];
	double diag[n];
	double nad[n-1];
	
	y[0] = -alpha / sin(a+h);
	y[n-1] = -beta / sin(a+(n+1)*h);
	
	// f(x) = 0
	for (int i=1; i<n-1; i++)
		y[i] = 0;
	
	for (int i=0; i<n-1; i++)
	{
		nad[i] = 1/sin(a+h*(i+2));
		pod[i] = 1/sin(a+h*(i+2));
	}
	
	for (int i=0; i<n; i++)
		diag[i] = -(1/sin(a+h*(i+2)) + 1/sin(a+h*(i+1)) - h*h*sin(a+h*(i+1)));
	
	// tridiagonal. resic
	double q;
	for (int i=0; i<n-1; i++)
	{
		// nuly pod
		// pod[i] je na druhem radku
		q = pod[i] / diag[i];
		// q = pod[i+1] / diag[i];
		diag[i+1] -= q * nad[i];
		y[i+1] -= q * y[i];
	}
	
	for (int i=n-2; i>-1; i--)
	{
		// nuly nad
		q = nad[i] / diag[i+1];
		y[i] -= q * y[i+1];
	}
	
	// Jednotkova matice, v y je nyni reseni
	for (int i=0; i<n; i++)
		y[i] /= diag[i];
	
	// Vypiseme do terminalu
	printf("%f %f\n", a, alpha);
	for (int i=0; i<n; i++)
		printf("%f %f\n", a + (i+1)*h, y[i]);
	printf("%f %f\n", b, beta);
	
	// Vypiseme do souboru
	FILE *fp;
	fp = fopen("out.txt", "w+");
    fprintf(fp, "%f %f\n", a, alpha);
	for (int i=0; i<n; i++)
		fprintf(fp, "%f %f\n", a + (i+1)*h, y[i]);
	fprintf(fp, "%f %f\n", b, beta);
    fclose(fp);
	
	return 0;
}
