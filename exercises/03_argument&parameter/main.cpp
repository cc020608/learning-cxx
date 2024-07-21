// READ: <https://stackoverflow.com/questions/156767/whats-the-difference-between-an-argument-and-a-parameter>

#include "../exercise.h"
#include <iostream>
#include <cassert>
void func(int);

// TODO: 为下列 ASSERT 填写正确的值
int main(int argc, char **argv) {
    auto arg = 99;
    ASSERT(arg == 99, "arg should be 99");
    std::cout << "befor func call: " << arg << std::endl;
    func(arg);
    ASSERT(arg ==99 , "arg should be 99");
    std::cout << "after func call: " << arg << std::endl;
    return 0;
}

// TODO: 为下列 ASSERT 填写正确的值
void func(int param) {
    int x=param;
    ASSERT(param ==x , "param should be x");
    std::cout << "befor add: " << param << std::endl;
    param += 1;
    ASSERT(param ==x+1 , "param should be x+1");
    std::cout << "after add: " << param << std::endl;
}
