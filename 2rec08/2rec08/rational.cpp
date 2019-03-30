#include "Rational.h"
using namespace std;

namespace CS2124 {
	int greatestCommonDivisor(int x, int y) {
		while (y != 0) {
			int temp = x % y;
			x = y;
			y = temp;
		}
		return x;
	}

	void Rational::nomalized() { //nomalize the number
		int greatDivid = greatestCommonDivisor(abs(numerator), abs(denominator));
		if (numerator < 0 && denominator < 0) {
			numerator = numerator / greatDivid * -1;
			denominator = denominator / greatDivid * -1;
		}
		else if (denominator < 0 && numerator > 0) {
			numerator = numerator / greatDivid * -1;
			denominator = denominator / greatDivid * -1;
		}
		else {
			numerator /= greatDivid;
			denominator /= greatDivid;
		}
	}

	Rational::Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
		nomalized();
	}
	Rational::Rational() : numerator(0), denominator(1) {}
	Rational::Rational(int num): numerator(num),denominator(1){}
	Rational& Rational::operator += (const Rational& rhs) {
		int diviedNum = greatestCommonDivisor(abs(denominator), abs(rhs.denominator));
		int numeratorTemp1 = numerator * (rhs.denominator / diviedNum);
		int denoTemp1 = denominator * (rhs.denominator / diviedNum);
		int numeratorTemp2 = rhs.numerator*(denominator / diviedNum);
		numerator = numeratorTemp1 + numeratorTemp2;
		denominator = denoTemp1;
		nomalized();
		return *this;
	}
	Rational& Rational::operator ++() {
		numerator += denominator;
		nomalized();
		return *this;
	}
	Rational Rational::operator ++(int dummy) {
		Rational ret=*this;
		numerator += denominator;
		nomalized();
		return ret;
	}
	Rational::operator bool()const {
		return(numerator != 0);
	}
	
	ostream& operator << (ostream&os, const Rational& rational) {
		if (rational.denominator != 1) {
			os << rational.numerator << "/" << rational.denominator;
		}
		else {
			os << rational.numerator;
		}
		return os;
	}

	istream& operator >> (std::istream& is, Rational& rational) {
		char slash;
		is >> rational.numerator >> slash >> rational.denominator;
		rational.nomalized();
		return is;
	}

	Rational operator + (const Rational& lhs, const Rational& rhs) {
		Rational ret = lhs;
		ret += rhs;
		return ret;
	}

	bool operator ==(const Rational& lhs, const Rational& rhs) {
		return(lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator);
	}
	
	bool operator !=(const Rational& lhs, const Rational& rhs) {
		return(!(lhs == rhs));
	}

	bool operator <(const Rational& lhs, const Rational& rhs) {
		int diviedNum = greatestCommonDivisor(abs(lhs.denominator), abs(rhs.denominator));
		int numeratorTemp1 = lhs.numerator * (rhs.denominator / diviedNum);
		int denoTemp1 = lhs.denominator * (rhs.denominator / diviedNum);
		int numeratorTemp2 = rhs.numerator*(lhs.denominator / diviedNum);
		return(numeratorTemp1 < numeratorTemp2);
	}
	bool operator >=(Rational& lhs, Rational& rhs) {
		return(!(lhs < rhs));
	}
	bool operator <=(Rational& lhs, Rational& rhs) {
		return((lhs < rhs) || (lhs == rhs));
	}
	bool operator >(Rational& lhs, Rational& rhs) {
		return(!(lhs < rhs) && !(lhs == rhs));
	}

	Rational& operator --(Rational& lhs) {
		Rational minus(-1);
		lhs.operator+=(minus);//reduce the number by negative one
		return lhs;
	}
	Rational operator --(Rational& lhs, int dummy) {//return the result before reduce it by one
		Rational minus(-1);
		Rational result = lhs;
		lhs.operator+=(minus);
		return result;
	}

}