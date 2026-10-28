#include <iostream>
#include "Matrices.h"

int main()
{
    TridiagonalMatrix<int> m(5); // 一个简单测试案例，并不算全面，可以后续按需新增补充
    try
    {
        m.Store(28, 3, 3);
        cout << "储存成功！" << endl;
    }
    catch (const OutOfBounds &)
    {
        cout << "下标越界！" << endl;
    }
    catch (const MustBeZero &)
    {
        cout << "此处输入必须为零！" << endl;
    }
    try
    {
        cout << m.Retrieve(4, 3) << endl;
    }
    catch (const OutOfBounds &)
    {
        cout << "下标越界！" << endl;
    }
}