#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char a[25], b[35];
    int n, i, j, count = 0;

    cout << "Enter frame length: ";
    cin >> n;

    cout << "Enter frame (0 & 1): ";
    cin >> a;

    if (strlen(a) != n)
    {
        cout << "Frame length does not match!";
        return 0;
    }

    i = 0;
    j = 0;

    while (i < n)
    {
        b[j] = a[i];

        if (a[i] == '1')
            count++;
        else
            count = 0;

        if (count == 5)
        {
            j++;
            b[j] = '0';   // Stuff a 0 after five consecutive 1s
            count = 0;
        }

        i++;
        j++;
    }

    b[j] = '\0';

    cout << "Frame after Bit Stuffing: " << b << endl;

    return 0;
}
