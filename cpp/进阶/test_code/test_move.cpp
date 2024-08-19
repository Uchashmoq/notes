#include<iostream>
#include<string>
#include<memory>
using namespace std;
struct Person{
    int age;
    string name;
    Person(int&& age,string&& name){
        this->age=age,this->name=name;
    }
    Person(Person& person){
        puts("copy constructor");
        this->age=person.age,this->name=person.name;
    }
    ~Person(){
        cout<<age<<" , "<<name<<" distructed"<<endl;
    }
};
int main(){
    unique_ptr<Person> p(new Person(18,"zhangsan"));
    unique_ptr<Person> p1;
    p1=move(p);
    
}