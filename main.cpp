#include <iostream>
#include <fstream>
#include <sstream>
#include "Bignum.h"

using namespace std;

void test();
void getInput(const string &path_input, const string &path_output);
Bignum calculate(Bignum bignum1, string op, Bignum bignum2);

int main(int argc, char** argv) {
    getInput(argv[1], argv[2]);
//    test();
    return 0;
}

void test(){
    int i, j;
    for (i = 1; i <= 4 ; ++i) {
        for (j = 1; j < 40 - i; ++j) {
            printf(" ");
        }
        for (j = 1; j <= i; ++j) {
            printf("%d", j);
        }
        for (j = i - 1; j > 0; --j) {
            printf("%d", j);
        }
        printf("\n");
    }

    for (i = 3; i >= 1; --i) {
        for (j = 1; j < 40 - i; ++j) {
            printf(" ");
        }
        for (j = 1; j <= i; ++j) {
            printf("%d", j);
        }
        for (j = i - 1; j > 0; --j) {
            printf("%d", j);
        }
        printf("\n");
    }

}


void getInput(const string &path_input, const string &path_output){
    ifstream in(path_input);
    ofstream out(path_output);
    if (!in){
        cout << "fail to open file " + path_input << endl;
        return;
    }
    if (!out){
        cout << "fail to open file " + path_output << endl;
        return;
    }
    string feature;
    Bignum bignum1, bignum2;
    string op;
    getline(in, feature);
    while (getline(in, feature)){
        stringstream stringin(feature);
        stringin >> bignum1;
        while (stringin >> op >> bignum2){
            bignum1 = calculate(bignum1, op, bignum2);
        }
        out << bignum1 << endl;
    }
}


Bignum calculate(Bignum bignum1, string op, Bignum bignum2){
    if (op == "+"){
        return bignum1 + bignum2;
    } else if(op == "-"){
        return bignum1 - bignum2;
    } else if(op == "*"){
        return bignum1 * bignum2;
    } else if (op == "/"){
        return bignum1 / bignum2;
    }
}
