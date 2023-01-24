#include <iostream>
#include <stdexcept>
#include <string>
#include <math.h>

using namespace std;

class MyExcept1 {};

class MyExcept2 {
	string msg;
public:
	MyExcept2(const string& s) : msg(s) {}
	const char* message() const { return msg.c_str(); }
};

class MyExcept3 : public invalid_argument {
	double num1;
	double num2;
public:
	MyExcept3(const string msg, double n, double m) : invalid_argument(msg), num1(n), num2(m) {}
	double arg() const { return num1; }
};

void root1(double a, double b) {
	double a1 = asin(a / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	double b1 = asin(b / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	cout << "A = " << a1 << ". B = " << b1 << "." << endl;
}

double root2(double a, double b) throw() {
	double a1 = asin(a / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	double b1 = asin(b / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	cout << "A = " << a1 << ". B = " << b1 << "." << endl;
}

double root3(double a, double b) throw(invalid_argument) {
	if (b <= 0.0 || a <= 0.0)
		throw invalid_argument("Недопустимые значения катетов.");
	double a1 = asin(a / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	double b1 = asin(b / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	cout << "A = " << a1 << ". B = " << b1 << "." << endl;
}

double root4_1(double a, double b) throw(MyExcept1) {
	if (b <= 0.0 || a <= 0.0)
		throw MyExcept1();
	double a1 = asin(a / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	double b1 = asin(b / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	cout << "A = " << a1 << ". B = " << b1 << "." << endl;
}

double root4_2(double a, double b) throw(MyExcept2) {
	if (b <= 0.0 || a <= 0.0)
		throw MyExcept2("Недопустимые значения катетов.");
	double a1 = asin(a / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	double b1 = asin(b / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	cout << "A = " << a1 << ". B = " << b1 << "." << endl;
}

double root4_3(double a, double b) throw(MyExcept3) {
	if (b <= 0.0 || a <= 0.0)
		throw MyExcept3("Недопустимые значения катетов.", a, b);
	double a1 = asin(a / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	double b1 = asin(b / (sqrt((a * a) + (b * b)))) * 180 / 3.1415;
	cout << "A = " << a1 << ". B = " << b1 << "." << endl;
}

void launcher(void (*func)(double, double)) {
	double a, b;
	cout << "Введите первый катет: ";
	cin >> a;
	cout << "Введите второй катет: ";
	cin >> b;
	cout << "Углы прямоугольного треугольника: " << endl;
	func(a, b);
}

int main() {
	setlocale(LC_ALL, "rus");
	cout << "Функция вычисляет углы прямоугольного треугольника.\n";

	try {
		launcher(root1);
	}
	catch (...) {
		cout << "Произошло исключение в функции root1" << endl;
	}

	try {
		launcher(root2);
	}
	catch (...) {
		cout << "Произошло исключение в функции root2" << endl;
	}

	try {
		launcher(root3);
	}
	catch (invalid_argument& e) {
		cout << e.what() << endl;
	}

	try {
		launcher(root4_1);
	}
	catch (MyExcept1) {
		cout << "Произошло исключение MyExcept1 в функции root4_1" << endl;
	}

	try {
		launcher(root4_2);
	}
	catch (MyExcept2& e) {
		cout << e.message() << endl;
	}

	try {
		launcher(root4_3);
	}
	catch (MyExcept3& e) {
		cout << e.what() << " " << e.arg() << endl;
	}
}
