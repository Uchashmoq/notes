#include<string>
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex msg_lock;
bool ready = false;
condition_variable cv;

void producer(string *msg){
    {
        //3. 出让后获得锁
        unique_lock<mutex> lck(msg_lock);
        cin>>(*msg);
        ready=true;
    }
    //使锁回归
    cv.notify_all();
}
void comsumer(string *msg){
    //1 .先获得锁
    unique_lock<mutex> lck(msg_lock);
    //2 .出让锁，等待notify再回归
    cv.wait(lck , [](){return ready;});
    cout<<"receive : "<<(*msg)<<endl;
}
int main(){
    string s;
    thread pth(producer,&s);
    thread cth(comsumer,&s);
    pth.join();
    cth.join();
}