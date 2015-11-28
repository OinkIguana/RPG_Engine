#pragma once
#include <functional>
#include <thread>
#include "config.h"
#include <cmath>

namespace util {
    template<typename T>
    inline void quicksort(T * part, const unsigned int& len, std::function<bool(T, T)> pred) {
        if (len <= 1) { return; }
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
        std::thread r(quicksort<T>, right, ir, pred);
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
    inline void mergesort(T * part, const unsigned int& len, std::function<bool(T, T)> pred) {
        if (len <= 1) { return; }
        const unsigned int ml = (unsigned int) std::floor(len / 2.0), mr = (unsigned int) std::ceil(len / 2.0);
        T * left = new T[ml];
        for (unsigned int i = 0; i < ml; i++) {
            left[i] = part[i];
        }
        T * right = new T[mr];
        for (unsigned int i = 0; i < mr; i++) {
            right[i] = part[ml + i];
        }
        std::thread l(mergesort<T>, left, ml, pred);
        std::thread r(mergesort<T>, right, mr, pred);
        l.join();
        r.join();
        unsigned int il = 0, ir = 0;
        for (unsigned int i = 0; i < len; i++) {
            if (il < ml && (ir == mr || pred(left[il], right[ir]))) {
                part[i] = left[il++];
            } else {
                part[i] = right[ir++];
            }
        }
        delete[] left;
        delete[] right;
    }
}