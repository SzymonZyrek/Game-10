//
//  CPPQueue.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__CPPQueue__
#define __OpenGLTutorial__CPPQueue__

#include <stdio.h>
#include <vector>
#include <iostream>
#include "TestResult.h"

template <class T> class CPPQueue {
public:
    std::vector<T> _inner_vector;
    CPPQueue(int size)
    {
        this->_size = size;
        _head = 0;
        _tail = 0;
        _empty = true;
        _full = false;
    }
    int getHead()
    {
        return _head;
    }
    int getTail()
    {
        return _tail;
    }
    void setSize(int theSize)
    {
        this->_size = theSize;
    }
    int getSize()
    {
        return _size;
    }
    bool isEmpty()
    {
        return _empty;
    }
    bool isFull()
    {
        return _full;
    }
    TestResult enqueue(T elem)
    {
        if (!_full)
        {
            std::vector<int>::iterator iter = _inner_vector.begin() + _tail;
            _inner_vector.insert(iter, elem);
            _empty = false;
        }else{
            return TestResult("Queue is full! Cant add more elements");
        }
        _tail = (_tail+1)%_size;
        if (_tail == _head)
        {
            _full = true;
        }
        return TestResult();
    }
    T dequeue()
    {
        if (_empty)
        {
            return 0;
        }
        T result = _inner_vector[_head];
        _full = false;
        _head = (_head + 1)%_size;
        if (_head == _tail)
        {
            _empty = true;
        }
        return result;
    }
private:
    int _size;
    int _head;
    int _tail;
    bool _empty;
    bool _full;
};


#endif /* defined(__OpenGLTutorial__CPPQueue__) */
