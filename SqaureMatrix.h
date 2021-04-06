#pragma once
#include <iostream>
using namespace std;

template<typename p>
class SquareMatrix
{
public:
    SquareMatrix();
    ~SquareMatrix();
    SquareMatrix(SquareMatrix& u);
    SquareMatrix& operator = (const SquareMatrix& u);
    SquareMatrix(SquareMatrix&& u);
    SquareMatrix& operator = (const SquareMatrix&& u);
    void resize(int newSize);
    bool operator == (const SquareMatrix& u);
    SquareMatrix operator + (const SquareMatrix& u);
    p& at(int row, int column);
    int size();
private:
    p** _ptr;
    int size;
};


template <typename p>
SquareMatrix<p>::SquareMatrix() : _ptr(nullptr), size(0)
{
 
}

template <typename p>
SquareMatrix<p>::~SquareMatrix()
{
    if (_ptr != nullptr)
    {
        for (int i{0}; i < size; i++)
        {
            delete[] _ptr[i];
        }
        delete[] _ptr;
    }
    
}

template <typename p>
SquareMatrix<p>::SquareMatrix(SquareMatrix& u)
{
    size = u.size;
    //Assign Memory
    _ptr = new p* [size];
    for (int i{0}; i < size;i++)
    {
        _ptr[i] = new p[size];
    }

    //Copy the contents
    for (int i{0}; i < size; i++)
    {
        for (int j{0}; j < size; j++)
        {
            _ptr[i][j] = u._ptr[i][j];
        }
    }
}

template <typename p>
SquareMatrix<p>& SquareMatrix<p>::operator=(const SquareMatrix& u)
{
    if (this != &u)
    {
        //delete the existing memory
        if (_ptr != nullptr)
        {
            for (int i{0}; i < size; i++)
            {
                delete[] _ptr[i];
            }
            delete[] _ptr;
        }

        size = u.size;
        //Assign Memory
        _ptr = new p * [size];
        for (int i{0}; i < size; i++)
        {
            _ptr[i] = new p[size];
        }

        //Copy the contents
        for (int i{0}; i < size; i++)
        {
            for (int j{0}; j < size; j++)
            {
                _ptr[i][j] = u._ptr[i][j];
            }
        }
    }
    return *this;
}

template <typename p>
SquareMatrix<p>::SquareMatrix(SquareMatrix&& u)
{
    //transfer the ownership to the current object instance
    size = u.size;
    _ptr = u._ptr;
    u._ptr = nullptr;

}

template <typename p>
SquareMatrix<p>& SquareMatrix<p>::operator=(const SquareMatrix&& u)
{
    if (this != &u)
    {
        //transfer the ownership to the current object instance
        size = u.size;
        _ptr = u._ptr;
        u._ptr = nullptr;
    }
    return *this;
}

template <typename p>
void SquareMatrix<p>::resize(int newSize)
{
    p** tmp = new p * [new_Size];
    for (int i{0}; i < new_Size; i++)
    {
        tmp[i] = new p[new_Size];
    }

    //Copy the contents
    for (int i{0}; i < size; i++)
    {
        for (int j{0}; j < size; j++)
        {
            tmp[i][j] = _ptr[i][j];
        }
    }

    //delete the old memory
    if (_ptr != nullptr)
    {
        for (int i{0}; i < size; i++)
        {
            delete[] _ptr[i];
        }
        delete[] _ptr;
    }

    //assign the new memory
    rawptr = tmp;
    dim = newSize;
}

template <typename p>
bool SquareMatrix<p>::operator==(const SquareMatrix& u) 
{
    for (int i{0}; i < size; i++)
    {
        for (int j{0}; j < size; j++)
        {
            if (_ptr[i][j] != u._ptr[i][j])
            {
                return -1;
            }
        }
    }

    return 0;
}

template <typename p>
SquareMatrix<p> SquareMatrix<p>::operator+(const SquareMatrix& u)
{
    u** tmp = new u * [size];
    for (int i{0}; i < size; i++)
    {
        tmp[i] = new T[size];
    }

    for (int i{0}; i <size; i++)
    {
        for (int j{0}; j < size; j++)
        {
            tmp[i][j] = _ptr[i][j] + u._ptr[i][j];
        }
    }

    return tmp;
}

template <typename p>
p& SquareMatrix<p> :: at(int row, int column)
{
    return _ptr[row][column];
}

template <typename p>
p& SquareMatrix<p> ::  size()
{
    return size;
}

