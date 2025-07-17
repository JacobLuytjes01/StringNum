#include <iostream>
using namespace std;
#include "StringNum.cpp"

ostream& operator<<(ostream& out, const StringNum& b){
    out << b.getNumber();
    return out;
}

int main() {
    StringNum str1("33");
    StringNum str1B("99");
    StringNum str1C("2");
    StringNum str1D("49.94");

    StringNum str2("29.123123");
    StringNum str3("999.999");
    StringNum str4("9999.9999");
    StringNum str5("555.23");
    StringNum str6("555.77");
    StringNum str7("-555.77");

    /*
    cout << ++str1 << endl; // 34.0
    cout << str1++ << endl; // 34.0
    cout << str1 << endl; // 35.0
    */

    /*
    cout << str1D * str1D << endl; // 2494.0036
    cout << str2 + str2 << endl; // 58.246246
    cout << str3 * str3 << endl; // 999998.000001
    cout << str2 * str1C << endl; // 58.246246
    cout << str1C * str2 << endl; // 58.246246
    cout << str7 * str7 << endl; // 308880.2929
    cout << str1C * str1C << endl; // 4.0
    cout << str4 * str1C << endl; // 19999.9998

    // should both be -0.54
    cout << str5 + str7 << endl;
    cout << str7 + str5 << endl;

    // should be 0.0
    cout << (str7 + str5) -  (str7 + str5) << endl;

    // should all be -0.54
    cout << StringNum("0.0") + (str7 + str5) << endl;
    cout << (str7 + str5) + StringNum() << endl;
    cout << ((str7 + str5) -  (str7 + str5)) - (str7 + str5) << endl;
    cout << (str7 + str5) -  ((str7 + str5) - (str7 + str5)) << endl;

    // should be 10999.9989
    cout << str3 + str4 << endl;


    cout << str2 - str6 << endl; // -526.646877
    cout << str6 - str2 << endl; // 526.646877

    cout << str1-str1B << endl; // -66


    cout << "True Side >=" << endl;
    cout << (str1B >= str1) << " " << (str1B >= str2) << " " << (str4 >= str3) << " " << (str6 >= str5) << endl;
    cout << (str4 >= str1) << " " << (str4 >= str2) << " " << (str4 >= str3) << " " << (str4 >= str5) << endl;
    cout << (str4 >= str4) << " " << (str2 >= str2) << " " << (str3 >= str3) << " " << (str5 >= str5) << endl;
    cout << "False Side >=" << endl;
    cout << (str1 >= str1B) << " " << (str2 >= str1B) << " " << (str3 >= str4) << " " << (str5 >= str6) << endl;
    cout << (str1 >= str4) << " " << (str2 >= str4) << " " << (str3 >= str4) << " " << (str5 >= str4) << endl;

    cout << "True Side >" << endl;
    cout << (str1B > str1) << " " << (str1B > str2) << " " << (str4 > str3) << " " << (str6 > str5) << endl;
    cout << (str4 > str1) << " " << (str4 > str2) << " " << (str4 > str3) << " " << (str4 > str5) << endl;
    cout << "False Side >" << endl;
    cout << (str4 > str4) << " " << (str2 > str2) << " " << (str3 > str3) << " " << (str5 > str5) << endl;
    cout << (str1 > str1B) << " " << (str2 > str1B) << " " << (str3 > str4) << " " << (str5 > str6) << endl;
    cout << (str1 > str4) << " " << (str2 > str4) << " " << (str3 > str4) << " " << (str5 > str4) << endl;



    str1 = str2 + str1;
    str1 = str2 - str1;
    cout << str1 << endl;
    //str3 = str3 + str4;
    str3 = str3 - str4;
    cout << str3 << endl;
    //str5 = str5 + str6;
    str5 = str5 - str6;
    cout << str5 << endl;


    StringNum a = 0;
    StringNum b = 1;
    StringNum temp = 1;

    for (int i = 1; i <= 9; i++) {
        temp = a + b;
        a = b;
        b = temp;
        cout << temp << "\n";
    }

    /*
    StringNum a2 = 100;
    int x = 100;
    for (int i = 1; i <= 150; ++i) {
        a2 = a2 - i;
        x = x - i;
        if (a2 != x) {
            cout << a2 << " : " << x << endl;
        }
    }

    StringNum a2 = 80;
    long x = 80;
    for (int i = 1; i <= 10; ++i) {
        a2 = a2 * (StringNum(-1) - StringNum(i));
        x = x * (-1 - i);
        if (a2 != x) {
            cout << a2 << " : " << x << endl;
        }
    }
    */
    return 0;
}
