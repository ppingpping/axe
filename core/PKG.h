#import "typedefs.h"
#import "assert.h"
#import "alloc.h"
#import "str.h"
#import "error.h"
#import "adt.h"
#import "func.h"

namespace axe {

    template <typename Func>
    struct Deferred {
        Func func;
        
        ~Deferred() {
            func();
        }
    };

    template <typename Func>
    Deferred<Func> defer(Func&& func) {
        return Deferred<Func>{std::forward<Func>(func)};
    }

//     struct Writer {
//         template <typename T>
//         esize operator () (T&& thing) {
//             return write(stdout, std::forward<T>(thing));
//         }
//     } ;
// 
//     inline esize write(Writer& writer, str s) {
//         return writer(s);
//     }
    
    template <typename T, size N>
    size len(T (&)[N]) {
        return N;
    }
    
    template <typename T>
    size len(T const& t) {
        return t.size();
    }
    
    template <typename T, typename U>
    void memcopy(T& t, U const& u) {
        static_assert(sizeof(t) == sizeof(u), "size mismatch");
        memcpy(&t, &u, sizeof(t));
    }
}