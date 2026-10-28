// 常见的特殊矩阵的公式化描述（数组）
#include <iostream>
using namespace std;

class OutOfBounds
{
};
class MustBeZero
{
};

// 父类模板类：矩阵
/*begin————————————————————————————————————————————————————————————————————————————————*/
template <class T>
class Matrix
{
protected:
    int size; // 矩阵维度
    T *p;     // 使用一维数组储存矩阵的“关键元素”————数据结构的关键（公式化描述）

public:
    Matrix(int n) // 构造函数
    {
        size = n;
        p = NULL;
    }
    ~Matrix() // 析构函数
    {
        delete[] p;
    }
    virtual void Store(T x, int i, int j) = 0; // 映射储存函数

    /*映射规则的关键；
    1.位置数据f(i,j)为什么值时矩阵的元素一定为零，这一部分元素不需要真正储存，检索时直接输出0[这种方法可行的前提是规则已知]；
    2.剩余的可能有值的元素必须储存，关键在于怎么映射：即如何将二维的位置数据f(i,j)映射到一维数据上。
    ·常见的映射方式有行映射、列映射、斜对角映射。 */

    virtual T Retrieve(int i, int j) const = 0; // 检索函数

    /*使用const修饰函数是很良好的代码习惯：
    ·const既是访问权限上的约束，也是函数行为上的承诺。
    ·函数行为上的承诺：函数内不得改变this*所指的对象（当前对象的普通成员必须保证常量）；
    ·访问权限上的约束：被const合法修饰的函数允许被常引用。*/
};
/*end————————————————————————————————————————————————————————————————————————————————*/

// 子类1：对角矩阵
/*begin————————————————————————————————————————————————————————————————————————————————*/
template <class T>
class DiagonalMatrix : public Matrix<T>
{
public:
    DiagonalMatrix(int n) : Matrix<T>(n)
    {
        this->p = new T[n]{}; // 明确初始化：将数组元素初始化为0
    }
    void Store(T x, int i, int j) override;
    T Retrieve(int i, int j) const override;
};

template <class T>
void DiagonalMatrix<T>::Store(T x, int i, int j)
{
    if (i < 1 || j < 1 || i > this->size || j > this->size)
    {
        throw OutOfBounds();
    }
    if (i != j && x != 0)
    {
        throw MustBeZero();
    }
    else if (i == j) // 有效元素位置
    {
        this->p[i - 1] = x; // 斜对角映射
    }
}

template <class T>
T DiagonalMatrix<T>::Retrieve(int i, int j) const
{
    if (i < 1 || j < 1 || i > this->size || j > this->size)
    {
        throw OutOfBounds();
    }
    if (i != j)
    {
        return 0;
    }
    else
    {
        return this->p[i - 1];
    }
}
/*end————————————————————————————————————————————————————————————————————————————————*/

// 子类2：三对角矩阵
/*begin————————————————————————————————————————————————————————————————————————————————*/
template <class T>
class TridiagonalMatrix : public Matrix<T>
{
public:
    TridiagonalMatrix(int n) : Matrix<T>(n)
    {
        this->p = new T[3 * n - 2]{};
    }
    void Store(T x, int i, int j) override;
    T Retrieve(int i, int j) const override;
};

template <class T>
void TridiagonalMatrix<T>::Store(T x, int i, int j)
{
    if (i < 1 || j < 1 || i > this->size || j > this->size)
    {
        throw OutOfBounds();
    }
    switch (i - j) // 利用行与列的数学关系精巧实现斜对角映射
    {
    case 1:
        this->p[i - 2] = x;
        break;
    case 0:
        this->p[this->size + i - 2] = x;
        break;
    case -1:
        this->p[2 * this->size + i - 2] = x;
        break;
    default:
        if (x != 0)
            throw MustBeZero();
    }
}

template <class T>
T TridiagonalMatrix<T>::Retrieve(int i, int j) const
{
    if (i < 1 || j < 1 || i > this->size || j > this->size)
    {
        throw OutOfBounds();
    }
    switch (i - j)
    {
    case 1:
        return this->p[i - 2];
    case 2:
        return this->p[this->size + i - 2];
    case 3:
        return this->p[2 * this->size + i - 2];
    default:
        return 0;
    }
}
/*end————————————————————————————————————————————————————————————————————————————————*/

// 子类3：三角矩阵
/*begin————————————————————————————————————————————————————————————————————————————————*/
template <class T>
class LowerMatrix : public Matrix<T>
{
public:
    LowerMatrix(int n) : Matrix<T>(n)
    {
        this->p = new T[n * (n + 1) / 2]{};
    }
    void Store(T x, int i, int j) override;
    T Retrieve(int i, int j) const override;
};

template <class T>
void LowerMatrix<T>::Store(T x, int i, int j)
{
    if (i < 1 || j < 1 || i > this->size || j > this->size)
    {
        throw OutOfBounds();
    }
    if (i < j && x != 0)
    {
        throw MustBeZero();
    }
    else if (i >= j) // 有效元素位置
    {
        this->p[i * (i - 1) / 2 + j - 1] = x; // 行映射
    }
    /*UpperMatrix改成j>=i，采用列映射即可*/
}

template <class T>
T LowerMatrix<T>::Retrieve(int i, int j) const
{
    if (i < 1 || j < 1 || i > this->size || j > this->size)
    {
        throw OutOfBounds();
    }
    if (i >= j)
    {
        return this->p[i * (i - 1) / 2 + j - 1];
    }
    else
    {
        return 0;
    }
}
/*end————————————————————————————————————————————————————————————————————————————————*/
