#include<iostream>
#include <functional>
using namespace std;
struct Add{
    int operator()(int a,int b){
        return a+b;
    }
    int add(int a,int b){
        return a+b;
    }
};
int main(){
    int b=2;
    Add obj;
    auto func=bind(obj,2,placeholders::_1);
    //绑定参数
    cout<<func(1)<<endl;

    //绑定成员函数
    auto func1=bind(&Add::add,&obj,placeholders::_1,placeholders::_2);
    cout<<func1(10,20)<<endl;
}
