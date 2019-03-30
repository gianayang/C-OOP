#include <string>
#include <vector>

#ifndef RATIONAL_H
#define RATIONAL_H
namespace CS2124 {
	class Rational {
		friend std::ostream& operator << (std::ostream&os, const Rational&rational);
		friend std::istream& operator >> (std::istream& os, Rational& rational);
		friend bool operator ==(const Rational& lhs, const Rational& rhs);
		friend bool operator <(const Rational& lhs, const Rational& rhs);
	public:
		Rational();
		Rational(int numerator, int denominator);
		Rational(int num);
		Rational& operator += (const Rational& rhs);
		Rational& operator ++();
		Rational operator ++(int dummy);
		explicit operator bool()const;
	private:
		void nomalized();
		int numerator;
		int denominator;
	};
	Rational operator + (const Rational& lhs, const Rational& rhs);
	int greatestCommonDivisor(int x, int y);
	bool operator !=(const Rational& lhs, const Rational& rhs);
	Rational& operator --(Rational& lhs);
	Rational operator --(Rational& lhs, int dummy);
	bool operator >=(Rational& lhs, Rational& rhs);
	bool operator <=(Rational& lhs, Rational& rhs);
	bool operator >(Rational& lhs, Rational& rhs);
}

#endif // !1

