#include <iostream>
#include <cmath>

#include "laplace.cpp"

using namespace std;

double func(double s){
	return 1.0/s;
}

int main(int argc, const char* argv[]){
	cout << "Inverse Laplace Transform implementation test.\n";
	double s;
	for(s=0.0;s<=30.0;s++){
		cout << s << "\t" << func(s) << "\t" << Laplace.InverseTransform(func(s), s) << endl;
	}
	return 0;
}

