#include <iostream>
using namespace std;

bool powercheck(float num)
{
    int i = 1;

    while (i <= num)
    {
        if (i == num)
            return true;

        i = i * 2;
    }

    return false;
}

int main()
{
    cout << "Select no. of levels in hierarchy" << endl;
    cout << "1 - 2 Level" << endl;
    cout << "2 - 3 Level" << endl;

    int choice;
    cout << "Choice = ";
    cin >> choice;

    float s[3], c[3], ta[3], h[3];

    int n = choice + 1;
    int i = 1;

    while (i <= n)
    {
        cout << "For " << i << " level, input -" << endl;

        float size;
        cout << "Size : ";
        cin >> size;

        if (powercheck(size))
            s[i - 1] = size;
        else
        {
            cout << "Number Is Invalid" << endl;
            return 0;
        }

        cout << "Cost/bit : ";
        cin >> c[i - 1];

        cout << "Access Time : ";
        cin >> ta[i - 1];

        if (i == n)
            h[i - 1] = 1;
        else
        {
            cout << "Hit rate/ratio : ";
            cin >> h[i - 1];
        }

        cout << endl;
        i++;
    }

    i = 1;
    float a = 0;
    float b = 0;

    while (i <= n)
    {
        a = a + s[i - 1] * c[i - 1];
        b = b + s[i - 1];
        i++;
    }

    float e = a / b;

    float avg;

    if (choice == 1)
    {
        avg = h[0] * ta[0] + (1 - h[0]) * ta[1];
    }
    else
    {
        avg = h[0] * ta[0]
            + (1 - h[0]) * h[1] * ta[1]
            + (1 - h[0]) * (1 - h[1]) * ta[2];
    }

    cout << "Average cost/bit(c) = " << e << endl;
    cout << "Average access time(ta) = " << avg << endl;

    return 0;
}