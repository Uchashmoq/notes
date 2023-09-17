## 环境配置

#### 下载

go get github.com/gin-gonic/gin  

go get github.com/pilu/fresh

运行热加载 go run github.com/pilu/fresh

#### 初始化

```go
func ini() {
	r := gin.Default()
	r.GET("/", findex)
	r.GET("/news", fnews)
	r.GET("/admin/index", admfindex)
    r.SetFuncMap(template.FuncMap{
		"Myfunc": Myfunc,
	})
	//加载两层目录下的文件
	r.LoadHTMLGlob("www/**/*")
	r.Run("127.0.0.1:19999")

}
```





## HTML渲染

#### gin.H渲染

```go
//路由函数
func findex(c *gin.Context) {
	mp := gin.H{
		"Title": "首页",
		"Addr":  "本地",
	}
	c.HTML(http.StatusOK, "default/index.html", mp)
}
```

```html
<h2>{{.Title}}</h2>
<p>{{.Addr}}</p>
```

#### 结构体渲染

```go
func fnews(c *gin.Context) {
	vnews := &Artical{
		Title:   "这是新闻",
		Context: "这是内容",
	}
	c.HTML(200, "default/news.html", gin.H{
		"news": vnews,
	})
}
```

```html
<!--news是H的键，键对应结构体变量.后是结构体字段-->
    <h2>{{.news.Title}}</h2>
    <br>
    <p>{{.news.Context}}</p>
```

#### 别名

```html
{{ define "default/news.html" }}

!!!
{{end}}
```

#### 变量

```html
 <p>{{.Addr}}</p>
    {{$a := .Addr}}
  <p>这是变量：{{$a}}</p>
```

#### 自定义模板函数

```go
r.SetFuncMap(template.FuncMap{
		"Myfunc": Myfunc,
})


func Myfunc(s string) string {
	return "MyFunc处理了字符串：" + s
}

```



```html
<p>自定义函数 {{Myfunc .Introduction}}</p>
```

#### 遍历

```go
"Friends": []interface{}{
			&Person{
				Name: "舟少",
				QQ:   "12345",
			},
			&Person{
				Name: "吃鸡",
				QQ:   "89648964",
			},
		},
```

```html
<h4>Friends循环</h4>
    <!--range生成person变量，再访问person每个成员-->
    {{range $person:= .Friends}}
    <div>
        <p>name: {{$person.Name}}</p>
        <p>qq: {{$person.QQ}}</p>
        <br>
    </div>
    {{else}}
    <!--切片长度为0-->
        <p>没有朋友</p>
    {{end}}
```

#### 公共模板

```html
{{define "page_head"}}
<h1 style="color:aqua; background: #000">公共标题</h1>
{{end}}

引入：
{{template "page_head" .}}
```

#### 静态路由

```go
//         路由             映射的目录
	r.Static("/staticRouter", "./static")
```

```
```

#### GET

```
name := c.DefaultQuery("name", "NULL")
passwd := c.DefaultQuery("passwd", "NULL")

http://127.0.0.1:19999/get?name=zk&passwd=yyy

```

#### POST

```go
r.POST("/login", fpost)

func fpost(c *gin.Context) {
	name := c.DefaultPostForm("name", "NULL")
	passwd := c.DefaultPostForm("passwd", "NULL")//取出对应字段
	fmt.Println(name, passwd)

	c.HTML(200, "default/get.html", gin.H{
		"re": "login " + name + "@" + passwd,
	})
}
```

```html
			路由           方法
<form action="/login" method="post">
        用户名:<input type="text" name="name" /><br>  字段对应
        用户名:<input type="text" name="passwd" /><br>

        <input type="submit" value="提交">
</form>
```

#### GET绑定结构体

```go
//字段 					类型 			标签备注
Username string `json:"username" form:"username"`
err:=c.ShouldBind(对象指针)
```

## 路由组

#### 分组

```go
usg := r.Group("/user")
	{
		usg.GET("/login", controllers.UserController{}.Login)
		usg.GET("/info", controllers.UserController{}.Info)
	}
```

路由函数为控制器的方法，路由函数相同逻辑在一个源文件，并放在专门存路由的文件夹，控制器放在另一个文件夹
