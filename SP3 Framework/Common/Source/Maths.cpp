#include "Maths.h"

int GetSmaller(int a, int b) {

	if (a < b) {
		return a;
	}

	return b;

}

int GetLarger(int a, int b) {

	if (a > b) {
		return a;
	}

	return b;

}

int LCM(int a, int b) {

	if (a < 0) {
		a = -a;
	}
	if (b < 0) {
		b = -b;
	}

	return (a * (b / HCF(a, b)));

}

unsigned int LCM(unsigned int a, unsigned int b) {

	return (a * (b / HCF(a, b)));

}

int HCF(int a, int b) {

	if (a < 0) {
		a = -a;
	}
	if (b < 0) {
		b = -b;
	}

	if (b == 0) {
		return a;
	}

	return HCF(b, a % b);

}

unsigned int HCF(unsigned int a, unsigned int b) {

	if (b == 0) {
		return a;
	}

	return HCF(b, a % b);

}

int Abs(int a) {

	if (a < 0) {
		return -a;
	}

	return a;

}