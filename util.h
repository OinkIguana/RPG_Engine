#pragma once
#include <functional>
#include <thread>
#include "config.h"

namespace util {
    template<typename T>
    inline void quicksort(T * part, const unsigned int& len, std::function<bool(T, T)> pred) {
        if (len <= 1) return;
        T * left = new T[len - 1];
        T * right = new T[len - 1];
        unsigned int il = 0, ir = 0;
        T pivot = part[len - 1];
        for (unsigned int i = 0; i < len - 1; i++) {
            if (pred(part[i], pivot)) {
                left[il++] = part[i];
            } else {
                right[ir++] = part[i];
            }
        }
        std::thread l(quicksort<T>, left, il, pred);
        std::thread r(quicksort<T>, left, il, pred);
        l.join();
        r.join();
        for (unsigned int i = 0; i < len; i++) {
            if (i < il) {
                part[i] = left[i];
            } else if (i == il) {
                part[i] = pivot;
            } else {
                part[i] = right[i - il - 1];
            }
        }
        delete[] left;
        delete[] right;
    }

    template<typename T>
    inline void mergesort(T * part, unsigned int len) {
        
    }
}