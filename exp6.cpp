
#include <iostream>
#include <string>
using namespace std;
// Decimal to Binary
string decimalToBinary(int num, int base)
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
// Binary to Decimal
int binaryToDecimal(string bits)
{
int n = bits.length();
int sum = 0;
int power = 1;
for (int i = 0; i < n; i++)
{
int value =
(bits[n - 1 - i] - '0') * power;
sum = sum + value;
power = power * 2;
}
return sum;
}
// 2's Complement
string twosComplement(string num, string one)
{
string result = "";
// 1's complement
for (int i = 0; i < num.length(); i++)
{
if (num[i] == '0')
result = result + '1';
else
result = result + '0';
}
string temp = result;
int length;
if (temp.length() > one.length())
length = temp.length();
else
length = one.length();
while (temp.length() < length)
temp = "0" + temp;
while (one.length() < length)
one = "0" + one;
int carry = 0;
result = "";
// Add 1
for (int i = length - 1; i >= 0; i--)
{
int total =
(temp[i] - '0') +
(one[i] - '0') +
carry;
result =
char((total % 2) + '0') + result;
carry = total / 2;
}
return result;
}
// Binary Addition
string addBinary(string num1, string num2)
{
int length;
if (num1.length() > num2.length())
length = num1.length();
else
length = num2.length();
while (num1.length() < length)
num1 = "0" + num1;
while (num2.length() < length)
num2 = "0" + num2;
int carry = 0;
string result = "";
for (int i = length - 1; i >= 0; i--)
{
int total =
(num1[i] - '0') +
(num2[i] - '0') +
carry;
result =
char((total % 2) + '0') + result;
carry = total / 2;
}
return result;
}
// Left Shift A and Q
void leftShift(string &acc, string &quotient)
{
int last = acc.length() - 1;
// Left shift Accumulator
for (int i = 0; i < last; i++)
{
acc[i] = acc[i + 1];
}
// First bit of Q goes into last bit of A
acc[last] = quotient[0];
// Left shift Quotient
for (int i = 0; i < last; i++)
{
quotient[i] = quotient[i + 1];
}
// New Q0 = 0
quotient[last] = '0';
}
// Main
int main()
{
int dividendDecimal;
int divisorDecimal;
cout << "Enter Dividend in decimal : ";
cin >> dividendDecimal;
cout << "Enter Divisor in decimal : ";
cin >> divisorDecimal;
string dividend;
string divisor;
// Convert Dividend
if (dividendDecimal < 0)
{
dividend =
decimalToBinary(dividendDecimal * -1, 2);
}
else
{
dividend =
decimalToBinary(dividendDecimal, 2);
}
// Convert Divisor
if (divisorDecimal < 0)
{
divisor =
decimalToBinary(divisorDecimal * -1, 2);
}
else
{
divisor =
decimalToBinary(divisorDecimal, 2);
}
// Make both numbers same length
int length;
if (dividend.length() > divisor.length())
length = dividend.length();
else
length = divisor.length();
while (dividend.length() < length)
dividend = "0" + dividend;
while (divisor.length() < length)
divisor = "0" + divisor;
cout << "Dividend in Binary : "
<< dividend << endl;
cout << "Divisor in Binary : "
<< divisor << endl;
// Initial Accumulator
string acc = string(length, '0');
// 2's complement of Divisor
string negativeDivisor =
twosComplement(divisor, "1");
// Restoring Division
int count = length;
while (count > 0)
{
// Step 1: Left shift A and Q
leftShift(acc, dividend);
// Step 2: A = A - M
acc = addBinary(acc, negativeDivisor);
// Step 3: Check sign of A
if (acc[0] == '1')
{
// Negative -> Restore A
acc = addBinary(acc, divisor);
// Q0 = 0
dividend[dividend.length() - 1] = '0';
}
else
{
// Positive -> Q0 = 1
dividend[dividend.length() - 1] = '1';
}
count--;
}
// Final Answer
string quotient = dividend;
string remainder = acc;
cout << "Quotient in Binary = "
<< quotient << endl;
cout << "Remainder in Binary = "
<< remainder << endl;
cout << "Quotient in decimal = "
<< binaryToDecimal(quotient) << endl;
cout << "Remainder in decimal = "
<< binaryToDecimal(remainder) << endl;
return 0;
}