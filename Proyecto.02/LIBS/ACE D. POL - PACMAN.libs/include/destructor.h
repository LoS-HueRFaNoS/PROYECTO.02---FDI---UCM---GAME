// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef DESTRUCTOR_H_
#define DESTRUCTOR_H_

#include "checkML.h"

template<typename T>
class Destructor {
public:
    Destructor() : managedObj_(nullptr) {}

    virtual ~Destructor() {
        if (managedObj_ != nullptr)
            delete managedObj_;
    }
    void setObject(T* o) { managedObj_ = o; }
private:
    T* managedObj_;
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif