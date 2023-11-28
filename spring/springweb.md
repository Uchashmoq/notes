## hello world

```java
package com.mahaoran.controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {
    @RequestMapping("/hello")
    public String hello(){
        System.out.println("hello world");
        return "hello world";
    }
}
```

## 获取参数

### 原始

```java
@RestController
public class HelloRequestController {
    @RequestMapping("/testRequest")
    public String simpleRequest(HttpServletRequest request){
        String name = request.getParameter("name");
        String age = request.getParameter("age");
        System.out.printf("name = %s, age = %s\n",name,age);
        return "OK";
    }
}
```

### spring

```java
@RestController
public class HelloSpringRequestController {
    @RequestMapping("/springRequest")
    public String springRequest(String name,Integer age){
        System.out.printf("name = %s,age = %s\n",name,age);
        return "OK";
    }
}
```

参数名映射

```java
 @RequestMapping("/springRequest")
//请求中name->username
    public String springRequest(@RequestParam(name="name",required=false) String username,Integer age){
        System.out.printf("name = %s,age = %s\n",name,age);
        return "OK";
}
```

### 绑定实体类

```java
@RestController
public class HelloPojoController {
    @RequestMapping("/pojoRequest")
    public String pojoRequest(User user){
        System.out.println(user);
        return "OK";
    }
}
```

### 数组集合参数

数组

```java
public String pojoRequest(String[] hobby){}
//URL参数 : ?hobby=dance&hobby=sing
```

集合

```java
public String pojoRequest(@RequestParam List<String> hobby){}
//URL参数 : ?hobby=dance&hobby=sing
```

### 日期

```java
public String dateParam(@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") LocalDateTime time){}
//URL参数 : ?time=2022-12-12 10:05:45
```

### JSON

```java
public String jsonParam(@RequestBody User user){}
//在post请求的body发送JSON，键和成员变量名保持一致
```

### 路径参数

```java
 @RestController
public class HelloPathVariable {
    @RequestMapping("/path/{i}")//可有多个变参
    public String pathVariable(@PathVariable Integer i){
        System.out.println(i);
        return "OK";
    }
}

//URL : http://localhost:8080/path/2
```

## IOC容器

`@Component`将该实现类交给IOC容器

`@Autowired`变量自动从容器寻找实现类

### @Component衍生注解

`@Controller` 控制器层

`@Service` service层

`@Repository`DAO层  `@Repository(value="foo")` 指定bean的名字

### bean扫描范围

启动类所在包以及子包

`@ComponentScan({"com.mahaoran","dao"})`在启动类上，手动指定bean扫描范围

### 同一个接口找到了多个bean

1.在要注入的实现类加上`@Primary`

2.`@Autowired`上加上`@Qualifier(bean的名字)`

3.`@Autowired`换成`@Resource(bean的名字)`

## RESTFUL

指定请求方法

`@RequestMapping(value="URL",method = RequestMethod.GET)` 或 @GetMapping("URL")
