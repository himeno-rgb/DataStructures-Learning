#include <iostream>
#include "circular_doubly_Lists.h"
using namespace std;

template <class T>
void out(cdchain<T> &c)
{
    node<T> *curr = c.head->next;
    if (c.head->next == c.head)
    {
        cout << "[]";
    }
    else
    {
        cout << "[";
        while (curr != c.head)
        {
            if (curr != c.head->next)
                cout << ", ";
            cout << curr->element;
            curr = curr->next;
        }
        cout << "]";
    }
}

void test(int x[], int n)
{
    cdchain<int> c;
    cdchain<int> a;
    cdchain<int> b;
    for (int i = 0; i < n; i++)
    {
        c.Insert(x[i]);
    }
    split<int>(c, a, b);
    cout << "c = ";
    out(c);
    cout << " -> a = ";
    out(a);
    cout << ", b = ";
    out(b);
    cout << endl;
}

int main()
{
    int x1[1] = {};
    int x2[] = {7};
    int x3[] = {1, 2};
    int x4[] = {1, 2, 3, 4, 5};
    int x5[] = {10, 20, 30, 40};
    int x6[] = {-1, -1, 0, 7};
    test(x1, 0);
    test(x2, 1);
    test(x3, 2);
    test(x4, 5);
    test(x5, 4);
    test(x6, 4);
    return 0;
}