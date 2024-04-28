#include "Polynomial.h"
using namespace std;

int main()
{
	cout << "Testing the Polynomial class" << endl;
	cout << "INPUT RULE OF MONOMIALS: <coefficient(double)><x^><xPow(int)><y^><yPow(int)><z^><zPow(int)>" << endl;
	cout << "Select operation:" << endl;
	cout << "1. Polynomial * constant" << endl;
	cout << "2. Polynomial * Polynomial" << endl;
	cout << "3. Polynomial + Polynomial" << endl;
	cout << "4. Polynomial - Polynomial" << endl;
	u_short num = 0;
	cin >> num;
	Polynomial first;
	Polynomial second;
	try
	{
		switch (num)
		{
		case 1:
			cout << "Enter polynomial:" << endl;
			cin >> first;
			double val;
			cout << "Enter constant:" << endl;
			cin >> val;
			cout << "Result: " << first * val << endl;
			break;
		case 2:
			cout << "Enter first polynomial:" << endl;
			cin >> first;
			cout << "Enter second polynomial:" << endl;
			cin >> second;
			cout << "Result: " << first * second << endl;
			break;
		case 3:
			cout << "Enter first polynomial:" << endl;
			cin >> first;
			cout << "Enter second polynomial:" << endl;
			cin >> second;
			cout << "Result: " << first + second << endl;
			break;
		case 4:
			cout << "Enter first polynomial:" << endl;
			cin >> first;
			cout << "Enter second polynomial:" << endl;
			cin >> second;
			cout << "Result: " << first - second << endl;
			break;
		default:
			cout << "Wrong number!";
			break;
		}
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
}

