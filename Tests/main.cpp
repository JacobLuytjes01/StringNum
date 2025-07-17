#include <iostream>
using namespace std;
#include "../StringNum.cpp"

ostream& operator<<(ostream& out, const StringNum& b){
    out << b.getNumber();
    return out;
}
void CheckNum(const StringNum& a, const StringNum& b, bool& check) {
    if (a != b) {
        check = false;
        cout << a.getNumber() << " != " << b.getNumber() << endl;
    }
}
void CheckNum2(const StringNum& a, const string& s, bool& check) {
    if (a < StringNum(s)) {
        check = false;
        cout << "< failed on "<< a << " : " << s << endl;
    }
    if (a > StringNum(s)) {
        check = false;
        cout << "> failed on "<< a << " : " << s << endl;
    }
}
void CheckNumLeftBigger(const StringNum& a, const string& s, bool& check) {
    if (!(a >= StringNum(s) && a > StringNum(s))) {
        check = false;
        cout << "Left not bigger on "<< a << " : " << s << endl;
    }
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

    bool allTestsPass = true;

    CheckNum(++str1, StringNum("34.0"), allTestsPass);
    CheckNum(str1++, StringNum("34.0"), allTestsPass);
    CheckNum(str1, StringNum("35.0"), allTestsPass);

    CheckNum(--str1, StringNum("34.0"), allTestsPass);
    CheckNum(str1--, StringNum("34.0"), allTestsPass);
    CheckNum(str1, StringNum("33.0"), allTestsPass);

    CheckNum(str1D * str1D, StringNum("2494.0036"), allTestsPass);
    CheckNum(str2 + str2, StringNum("58.246246"), allTestsPass);
    CheckNum(str3 * str3, StringNum("999998.000001"), allTestsPass);
    CheckNum(str2 * str1C, StringNum("58.246246"), allTestsPass);
    CheckNum(str1C * str2, StringNum("58.246246"), allTestsPass);
    CheckNum(str7 * str7, StringNum("308880.2929"), allTestsPass);
    CheckNum(str1C * str1C, StringNum("4.0"), allTestsPass);
    CheckNum(str4 * str1C, StringNum("19999.9998"), allTestsPass);

    CheckNum(str5 * str7, StringNum("-308580.1771"), allTestsPass);
    CheckNum(str7 * str5, StringNum("-308580.1771"), allTestsPass);

    CheckNum((str7 + str5) -  (str7 + str5), StringNum("0.0"), allTestsPass);
    CheckNum((str7 + str5) -  (str7 + str5), StringNum("-0.0"), allTestsPass);

    CheckNum2((str7 + str5) -  (str7 + str5), "0.0", allTestsPass);
    CheckNum2((str7 + str5) -  (str7 + str5), "-0", allTestsPass);
    CheckNum((str7 + str5) -  (str7 + str5), StringNum("-0"), allTestsPass);
    CheckNum2(StringNum(5), "5", allTestsPass);
    CheckNum2(StringNum("0.5"), "0.5", allTestsPass);

    CheckNum(StringNum("0.0") + (str7 * str5), StringNum("-308580.1771"), allTestsPass);
    CheckNum((str7 + str5) + StringNum(), StringNum("-0.54"), allTestsPass);
    CheckNum(((str7 + str5) -  (str7 + str5)) - (str7 + str5), StringNum("-0.54"), allTestsPass);
    CheckNum((str7 + str5) -  ((str7 + str5) - (str7 + str5)), StringNum("-0.54"), allTestsPass);

    CheckNum(str3 + str4, StringNum("10999.9989"), allTestsPass);

    CheckNum(str2 - str6, StringNum("-526.646877"), allTestsPass);
    CheckNum(str6 - str2, StringNum("526.646877"), allTestsPass);

    CheckNumLeftBigger(StringNum(5), "4", allTestsPass);
    CheckNumLeftBigger(StringNum(5), "-4", allTestsPass);
    CheckNumLeftBigger(StringNum(1), "0", allTestsPass);


    // cout << "True Side >=" << endl;
    // cout << (str1B >= str1) << " " << (str1B >= str2) << " " << (str4 >= str3) << " " << (str6 >= str5) << endl;
    // cout << (str4 >= str1) << " " << (str4 >= str2) << " " << (str4 >= str3) << " " << (str4 >= str5) << endl;
    // cout << (str4 >= str4) << " " << (str2 >= str2) << " " << (str3 >= str3) << " " << (str5 >= str5) << endl;
    // cout << "False Side >=" << endl;
    // cout << (str1 >= str1B) << " " << (str2 >= str1B) << " " << (str3 >= str4) << " " << (str5 >= str6) << endl;
    // cout << (str1 >= str4) << " " << (str2 >= str4) << " " << (str3 >= str4) << " " << (str5 >= str4) << endl;
    //
    // cout << "True Side >" << endl;
    // cout << (str1B > str1) << " " << (str1B > str2) << " " << (str4 > str3) << " " << (str6 > str5) << endl;
    // cout << (str4 > str1) << " " << (str4 > str2) << " " << (str4 > str3) << " " << (str4 > str5) << endl;
    // cout << "False Side >" << endl;
    // cout << (str4 > str4) << " " << (str2 > str2) << " " << (str3 > str3) << " " << (str5 > str5) << endl;
    // cout << (str1 > str1B) << " " << (str2 > str1B) << " " << (str3 > str4) << " " << (str5 > str6) << endl;
    // cout << (str1 > str4) << " " << (str2 > str4) << " " << (str3 > str4) << " " << (str5 > str4) << endl;

    StringNum str8 = str1;
    str8 = str2 + str1;
    str8 = str8 - str2;
    CheckNum(str8, str1, allTestsPass);

    str8 = str3 + str4;
    str8 = str8 - str4;
    CheckNum(str8, str3, allTestsPass);

    str8 = str5 + str6;
    str8 = str8 - str6;
    CheckNum(str8, str5, allTestsPass);

    StringNum a2 = 0;
    StringNum b2 = 1;
    StringNum temp2 = 1;
    int a1 = 0;
    int b1 = 1;
    int temp1;
    for (int i = 1; i <= 9; i++) {
        temp2 = a2 + b2;
        a2 = b2;
        b2 = temp2;
        temp1 = a1 + b1;
        a1 = b1;
        b1 = temp1;
        CheckNum(temp1, temp2, allTestsPass);
    }

    StringNum a3 = 100;
    int y = 100;
    for (int i = 1; i <= 150; ++i) {
        a3 = a3 - i;
        y = y - i;
        CheckNum(a3, y, allTestsPass);
    }

    StringNum a4 = 80;
    long x = 80;
    for (int i = 1; i <= 6; ++i) {
        a4 = a4 * (StringNum(-1) - StringNum(i));
        x = x * (-1 - i);
        CheckNum(a4, x, allTestsPass);
    }

    if (str1.hasDecimal()) {
        allTestsPass = false;
        cout << "hasDecimal failed with no decimal" << endl;
    }
    if (!str1D.hasDecimal()) {
        allTestsPass = false;
        cout << "hasDecimal failed with decimal" << endl;
    }

    if (StringNum(3).getLength() != 3) {
        allTestsPass = false;
        cout << "getLength failed with no decimal" << endl;
    }
    if (str1.getLength() != 4) {
        allTestsPass = false;
        cout << "getLength failed with decimal" << endl;
    }
    if (str2.getLength() != 9) {
        allTestsPass = false;
        cout << "getLength failed with large number" << endl;
    }
    if (str1.getNumber() != "33.0") {
        allTestsPass = false;
        cout << "getNumber failed with 33.0" << endl;
    }
    if (str1.getNumber() != "33.0") {
        allTestsPass = false;
        cout << "getNumber failed with 33.0" << endl;
    }
    if (str7.getNumber() != "-555.77") {
        allTestsPass = false;
        cout << "getNumber failed with -555.77" << endl;
    }

    if (allTestsPass) {
        cout << "All tests passed" << endl;
    }
    else {
        cout << "At least one test failed" << endl;
    }
    return 0;
}