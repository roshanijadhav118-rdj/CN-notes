#include <iostream>
using namespace std;

int main()
{
    char a[35], b[25];
    int n, i, j, count = 0;

    cout << "Enter stuffed frame length: ";
    cin >> n;

    cout << "Enter stuffed frame: ";
    cin >> a;

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
            i++;        // Skip the stuffed 0
            count = 0;
        }

        i++;
        j++;
    }

    b[j] = '\0';

    cout << "Original Frame: " << b << endl;

    return 0;
}
