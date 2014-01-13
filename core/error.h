#pragma once
#include <iosfwd>
#include <vector>
#include <axe/core/typedefs.h>

namespace axe {
    struct error {
        
        using printerfunc = void (*)(const char *str, size len);
        using errorfunc   = void (*)(int code, printerfunc);
        
        // code 00: addr is const char*
        // code 01: code is errno error
        // code 10: addr is function ponter to int (*)(int, printfunc)
        enum ErrType {
            NoErr     = 0,
            StringErr = 0,
            FuncErr   = 1,
            ErrNo     = 2,
            GAIErr    = 3
        } ;
        
        union {
            const char * charp;
            errorfunc   funcp;
            struct {
                int64  code      : 48;
                uint   type      : 2;
                uint   extra     : 14;
            };
        };
        
        
        constexpr error() : charp(0) {}
        constexpr error(int n) : code(n), type(ErrNo), extra(0) {}
        constexpr error(ErrType type, int code=0, uint extra=0) : 
                code(code), type(type), extra(extra) {}
        constexpr error(const char *str) : charp(str) { }
        constexpr error(std::nullptr_t) : code(0), type(0), extra(0) {}
        error(errorfunc f) : funcp(f) {
            type = FuncErr;
        }
        
        constexpr explicit operator bool () const    { return charp != 0; }
        constexpr bool operator ==   (error rhs) { return charp == rhs.charp; }
        
        str string(Allocator&) const;

    };
    std::ostream& operator<< (std::ostream& o, error err);

    struct esize {
        axe::size  size;
        error err;
    } ;

    constexpr error OK(error::NoErr);

    template <typename T>
    struct witherror {
        T item;
        error err;
        
        witherror(T&& t) : item(t), err(OK) {}
        witherror(T const& t) : item(t), err(OK) {}
        witherror(error e) : err(e) {}
        witherror(T&& t, error e) : item(t), err(e) {}
        witherror(T const& t, error e) : item(t), err(e) {}
        
        operator T () { return item; }
    };

    struct errorparam {
        error *err;
        
        errorparam()         : err(nullptr) {}
        errorparam(error& e) : err(&e)      {}
        
        void operator = (error e) {
            if (err) {
                *err = e;
            } else {
                throw e;
            }
        }
        
        operator error () {
            if (err) {
                return *err;
            } else {
                return error();
            }
        }
        
        explicit operator bool () {
            if (err) {
                return (bool) *err;
            } else {
                return false;
            }
        }
        
        errorparam& operator = (errorparam const&) = delete;
        str string(Allocator&) const;
    } ;
    
    struct Exception {
        std::vector<void*> backtrace;
        std::string        msg;
    } ;
    
    void raise(str msg);
    void raise(int errno_);
}