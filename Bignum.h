
#ifndef LAB04_BIGNUM_H
#define LAB04_BIGNUM_H

#define Int(x) ((x) - '0')
#define Char(x) (char)((x) + '0')

#include <iostream>

class Bignum {
private:
    std::string value;
public:
    explicit Bignum();

    explicit Bignum(std::string value);

    Bignum operator+(const Bignum &bignum);

    Bignum operator-(const Bignum &bignum);

    Bignum operator*(const Bignum &bignum);

    Bignum operator/(const Bignum &bignum);

    friend std::ostream &operator<<(std::ostream &ostream, Bignum &bignum);

    friend std::istream &operator>>( std::istream  &input, Bignum &bignum );

private:
    std::string add(std::string num1, std::string num2);

    std::string subtruct(std::string num1, std::string num2);

    std::string bigSubSmall(std::string num1, std::string num2);

    std::string multiply(char num1, char num2, int places);

    int divide(std::string &num1, std::string num2);

    std::string split_zero(std::string number);
};


#endif //LAB04_BIGNUM_H
