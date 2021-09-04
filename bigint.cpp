#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "bigint.h"



BigInteger::BigInteger() {
	num = "0"; 
}

BigInteger::BigInteger(std::string a) {
	num = a;
}

void BigInteger::display(){
	std::cout << num << std::endl;
}


// Comparator Function, returns 1 or 2 depending on which number is greater

int BigInteger::Compfunc(std::string a, std::string b) {
	if (a == b) { return 1; }
	if (a.size() > b.size()) { return 1; }
	if (a.size() < b.size()) { return 2; }
	if (a.size() == b.size()) {
		for (int i = 0; i < a.size(); i++) {
			if (a[i] > b[i]) { return 1; }
			if (a[i] < b[i]) { return 2; }
		}
	}
}

// Since some of the arithmatic operations involve adding zero's to match size of both numbers
// We do have to remove the extra zero's

void Zero_remove(std::string& a) {
	int i = 0;
	while (a[i] == '0') {
		a.erase(i, 1);
	}
}

// Addition function
// Takes in size difference of both objects, and adds corresponding zero's to the shorter object
// Simple visualization of how we added numbers in elementary school
// Adding both values from the right end, and if they end up being greater than 9, add the carry to the next number
// The value at any index is also done a modulus of 10, carry is a division of the sum by 10

std::string BigInteger::Addfunc(std::string a, std::string b) {
	//std::cout << a.size() - b.size() << std::endl;
	int diff = a.size() - b.size();
	int length = std::max(a.size(), b.size()), b1;
	char carry = '0' - 48;
	//std::cout << carry << " ";
	if (b.size() < a.size()) { for (int j = 0; j < diff; j++) { b.insert(0, "0"); } }
	b1 = b.size() - 1;
	std::string result(length + 1, '0');
	if (a.size() > b.size() || a.size() == b.size()) {
		for (int i = a.size() - 1; b1 >= 0; i--) {
			//std::cout << "A Bigger" << " ";
			result[length] = a[i] + b[b1] + carry - 96;
			if (result[length] > 9) { carry = ((a[i] + b[b1] + carry - 96) / 10); }
			else { carry = '0' - 48; }
			//std::cout << "Carry: " << carry << " ";
			result[length] = result[length] % 10;
			result[length] += 48;
			////std::cout << "Result: " << result[length] << std::endl;
			length -= 1;
			b1 -= 1;
		}
		//std::cout << "Carry: " << carry << std::endl;
		if (carry > '0' - 48) { result[length] = 48 + carry; }
		//std::cout << result.size() << std::endl;
		if (result[0] == '0') { Zero_remove(result); }
		return result;
	}


}


// Subtraction Function
// Similar to addition, adding leading zeroes to the relevant object
// For loop runs on the basis of the bigger number, and if the difference of the subtrahend and minuend subtracted by the borrow is a negative value, add 10 and borrow set to 1
// This allows for carry forward of the borrow, as any difference value that is negative will keep the borrow on it until a donator is reached

std::string BigInteger::SubtractFunc(std::string a, std::string b) {
	int sub = Compfunc(a, b), length = std::max(a.size(), b.size());
	char borrow = '0' - 48;
	std::string difference(length, '0');
	int diff = a.size() - b.size();
	if (b.size() < a.size()) { for (int i = 0; i < diff; i++) { b.insert(0, "0"); } }
	if (sub == 1) {
		for (int i = a.size() - 1; i >= 0; i--) {
			length -= 1;
			if (a[i] - b[i] - borrow < 0) { difference[length] = a[i] + 10 - b[i] - borrow + 48; borrow = '1' - 48; }
			else {
				difference[length] = 48 + a[i] - b[i] - borrow;
				borrow = '0' - 48;
			}
		}
		Zero_remove(difference);
		return difference;
	}

}

