#include<stdio.h>
#include <iostream>
#include<stdlib.h>
#include<math.h>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;



void trapezium_p(double left, double right,int n,double& sum_t)
{
	///*----наша функция---*/
	sum_t = 8 / (1 + left * left);
	double runner;

	double step = (right - left) / n;
	/* формула трапеции */
	for (runner = left + step; runner < right; runner += step)
		sum_t += 8 / (1 + runner * runner);
	sum_t = (sum_t + 0.5 * (8 / (1 + left * left) + 8 / (1 + right * right))) * step;


}

int main()
{
	setlocale(LC_ALL, "Russian");
	using namespace std::chrono;
	using namespace std;

	cout << "Метод трапеций на 4-х потоках:" << endl;
	for (int i = 100; i <= 1000000; i = i * 10)
	{
		double area1 = 0;
		double area2 = 0;
		double area3 = 0;
		double area4 = 0;
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		std::thread thr1(trapezium_p, 0, 0.25, i, std::ref(area1));
		std::thread thr2(trapezium_p, 0.25, 0.5, i, std::ref(area2));
		std::thread thr3(trapezium_p, 0.5, 0.75, i, std::ref(area3));
		std::thread thr4(trapezium_p, 0.75, 1, i, std::ref(area4));
		thr1.join();
		thr2.join();
		thr3.join();
		thr4.join();
		double area = area1 + area2 + area3 + area4;
		printf("Значение интеграла : %.7f количество интервалов : %d\n", area, i);
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration <double> duration = (t2 - t1);
		cout << " Продолжительность : " << duration.count() << " секунд\n" << endl;
	}

	return 0;
}
