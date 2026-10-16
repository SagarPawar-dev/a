
#include <iostream>
#include <string>
using namespace std;

string fractionToBinary(double fraction)
{
    string result = "";

    while (fraction > 0 && result.length() < 64)
    {
        fraction = fraction * 2;

        if (fraction >= 1)
        {
            result = result + "1";
            fraction = fraction - 1;
        }
        else
        {
            result = result + "0";
        }
    }

    return result;
}

string integerToBinary(long n)
{
    if (n == 0)
        return "0";

    string result = "";

    while (n > 0)
    {
        result = char((n % 2) + '0') + result;
        n = n / 2;
    }

    return result;
}

string binaryToHex(string binary)
{
    string hex = "";

    while (binary.length() % 4 != 0)
    {
        binary = "0" + binary;
    }

    for (int i = 0; i < binary.length(); i = i + 4)
    {
        int value = 0;

        value = value + (binary[i] - '0') * 8;
        value = value + (binary[i + 1] - '0') * 4;
        value = value + (binary[i + 2] - '0') * 2;
        value = value + (binary[i + 3] - '0') * 1;

        if (value < 10)
        {
            hex = hex + char(value + '0');
        }
        else
        {
            hex = hex + char(value - 10 + 'A');
        }
    }

    return hex;
}

void convert(double num, int exponentBits, int mantissaBits,
             int bias, bool extended)
{
    int sign = 0;

    if (num < 0)
    {
        sign = 1;
        num = -num;
    }

    long integerPart = (long)num;
    double fractionPart = num - integerPart;

    string integerBinary = integerToBinary(integerPart);
    string fractionBinary = fractionToBinary(fractionPart);

    int exponent;

    if (integerPart != 0)
    {
        exponent = integerBinary.length() - 1;
    }
    else
    {
        int firstOne = -1;

        for (int i = 0; i < fractionBinary.length(); i++)
        {
            if (fractionBinary[i] == '1')
            {
                firstOne = i;
                break;
            }
        }

        exponent = -(firstOne + 1);
    }

    int biasedExponent = exponent + bias;

    string exponentBinary = "";

    for (int i = 0; i < exponentBits; i++)
    {
        exponentBinary = char((biasedExponent % 2) + '0') + exponentBinary;
        biasedExponent = biasedExponent / 2;
    }

    string mantissa = "";

    if (integerPart != 0)
    {
        for (int i = 1; i < integerBinary.length(); i++)
        {
            mantissa = mantissa + integerBinary[i];
        }

        mantissa = mantissa + fractionBinary;
    }
    else
    {
        int firstOne = -1;

        for (int i = 0; i < fractionBinary.length(); i++)
        {
            if (fractionBinary[i] == '1')
            {
                firstOne = i;
                break;
            }
        }

        if (firstOne != -1)
        {
            for (int i = firstOne + 1; i < fractionBinary.length(); i++)
            {
                mantissa = mantissa + fractionBinary[i];
            }
        }
    }

    if (extended)
    {
        mantissa = "1" + mantissa;

        while (mantissa.length() < 64)
        {
            mantissa = mantissa + "0";
        }

        if (mantissa.length() > 64)
        {
            mantissa = mantissa.substr(0, 64);
        }
    }
    else
    {
        while (mantissa.length() < mantissaBits)
        {
            mantissa = mantissa + "0";
        }

        if (mantissa.length() > mantissaBits)
        {
            mantissa = mantissa.substr(0, mantissaBits);
        }
    }

    cout << endl;
    cout << "binary output = ";

    string result = char(sign + '0') + exponentBinary + mantissa;

    cout << result << endl;

    cout << "Hex equivalent output = " << binaryToHex(result) << endl;
}

int main()
{
    double num;

    cout << "Enter decimal number: ";
    cin >> num;

    double positiveNum = num;

    if (positiveNum < 0)
    {
        positiveNum = -positiveNum;
    }

    int integer = (int)positiveNum;
    double frac = positiveNum - integer;

    string binary = integerToBinary(integer);

    if (frac > 0)
    {
        binary = binary + "." + fractionToBinary(frac);
    }

    cout << "Binary output=" << binary << endl;

    cout << "Select F.P Format " << endl;
    cout << " 1. Single Precision" << endl;
    cout << " 2. Double Precision" << endl;
    cout << " 3. Extended Precision" << endl;

    int choice;

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        convert(num, 8, 23, 127, false);
        break;

    case 2:
        convert(num, 11, 52, 1023, false);
        break;

    case 3:
        convert(num, 15, 64, 16383, true);
        break;

    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}