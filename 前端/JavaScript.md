## 引入

```html
<script>
    alert("666")
</script>

<script src="js/demo.js"></script>
```

## 输出

```js
window.alert("window alert");
document.write("document write");
console.log("console log");
```

## 变量

```js
var x = 1;
let y = 2;
const z = 3;
```

## 类型

```js
typeof 3
typeof null
typeof x

parseInt("12")
parseInt("12A13")//12
parseInt("A13")//NaN 

Number 0,NaN false
String 空false
Null , undefined : false
```

## 函数

```js
function add(a,b){
    return a+b;
}

var add = function (a,b){
    return a+b;
}
```

## 数组对象

```js
var arr = new Array(1,2,3)
var arr = [1,2,3]
//长度可变，有undefined索引

//遍历
for (let i=0;i<arr.length;i++){
    console.log(arr[i])
}

arr.foreach(function(e){
    //处理每一个e(不包括undefined)
})

arr.foreach((e)=>{
    //处理每一个e(不包括undefined)
})

//增删
arr.push(4,5,6)
arr.splice(offset,n)
```

## 字符串对象

```js
var s1= new String("hello")
s2="hello"

str.charAt(0)
str.indexOf("lo")
str.trim()
str.substring(start,end)
```

## 自定义对象

```js
var Person = {
    name : "zhangsan"
    eat : function(){
        alert("eat")
    } 
}
```

## json对象

```js
var jsonstr = '{"name" : "zhangsan","age" : "20"}'
//转对象

var obj = JSON.parse(jsonstr)
alert(obj.name)

var jsonstr = JSON.stringify(obj)
```



## BOM

### window

```js
//确认框
var flag = confirm("你确定吗")
//定时器
setInterval(func,毫秒间隔)
//延迟
setTimeout(func,毫秒)
```

### location

```js
location.href="baidu.com"//跳转
```

## DOM

```js
var img = document.getElementById("foo") //id获取
var divs = document.getElementByTagName("div")//标签名获取
							  (Class)Name("hobby")
							  
```

## 事件

```js
//HTML属性绑定 
onclick = "on()"
//DOM对象
obj=document.getElementById("obj1");
obj.onclick = function(){
    
}

```

