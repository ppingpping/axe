#pragma once
#include <iosfwd>
#include "typedefs.h"

struct error {
    
    using printerfunc = void (*)(const char *str, size len);
    using errorfunc   = void (*)(int code, printerfunc);
    
    // code 00: addr is const char*
    // code 01: code is errno error
    // code 10: addr is function ponter to int (*)(int, printfunc)
    
    union {
        const char * charp;
        errorfunc   funcp;
        struct {
            int64  code      : 48;
            bool   is_errno  : 1;
            bool   is_funcp  : 1;
            uint   extra     : 14;
        };
    };
    
    
    error() = default;
    constexpr error(int n) : code(n), is_errno(true), is_funcp(false), extra(0) {}
    constexpr error(int code, bool is_errno, bool is_funcp, uint extra) : 
            code(code), is_errno(is_errno), is_funcp(is_funcp), extra(extra) {}
    constexpr error(const char *str) : charp(str) { }
    error(errorfunc f) : funcp(f) {
        is_funcp = true;
    }
    
    operator bool () { return this->charp != 0; }

};
std::ostream& operator<< (std::ostream& o, error err);

constexpr error OK(0, 0, 0, 0);