#pragma once
#include <iostream>
using namespace std;

// 双向节点类
template <class T>
class node
{
public:
    T element;
    node<T> *next;
    node<T> *prev;
    node(T x)
    {
        element = x;
        next = NULL;
        prev = NULL;
    }
};

// 带头节点的双向循环链表类
template <class T>
class cdchain
{
public:
    node<T> *head;
    int count;
    cdchain()
    {
        count = 0;
        head = new node<T>(T{}); // 初始化链表时在头节点里面的元素填充空
        head->next = head;
        head->prev = head;
    }
    void Insert(T x); // 插入函数
    T *Get();         // 获得链表里面所有节点里面的元素
};

template <class T>
void cdchain<T>::Insert(T x) // 插入方式为尾插（无序插入）
{
    node<T> *temp = new node<T>(x);
    if (head->next == head)
    {
        temp->next = head;
        temp->prev = head;
        head->next = temp;
        head->prev = temp;
        count++;
    }
    else
    {
        temp->next = head;
        temp->prev = head->prev;
        head->prev->next = temp;
        head->prev = temp;
        count++;
    }
}

template <class T>
T *cdchain<T>::Get()
{
    T *s = new T[this->count]; // 利用数组实现元素获取
    node<T> *curr = head->next;
    for (int i = 0; i < this->count; i++)
    {
        s[i] = curr->element;
        curr = curr->next;
    }
    return s;
}

// 核心功能函数
// 功能：将c链表里面索引为奇数的节点元素存入链表a，其余节点元素存入链表b
// 实现：复制链表元素存入新创建的链表，并没有复用指针
template <class T>
void split(cdchain<T> c, cdchain<T> &a, cdchain<T> &b)
{
    T *p = c.Get();
    int i = 0;
    while (i < c.count)
    {
        if (i % 2 == 1)
        {
            a.Insert(p[i]);
        }
        else
        {
            b.Insert(p[i]);
        }
        i = i + 1;
    }
    delete[] p;
}