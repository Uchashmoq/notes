using namespace std;
#include<thread>
#include<iostream>
void thread_func(string name){
    cout<<"start "<<name<<endl;
}
int main(){
    //线程函数传参
    thread th1(thread_func,"join");
    th1.join();
    //lambda表达式
    thread th2([](){cout<<"start lambda\n";});
    th2.join();

    thread th3(thread_func,"named detach");
    th3.detach();
    
    //匿名分离态线程
    thread (thread_func,"detach thread").detach();
    getchar();
}