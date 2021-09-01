#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>


class BigInteger{
	std::string num;
public:
	BigInteger();
	BigInteger(std::string a);
	int Compfunc(std::string a, std::string b);
	std::string Addfunc(std::string a, std::string b);
	std::string SubtractFunc(std::string a, std::string b);
	std::string MultiFunc(std::string a, std::string b);
	std::string Factorial(std::string a);
	std::string Fibonacci(std::string a);
	const std::string display();
};


