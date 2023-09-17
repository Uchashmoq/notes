```c++
//cin
string s,t;
    cin>>s>>t;
    cout<<s<<t<<endl;

//cin.get(buf,n)
char buf[10];
    cin.get(buf,5);//最多4个字符
    string s(buf);
    cout<<s;
//getline
 string s;
    getline(cin,s);
    cout<<"a line: "<<s;
```

