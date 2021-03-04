// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef UNIC_PTR_H_
#define UNIC_PTR_H_

#include "checkML.h"

template<typename T> 
class unic_ptr
{
public:
    explicit unic_ptr(T *p) :m_ptr(p) {}
    unic_ptr() :m_ptr(NULL) {}
    //el destructor
    ~unic_ptr() { delete m_ptr; }    
    //no es copiable
    unic_ptr(const unic_ptr &o) = delete;
    unic_ptr &operator=(const unic_ptr &o) = delete;
    //pero sí es movible
    unic_ptr(unic_ptr &&o) 
    {
        m_ptr = o.m_ptr;
        o.m_ptr = NULL;
    }
    unic_ptr &operator=(unic_ptr &&o)
    {
        delete m_ptr;
        m_ptr = o.m_ptr;
        o.m_ptr = NULL;
    }
    //otros
    T *get() const { return m_ptr; }
    void reset(T *p)
    {
        T *t = m_ptr;
        m_ptr = p;
        delete t;
    }
    T *release()
    {
        T *t = m_ptr;
        m_ptr = NULL;
        return t;
    }
    T *operator->() const { return m_ptr; }
    T &operator*() const { return *m_ptr; }
private:
    T *m_ptr;
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif