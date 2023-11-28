### 声明类

```c++
class Student {
private:
    string _name;
public:
    Student();
    Student(string name);
    Student(const Student& stu);//拷贝式构造
    ~Student();
    void intro()const;
};
void Student:: intro()const {
    cout<<"i am"<<_name<<endl;
}
Student::Student() : _name("NULL"){
    //初始化列表
}
//有参写了后就不提供默认构造
Student::Student(string name){
    _name=name;
}
//已有对象克隆
//在值传递函数参数时调用
//值返回局部对象

//拷贝构造写了就不提供其他构造
//指针成员最好深拷贝
Student::Student(const Student& stu){
    _name=stu._name;
}

Student::~Student(){
    cout<<_name<<" deleted"<<endl;
}

```

### 创建对象

```c++
	Student stu1("xjp");
    stu1.intro();

    Student stu2=Student("jzm");
    stu2.intro();

    Student stu3(stu2);
    stu3.intro();
```

### 静态字段

```c++
class Student{
    public:
    //静态字段和方法不占对象内存
    static string _teacher;
    static void say(){
        //静态方法只能访问静态
        cout<<"Students' teacher is "<<_teacher<<endl;
    }
};
//类内声明，类外初始化
string Student::_teacher="wzl";
int main(){
    Student s;
    cout<<Student::_teacher<<endl;
}
```

### this指针

return *this;链式调用

if(this==NULL) return;防止空指针异常

void func() const{} 常函数，this不可修改，常对象只能调常函数，mutable字段在常函数可修改

### 友元

```c++
class MyClass {
private:
    int privateData;

public:
    MyClass(int data) : privateData(data) {}

    // 声明友元函数
    friend void friendFunction(const MyClass& obj);
    friend class MyFriend;//该类的方法可以访问MyClass的私有成员
    friend int MyFriend::func();//友元方法
    
};

// 定义友元函数
void friendFunction(const MyClass& obj) {
    std::cout << "访问私有数据：" << obj.privateData << std::endl;
}

int main() {
    MyClass obj(42);
    friendFunction(obj); // 调用友元函数

    return 0;
}
```

### 运算符重载

#### +

```c++
Student Student::operator+(Student &stu){
    return Student(this->_name,this->_age+stu._age);
}//通过方法重载

//全局函数重载：。。。。
```

### <<

```c++
void operator<<(std::ostream &cout,Student s){
    cout<<"reload<<"<<endl;
}
```

#### 前置++

```
Student& Student::operator++(){
	this->_age++;
	return *this;
}//返回引用，对同一个对象操作,先加再使用
```

#### 后置++

```c++
Student Student::operator++(Student){
	Student tmp=*this;//先用再加
    this._age++;
    return tmp;
}
```

#### =

```c++
Student& Student::operator=(Student& stu){
	//判断this是否有堆区数据，如果有，先释放再深拷贝
	
    //拷贝各字段
	return *this;//为了连等
}
```

#### 仿函数

```c++
int operator()(int a,int b){
	return a+b;
}
```

### 继承

```c++
class 基类 {
  // 基类成员声明
};

class 派生类 : (virtual 虚继承)访问修饰符 基类 {
  // 派生类成员声明
};
```

![继承方式](.\继承方式.png)

```
1.非静态可继承，私有隐藏
2.构造 先父后子     析构 先子后父
3.同名成员，访问父类要加作用域 o.Base::foo(),父类中同名成员（包括重载）被隐藏
4.静态同名
Son::a 或 Son::Base::a
子类的静态同名成员函数也会隐藏父类的同名函数
```

### 多态

```
基类方法加virtual，虚方法
重写 名 返回 参数表 相同
虚函数会在派生类占空间 vfptr

纯虚函数：
virtual 返 名 (参数表)=0;
必须重写，或也为抽象类

虚析构:
子类赋给父类，父类析构时子类不会析构
需要在父类析构方法加virtual，保证子类析构调用
virtual ~Foo(){}

纯虚析构：
父类析构是纯虚函数
virtual ~Foo()=0
Foo::~Foo(){

}
```



