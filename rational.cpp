#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cctype>
#include "../../includes/rational/rational.h"

Rational::Rational(){
    _error = -1;                                               

}
Rational::Rational(int numerator, int denominator){
    set_num(numerator);
    set_denom(denominator);
    _error = is_error();
}
Rational::Rational(int w){
    set_denom(1);
    set_num(w);
    _error = is_error();
}
void Rational::set(int numerator, int denominator){
    set_num(numerator);
    set_denom(denominator);
    _error = is_error();
}
void Rational::set_num(int n){
    _n = n;
    _error = is_error();
}
void Rational::set_denom(int d){
    _d = d;
    _error = is_error();
}
int Rational::get_num() const{
    if (_error > 0){
        return -MAX;
    } else if (_error == -1){
        return _n;
    }
}
int Rational::get_denom() const{
    if (_error > 0){
        return -MAX;
    } else if (_error == -1){
        return _d;
    }
}

int Rational::error() const{
    if (_error == 1){
        return 1;
    } else if (_error == 2){
        return 2;
    } else if (_error == 3){
        return 3;
    } else if (_error == 4){
        return 4;
    } else if (_error == 5){
        return 5;
    } else {
        return -1;
    }
}

string Rational::error_description() const{
    string error_desc;
    if (error() == 1){
        error_desc = "Denominator is 0. ";
    } else if (error() == 2){
        error_desc = "Denominator is greater than MAX (9999). ";
    } else if (error() == 3){
        error_desc = "Numerator is greater than MAX, (9999). ";
    } else if (error() == 4){
        error_desc = "Denominator is a non-integer value. ";
    } else if (error() == 5){
        error_desc == "Numerator is a non-integer value. ";
    }
    return error_desc;
}
void Rational::reset(){
    set_num(0);
    set_denom(1);
    _error = -1;

}

Rational operator+(const Rational &num1, const Rational &num2){            //ADDING FRACTIONS: [a/b + c/d] = [(ad + cb)/bd]
    Rational temp;
    int left_denom = num1.get_denom();
    int right_denom = num2.get_denom();
    int error = num1.error();
    int error2 = num2.error();
    if (left_denom == right_denom){                                                                       //IF DENOMINATORS =
        temp.set_denom(left_denom);                                                                       //Keep denominator
        temp.set_num((num1.get_num() + num2.get_num()));                                                  //Add numerators
        return temp;
    } else if (left_denom != right_denom){                                                                //IF DENOMINATORS !=
        temp.set_denom((left_denom * right_denom));                                                       //Multiply denominators together        -> b * d                                            
        temp.set_num((num1.get_num() * num2.get_denom()) + (num2.get_num() * num1.get_denom()));          //Multiply common factors, then add     -> (ad + cb)
        return temp;
    } else if (error > 0){
        return num1;
    } else if (error2 > 0){
        return num2;
    }
}
Rational operator-(const Rational &num1, const Rational &num2){            //SUBTRACTING FRACTIONS: [a/b - c/d] = [(ad - cd)/bd]
    Rational temp;
    int left_denom = num1.get_denom();
    int right_denom = num2.get_denom();
    int error = num1.error();
    int error2 = num2.error();
    if (left_denom == right_denom){                                                                        //IF DENOMINATORS = 
        temp.set_denom(left_denom);                                                                        //Keep denominator
        temp.set_num((num1.get_num() - num2.get_num()));                                                   //Subtract numerators
        return temp;
    } else if (left_denom != right_denom){                                                                 //IF DENOMINATORS !=
        temp.set_denom((left_denom * right_denom));                                                        //Multiply denominators togethers        -> b * d
        temp.set_num((num1.get_num() * num2.get_denom()) - (num2.get_num() * num1.get_denom()));             //Multiply common factors, then subtract -> (ad - cb)
        return temp;
    } else if (error > 0){
        return num1;
    } else if (error2 > 0){
        return num2;
    }
}
Rational operator*(const Rational &num1, const Rational &num2){             //MULTIPLYING FRACTIONS: a/b * c/d
    Rational temp;
    int error = num1.error();
    int error2 = num2.error();
    if (error < 0 && error2 < 0){
        temp.set_denom(num1.get_denom() * num2.get_denom());                //Denomninator -> b * d
        temp.set_num(num1.get_num() * num2.get_num());                      //Numerator    -> a * c
        return temp;
    } else if (error > 0){
        return num1;
    } else if (error2 > 0){
        return num2;
    }
}
Rational operator/(const Rational &num1, const Rational &num2){            //DIVIDING FRACTIONS: a/b / c/d = ad / bc
    Rational temp;
    int error = num1.error();
    int error2 = num2.error();
    if (error < 0 && error2 < 0){
        temp.set_denom((num1.get_denom() * num2.get_num()));
        temp.set_num(num1.get_num() * num2.get_denom());
        return temp;
    } else if (error > 0){
        return num1;
    } else if (error2 > 0){
        return num2;
    }
}
ostream &operator<<(ostream &outs, const Rational &num){
    if (num.error() > 0){
        outs << " UNDEFINED ";
    } else {
        outs << num.get_num() << "/" << num.get_denom();
    }
    return outs;
}
istream &operator>>(istream &ins, Rational &num){
    int numerator, denominator;
    char slash;
    cin >> numerator;
    cin >> slash;
    cin >> denominator;
    Rational temp(numerator, denominator);
    num = temp;
    return ins;
}

int Rational::is_error() const{                                     //ERROR CONDITIONS.... more..??
    string test = to_string(_d);
    string test2 = to_string(_n);
    if (_d == 0){                                                   // 1) Denominator = 0 -> undefined
        return 1; 
    } else if (_d>MAX || _d<-MAX){                   //48(0)// 4) user enters NON-INTEGER value for denominator (isdigit returns a #>0 if a digit, returns 0 if NOT a digit)
        return 2;                  
    } else if (_n>MAX || _n<-MAX){                                   // 5) user enters NON-INTEGER value for numerator
        return 3;
    }
    int length_d = 1, length_n = 1;
    int d = _d, n = _n;
    if (d>0){
        for (length_d = 0; d>0; length_d++){
            d = d/10;
        }
        for (int i=0; i<length_d; i++){
        if (isdigit(test[i]) == 0){
            return 4;
        }
    }
    for (int i=0; i<length_n; i++){
        if (isdigit(test2[i]) == 0){
            return 5;
        }
    }
    }
   
    return -1;                                                  
}
