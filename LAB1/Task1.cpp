#include<stdio.h>
#include <iostream>
#include<stdlib.h>
#include<math.h>
#include <chrono>
#include <thread>
#include <ctime>

# define M_PI 3.141592653589793 /* pi, #include <math.h> */

using namespace std;

/*----наша функция---*/
double function(double x)
{
	return 8/(1+x*x);
}
double analyticalSolution()
{	
	double a = 0;
	double b = 1;
	double area = 8 * atan(b) - 8 * atan(a);
	printf("Значение интеграла аналитически : %.7f\n", area);
	return area;
}

/*----метод трапеций---*/
double trapezium(int n)
{	

	double left		= 0; // нижняя граница
	double right	= 1; // верхняя граница 
	double sum		= 0;
	double runner;
	
	double step = (right - left) / n;
	/* формула трапеции */
	for (runner = left + step; runner < right; runner += step)
	sum += function(runner);
	sum = (sum + 0.5 * (function(left) + function(right))) * step;
	printf("Значение интеграла : %.7f количество интервалов : %d\n", sum,n);
	return sum;
}

int main()
{

	using namespace std::chrono;
	using namespace std;
	setlocale(LC_ALL, "Russian");

	for (int i = 100; i <= 1000000; i = i * 10)
	{
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		double trap = trapezium(i);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);
		cout <<  " Продолжительность : " << duration.count() << " секунд\n" << endl;
	}	

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	analyticalSolution();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> duration = (t2 - t1);
	cout << " Продолжительность : " << duration.count() << " секунд\n" << endl;

	return 0;
}
