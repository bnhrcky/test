#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <cctype>

using namespace std;

int const MAX = 9999;

class Rational{
    public:
        Rational();
        Rational(int numerator, int denominator);
        Rational(int w);

        //Mutators
        void set(int numerator, int denominator);
        void set_num(int n);
        void set_denom(int d);

        //Accessors
        int get_num() const;
        int get_denom() const;

        int error() const;
        string error_description() const;
        void reset();

        friend Rational operator + (const Rational& num1, const Rational& num2);
        friend Rational operator - (const Rational& num1, const Rational& num2);
        friend Rational operator * (const Rational& num1, const Rational& num2);
        friend Rational operator / (const Rational& num1, const Rational& num2);
        friend ostream& operator << (ostream& outs, const Rational& num);
        friend istream& operator >> (istream& ins, Rational& num);

    private:
        int is_error() const;
        int _n;
        int _d;
        int _error;
};



#endif
