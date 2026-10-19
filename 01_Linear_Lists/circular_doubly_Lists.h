#pragma once
#include <iostream>
using namespace std;

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

template <class T>
class cdchain
{
public:
    node<T> *head;
    int count;
    cdchain()
    {
        count = 0;
        head = new node<T>(T{});
        head->next = head;
        head->prev = head;
    }
    void Insert(T x);
    T *Get();
};

template <class T>
void cdchain<T>::Insert(T x)
{
    node<T> *temp = new node(x);
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
    T *s = new T[this->count];
    node<T> *curr = head->next;
    for (int i = 0; i < this->count; i++)
    {
        s[i] = curr->element;
        curr = curr->next;
    }
    return s;
}

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