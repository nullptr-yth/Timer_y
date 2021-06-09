#include <iostream>
#include "Timer.h"
int t =0;
void test(void* i)
{
    t+=1;
    std::cout << "test:"<< t<< std::endl;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    Timer tmTest;
    tmTest.Init(1000,test, nullptr);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    tmTest.start();
    while (t<10)
    {}
    tmTest.stop();
   // t=0;
   // tmTest.start();
    while (t<10)
    {}
    return 0;
}