#ifndef PRINT_THREAD_SAFE
#define PRINT_THREAD_SAFE

#include <mutex>

class PrintThreadSafe {
 public:
    template <typename... Args>
    static void print(Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx);
        (std::cout << ... << args) << '\n';
    }
    
 private:
    static std::mutex mtx;
};

#endif
