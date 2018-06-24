
#include "Bignum.h"
Bignum::Bignum() = default;

Bignum::Bignum(std::string value) {
    this->value = value;
}
Bignum Bignum::operator+(const Bignum &bignum) {
    std::string num1 = value;
    std::string num2 = bignum.value;
    std::string result;
    int num1IsNev = num1.find('-');
    int num2IsNev = num2.find('-');
    num1 = num1.substr(num1IsNev + 1);
    num2 = num2.substr(num2IsNev + 1);

    if (num1IsNev == -1 && num2IsNev == -1){ // 都是正数
        result = add(num1, num2);
    } else if (num1IsNev != -1 && num2IsNev != -1){ // 都是负数
        result = "-" + add(num1, num2);
    } else if (num1IsNev == -1){ // num1 正，num2 负
        result = subtruct(num1, num2);
    } else{
        result = subtruct(num2, num1);
    }
    Bignum bignum_result(result);
//    bignum_result.value = result;
    return bignum_result;
}

Bignum Bignum::operator-(const Bignum &bignum) {
    std::string result;
    std::string num1 = value;
    std::string num2 = bignum.value;
    int num1IsNev = num1.find('-');
    int num2IsNev = num2.find('-');
    num1 = num1.substr(num1IsNev + 1);
    num2 = num2.substr(num2IsNev + 1);

    if (num1IsNev == -1 && num2IsNev == -1){ // 都是正数
        result = subtruct(num1, num2);
    } else if (num1IsNev != -1 && num2IsNev != -1){ // 都是负数
        result = subtruct(num2, num1);
    } else if (num1IsNev == -1){ // num1 正，num2 负
        result = add(num1, num2);
    } else{
        result = "-" + add(num1, num2);
    }
    Bignum bignum_result(result);
    return bignum_result;
}

Bignum Bignum::operator*(const Bignum &bignum) {
    std::string num1 = value;
    std::string num2 = bignum.value;
    int num1IsNev = num1.find('-');
    int num2IsNev = num2.find('-');
    num1 = num1.substr(num1IsNev + 1);
    num2 = num2.substr(num2IsNev + 1);
    int len1 = num1.length();
    int len2 = num2.length();

    std::string result = "0";
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            result = add(result, multiply(num1[len1 - i - 1], num2[len2 - j - 1], i + j));
        }
    }
    if ((num1IsNev == -1 && num2IsNev != -1) || (num1IsNev != -1 && num2IsNev == -1)){ // 都是正数
        result = "-" + result;
    }
    Bignum bignum_result(result);
    return bignum_result;
}

Bignum Bignum::operator/(const Bignum &bignum) {
    std::string num1 = value;
    std::string num2 = bignum.value;

    int num1IsNev = num1.find('-');
    int num2IsNev = num2.find('-');
    num1 = num1.substr(num1IsNev + 1);
    num2 = num2.substr(num2IsNev + 1);
    int len1 = num1.length();
    int len2 = num2.length();

    std::string result;
    std::string head = "0";
    for (int i = 0; i < len1 - len2 + 1; ++i) {
        result.append(std::to_string(divide(num1, num2)));
        num2 = head + num2;
    }
    result = split_zero(result);
    if ((num1IsNev == -1 && num2IsNev != -1) || (num1IsNev != -1 && num2IsNev == -1)){ // 都是正数
        result = "-" + result;
    }
    Bignum bignum_result(split_zero(result));
    return bignum_result;
}

std::ostream &operator<<(std::ostream &ostream, Bignum &bignum) {
    ostream << bignum.value;
    return ostream;
}

std::istream &operator>>(std::istream &input, Bignum &bignum) {
    std::string string;
    input >> string;
//    if (string.length() <= 40){
        bignum.value = string;
        return input;
//    }
//    std::cout << "the length of your number should be less than 40" << std::endl;
//    return input;
}

std::string Bignum::add(std::string num1, std::string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    int result_len = len1 > len2 ? len1 : len2;
    std::string result;
    for (int i = 0; i < result_len; ++i) {
        result.append("0");
    }

    int flag = 0;
    for (int i = 0; i < result_len; ++i) {
        if (i < len1) flag += Int(num1[len1 - 1 - i]);
        if (i < len2) flag += Int(num2[len2 - 1 - i]);
        result[result_len - 1 - i] = Char(flag % 10);
        flag /= 10;
    }
    if (flag == 1)
        result = '1' + result;
    return result;
}


std::string Bignum::subtruct(std::string num1, std::string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    if (len1 > len2){
        return split_zero(bigSubSmall(num1, num2));
    }
    else if (len1 < len2){
        return  '-' + split_zero(bigSubSmall(num2, num1));
    } else{
        for (int i = 0; i < len1; ++i) {
            if (num1[i] > num2[i]){
                return split_zero(bigSubSmall(num1, num2));
            }
            else if (num1[i] < num2[i]){
                return '-' + split_zero(bigSubSmall(num2, num1));
            }
        }
        return  "0";
    }
}

std::string Bignum::bigSubSmall(std::string num1, std::string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    int flag = 0;
    for (int i = 0; i < len1; ++i) {
        if (i < len2){
            flag -= num2[len2 - i - 1];
        } else{
            flag -= '0';
        }
        flag += num1[len1 - i - 1];
        if (flag < 0){
            num1[len1 - i - 1] = Char(flag + 10);//(char)(flag + 10 + '0');
            flag = -1;
        } else{
            num1[len1 - i - 1] = Char(flag);//(char)(flag + '0');
            flag = 0;
        }

    }
    return num1;
}

std::string Bignum::multiply(char num1, char num2, int places) {
    std::string result;
    std::string tmp = std::to_string(Int(num1) * Int(num2));
    result.append(tmp);
    for (int i = 0; i < places; ++i) {
        result.append("0");
    }
    return result;
}

int Bignum::divide(std::string &num1, std::string num2) {
    int len = num2.length();
    std::string num1_start = num1.substr(0, len);
    int flag = 0;
    while (num1_start >= num2){
        flag++;
        num1_start = bigSubSmall(num1_start, num2);
    }
    int zero_len = len - num1_start.length();
    for (int i = 0; i < zero_len; ++i) {
        num1[i] = '0';
    }

    for (int i = zero_len; i < len; ++i) {
        num1[i] = num1_start[i];
    }
    return flag;
}

std::string Bignum::split_zero(std::string number) {
    int start = number.find_first_not_of('0');
    if (start == -1)
        return "0";
    return number.substr(start);
}










