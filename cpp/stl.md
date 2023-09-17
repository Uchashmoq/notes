### vector

```c++
#include<vector>

vector<int> v;
v.push_back(10);

//遍历
for(vector<int>::iterator it=v.begin;it!=v.end();it++){
    *it
}
//for_each遍历
for_each(v.begin(),v.end(),int回调)
```

