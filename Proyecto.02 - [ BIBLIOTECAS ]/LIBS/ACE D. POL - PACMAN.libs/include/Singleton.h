// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "checkML.h"
#include "unic_ptr.h"

template<typename T>
class Singleton {
protected:
    Singleton() {}
public:
    Singleton<T>& operator=(const Singleton<T>& o) = delete;
    Singleton(const Singleton<T>& o) = delete;
    virtual ~Singleton() {}
    
    // instance y init como antes …
    template<typename ...Targs>
    inline static T* init(Targs &&...args) {
        //assert(instance_.get() == nullptr);
        instance_.reset(new T(std::forward<Targs>(args)...));
        return instance_.get();
    }
    inline static T* instance() {
        if (instance_.get() == nullptr) init();
        return instance_.get();
    }
    
private:
    static unic_ptr<T> instance_;
};

template<typename T>
unic_ptr<T> Singleton<T>::instance_;














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif