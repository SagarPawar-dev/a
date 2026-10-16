#include <bits/stdc++.h>

using namespace std;

// Convert decimal to Binary

string toBinary(int num, int base)

{

string bits = "";



while (num > 0)

{

    int rem = num % base;

    bits = char(rem + '0') + bits;

    num = num / base;

}



return bits;

}

// Convert Binary into decimal

int toDecimal(string bits)

{

int n = bits.length();

int sum = 0;



for (int i = 0; i < n; i++)

{

    int value = (bits[n - 1 - i] - '0') * pow(2, i);

    sum = sum + value;

}



return sum;

}

// 2's complement

string twosComp(string num, string one)

{

string comp = "";



for (int i = 0; i < num.length(); i++)

{

    if (num[i] == '0')

        comp = comp + '1';

    else

        comp = comp + '0';

}



int n;



if (comp.length() > one.length())

    n = comp.length();

else

    n = one.length();



while (comp.length() < n)

    comp = "0" + comp;



while (one.length() < n)

    one = "0" + one;



int carry = 0;

string result = "";



for (int i = n - 1; i >= 0; i--)

{

    int sum = (comp[i] - '0') + (one[i] - '0') + carry;



    result = char((sum % 2) + '0') + result;

    carry = sum / 2;

}



if (carry)

    result = "1" + result;



return result;

}

// Addition of binary numbers

string addBinary(string num1, string num2)

{

int n;



if (num1.length() > num2.length())

    n = num1.length();

else

    n = num2.length();



while (num1.length() < n)

    num1 = "0" + num1;



while (num2.length() < n)

    num2 = "0" + num2;



int carry = 0;

string result = "";



for (int i = n - 1; i >= 0; i--)

{

    int sum = (num1[i] - '0') + (num2[i] - '0') + carry;



    result = char((sum % 2) + '0') + result;

    carry = sum / 2;

}



return result;

}

// Left shift A and Q

void shiftLeft(string &rem, string &quot)

{

int n = rem.length() - 1;



for (int i = 0; i < n; i++)

    rem[i] = rem[i + 1];



rem[n] = quot[0];



for (int i = 0; i < n; i++)

    quot[i] = quot[i + 1];



quot[n] = '0';

}

int main()

{

int dividend, divisor;



cout << "Enter dividend in decimal : ";

cin >> dividend;



cout << "Enter divisor in decimal : ";

cin >> divisor;



// Convert divisor to Binary

if (divisor < 0)

    divisor = -divisor;



string div = toBinary(divisor, 2);



// Convert dividend to Binary

if (dividend < 0)

    dividend = -dividend;



string quot = toBinary(dividend, 2);



// Make equal length

int n;



if (div.length() > quot.length())

    n = div.length();

else

    n = quot.length();



while (div.length() < n)

    div = "0" + div;



while (quot.length() < n)

    quot = "0" + quot;



cout << "Dividend in Binary : " << quot << endl;

cout << "Divisor in Binary : " << div << endl;



// Initial remainder

string rem = "";



while (rem.length() < n)

    rem = "0" + rem;



// 2's complement of divisor

string compDiv = twosComp(div, "1");



int count = n;



while (count > 0)

{

    if (rem[0] == '1')

    {

        shiftLeft(rem, quot);

        rem = addBinary(rem, div);

    }

    else

    {

        shiftLeft(rem, quot);

        rem = addBinary(rem, compDiv);

    }



    if (rem[0] == '1')

        quot[quot.length() - 1] = '0';

    else

        quot[quot.length() - 1] = '1';



    count--;

}



// Final correction

if (rem[0] == '1')

    rem = addBinary(rem, div);



cout << "Quotient in Binary = " << quot << endl;

cout << "Remainder in Binary = " << rem << endl;



cout << "Quotient in decimal = " << toDecimal(quot) << endl;

cout << "Remainder in decimal = " << toDecimal(rem) << endl;



return 0;

}