#include <cmath>

//C# version from http://www.codeproject.com/KB/recipes/LaplaceTransforms.aspx

class Laplace
{
	static const int DefaultStehfest = 14;
	static double ln2; // log of 2
public:
	static double (*f)(double t); 
	static double *V; //wspolczynniki Stehfesta
	static int NV; //liczba wspolczynnikow
	
	static void InitStehfest(int N)
	{
		ln2 = log(2.0);
		int N2 = N / 2;
		NV = 2 * N2;
		V = new double[NV];
		int sign = 1;
		if ((N2 % 2) != 0)
			sign = -1; 
		for (int i = 0; i < NV; i++){ 
			int kmin = (i + 2) / 2; 
			int kmax = i + 1; 
			if (kmax > N2) 
				kmax = N2; 
			V[i] = 0;
			sign = -sign;
			for (int k = kmin; k <= kmax; k++){ 
				V[i] = V[i] + (pow(k, N2) / Factorial(k)) * (Factorial(2 * k) 
				/ Factorial(2 * k - i - 1)) / Factorial(N2 - k) 
				/ Factorial(k - 1) / Factorial(i + 1 - k); 
			} 
			V[i] = sign * V[i]; 
		} 
	}

	static double Transform(double (*F)(double s), double s)
	{
		const int DefaultIntegralN = 5000;
		double du = 0.5 / (double)DefaultIntegralN;
		double y =  - F(0) / 2.0;
		double u = 0;
		double limit = 1.0 - 1e-10;
		while (u < limit){
			u += du;
			y += 2.0 * pow(u, s - 1) * F(log(u));
			u += du;
			y += pow(u, s - 1) * F(-log(u));
		}
		return 2.0 * y * du / 3.0;
	}

	static double InverseTransform(double (*f)(double t), double t)
	{
		double ln2t = ln2 / t; 
		double x = 0; 
		double y = 0; 
		for (int i = 0; i < NV; i++){ 
			x += ln2t; 
			y += V[i] * f(x); 
		}
		return ln2t * y; 
	}

	static double Factorial(int N)
	{
		double x = 1; 
		if (N > 1){
			for (int i = 2; i <= N; i++)
				x = i * x; 
		}
		return x; 
	} 
};

