
#include <iostream>
#include <string>
using namespace std;

// Decimal to Binary
string decimalToBinary(int num, int base)
{
    if (num == 0)
        return "0";

    string bits = "";

    while (num > 0)
    {
        int rem = num % base;
        bits = char(rem + '0') + bits;
        num = num / base;
    }

    return bits;
}

// Binary to Decimal (unsigned magnitude)
long long binaryToDecimal(string bits)
{
    long long sum = 0;

    for (int i = 0; i < bits.length(); i++)
    {
        sum = sum * 2 + (bits[i] - '0');
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
            result += '1';
        else
            result += '0';
    }

    while (one.length() < result.length())
        one = "0" + one;

    int carry = 0;
    string temp = result;
    result = "";

    // Add 1
    for (int i = temp.length() - 1; i >= 0; i--)
    {
        int total = (temp[i] - '0') +
                    (one[i] - '0') + carry;

        result = char((total % 2) + '0') + result;
        carry = total / 2;
    }

    return result;
}

// Binary Addition (fixed width)
string addBinary(string num1, string num2)
{
    int length = num1.length();

    while (num2.length() < length)
        num2 = "0" + num2;

    int carry = 0;
    string result = "";

    for (int i = length - 1; i >= 0; i--)
    {
        int total = (num1[i] - '0') +
                    (num2[i] - '0') + carry;

        result = char((total % 2) + '0') + result;
        carry = total / 2;
    }

    return result;
}

// Arithmetic Right Shift
void rightShift(string &acc, string &multiplier, char &qMinus1)
{
    int last = acc.length() - 1;

    // Save Q0
    qMinus1 = multiplier[last];

    // Save sign bit of A
    char signBit = acc[0];

    // Shift Q right
    for (int i = last; i > 0; i--)
        multiplier[i] = multiplier[i - 1];

    // A's last bit moves into Q's first bit
    multiplier[0] = acc[last];

    // Arithmetic right shift A
    for (int i = last; i > 0; i--)
        acc[i] = acc[i - 1];

    // Preserve sign bit
    acc[0] = signBit;
}

int main()
{
    int multiplicandDecimal;
    int multiplierDecimal;

    cout << "Enter Multiplicand in decimal : ";
    cin >> multiplicandDecimal;

    cout << "Enter Multiplier in decimal : ";
    cin >> multiplierDecimal;

    // Determine required bit width, including sign
    int length = 2;

    long long maxValue =
        (multiplicandDecimal < 0
         ? -(long long)multiplicandDecimal
         : multiplicandDecimal);

    long long secondValue =
        (multiplierDecimal < 0
         ? -(long long)multiplierDecimal
         : multiplierDecimal);

    if (secondValue > maxValue)
        maxValue = secondValue;

    while (maxValue > (1LL << (length - 1)) - 1)
        length++;

    // Convert both operands to fixed-width two's complement
    auto toTwos = [&](int num)
    {
        long long value = num;
        string bits = "";

        for (int i = 0; i < length; i++)
        {
            bits = char('0' + (value & 1)) + bits;
            value >>= 1;
        }

        return bits;
    };

    string multiplicand = toTwos(multiplicandDecimal);
    string multiplier = toTwos(multiplierDecimal);

    cout << "M in Binary : " << multiplicand << endl;
    cout << "Q in Binary : " << multiplier << endl;

    string acc(length, '0');
    char qMinus1 = '0';

    string negativeM = twosComplement(multiplicand, "1");

    // Booth's Algorithm
    int count = length;

    while (count > 0)
    {
        char q0 = multiplier[length - 1];

        if (q0 == '1' && qMinus1 == '0')
            acc = addBinary(acc, negativeM);
        else if (q0 == '0' && qMinus1 == '1')
            acc = addBinary(acc, multiplicand);

        rightShift(acc, multiplier, qMinus1);
        count--;
    }

    // Final product is a signed 2's-complement number
    string product = acc + multiplier;

    cout << "Result (product) in binary = "
         << product << endl;

    // Convert signed two's-complement product to decimal
    long long decimalResult;

    if (product[0] == '1')
    {
        string magnitude = twosComplement(product, "1");
        decimalResult = -binaryToDecimal(magnitude);
    }
    else
    {
        decimalResult = binaryToDecimal(product);
    }

    cout << "Result in decimal = "
         << decimalResult << endl;

    return 0;
}