// Multiplication Function
// Complementary 1 and 0 return values
// A two pointer approach works here, one at the initial index and the second at the last index of our return object
// Where everytime we get done with one loop of multiplications, it results in a decrease of the second pointer, simulating how we multiply tens,hundreds,thousands position
// Subsequent addition of the values pre-existing with the multiplied values

std::string BigInteger::MultiFunc(std::string a, std::string b) {
	int length = (a.size() + b.size());
	std::string prod(length, '0');
	//std::cout << prod << std::endl;
	if (a == "0" || b == "0") { prod = "0"; return prod; }
	if (a == "1" || b == "1") { if (a == "1") { prod = b; return prod; } else if (b == "1") { prod = a; return prod; } }
	int l1 = a.size() - 1, l2 = b.size() - 1, ptr1 = 1, ptr2;
	length -= 1;
	if (a.size() > b.size() || a.size() == b.size()) {
		for (l2; l2 >= 0; l2--) {
			char sum = '0' - 48, carry = '0';
			ptr2 = a.size() + b.size() - ptr1;
			for (l1; l1 >= 0; l1--) {
				carry -= 48;
				//std::cout << (b[l2] - '0') << " " << a[l1] - '0' << std::endl;
				sum = (b[l2] - '0') * (a[l1] - '0') + carry + (prod[ptr2] - '0');
				//std::cout << "Sum: " << (b[l2] - '0') * (a[l1] - '0') + carry + (prod[ptr2] - '0') << std::endl;
				prod[ptr2] = (sum % 10) + 48;
				//std::cout << "Product: " << prod[ptr2] << std::endl;
				carry = sum / 10 + 48;
				//std::cout << "Carry: " << carry << std::endl;
				ptr2 -= 1;
			}
			if (carry > '0') { prod[ptr2] = sum / 10 + 48; }
			ptr1 += 1;
			l1 = a.size() - 1;
			//std::cout << prod << std::endl;
		}
		if (prod[0] == '0') { Zero_remove(prod); }
		return prod;
	}
}


// Factorial Function
// Standard iterative factorial, where a temporary variable allows us to increment by one whilst we multiply our return value

std::string BigInteger::Factorial(std::string a) {
	std::string j = "1", i{}, add = "1", temp, num = "1";
	if (a == "1" || a == "0") {
		return j;
	}
	std::cout << a << std::endl;
	while (num != a) {
		i = BigInteger::Addfunc(num, add);
		num = i;
		std::cout << "num: " << num << std::endl;
		temp = BigInteger::MultiFunc(j, num);
		std::cout << "temp: " << temp << std::endl;
		j = temp;
		std::cout << "num: " << num << " " << "a: " << a << " " << std::endl;
	}
	return j;


}

// Fibonacci Function
// Iterative

std::string BigInteger::Fibonacci(std::string a) {
	std::string j = "1", t = "0", temp, i = "2";
	if (a == "0") { return t; }
	if (a == "1") { return j; }
	a = BigInteger::Addfunc(a, "1");
	while (i != a) {
		temp = BigInteger::Addfunc(j, t);
		std::cout << temp << std::endl;
		t = j;
		j = temp;
		i = BigInteger::Addfunc(i, "1");
	}
	return j;

}


void BigInteger::operator=(BigInteger const &a) {
	this->num = a.num;
}

void BigInteger::operator=(std::string const &a) {
	this->num = a;
}

BigInteger BigInteger::operator+(BigInteger const &a) {
	BigInteger temp;
	std::cout << "Constructing a new object" << std::endl;
	std::cout << this->num << " " << a.num << std::endl;
	temp = Addfunc(this->num, a.num);
	return temp;

}

BigInteger BigInteger::operator-(BigInteger const &a) {
	BigInteger temp;
	temp = SubtractFunc(this->num, a.num);
	return temp;
}

BigInteger BigInteger::operator*(BigInteger const& a) {
	BigInteger temp;
	temp = MultiFunc(this->num, a.num);
	return temp;
}
