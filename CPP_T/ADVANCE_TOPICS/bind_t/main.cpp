#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <future>
#include <cmath>

using namespace std;
using namespace placeholders;


float Func(int value){
    return pow(value , 2.0);
}

int fn(float first, float second , float third){
    return first+second+third;
}

int main(){
    std::future<float> fut_sumtotal = td::async(std::launch::async,Func,8);
    thread t1(Func,std::move(sumtotal),8);
    thread t2(Func,std::move(sumtotal),87);
    thread t3(Func,std::move(sumtotal),6);


std:cout<<fut_sumtotal.get()<<endl;


 /*   int first = 100;
    auto f2 = bind(fn,first,_1,_2);
    int second = 200;
    auto f3 = bind(f2,second,_1);
    int third = 300;
    int result = f3(third);

    cout<<result<<endl;*/

    return 0;

}