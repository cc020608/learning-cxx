#include "../exercise.h"
#include <iostream>
#include <cassert>
// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;
public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]{}), cached(2), capacity(capacity) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr; // 使源对象的指针为空
        other.cached = 0;      // 重置源对象的状态
        other.capacity = 0;    // 重置源对象的状态
    }
    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci& operator=(DynFibonacci &&other) noexcept {
        if (this != &other) { // 防止自赋值
            delete[] cache; // 释放当前缓存

            cache = other.cache; // 转移资源
            cached = other.cached;
            capacity = other.capacity;

            other.cache = nullptr; // 使源对象的指针为空
            other.cached = 0;      // 重置源对象的状态
            other.capacity = 0;    // 重置源对象的状态
        }
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci()
    {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i < 0 || i >= capacity) {
            throw std::out_of_range("Index out of range");
        }

        // 如果 i 已缓存，直接返回
        if (cached > i) {
            return cache[i];
        }

        // 计算并缓存 Fibonacci 数
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1; // 更新已缓存的数量

        return cache[i];
    }
    // 访问运算符，简化获取 Fibonacci 数
    size_t operator[](int i) {
        return get(i);
    }

     size_t operator[](int i) const {
        if (i < 0 || i >= cached) {
            throw std::out_of_range("Index out of range");
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
