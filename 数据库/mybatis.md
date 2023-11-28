## HelloWorld

1.配置`application.properties`

```properties
spring.datasource.url=jdbc:mysql://localhost:3306/test
spring.datasource.username=root
spring.datasource.password=6666
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
```

2.编写查询接口

```java
@Mapper
public interface UserMapper {
    @Select("select * from student")
    List<Student> getAllStudents();
}
//Students字段对应
```

3.测试

```java
@SpringBootTest
class HelloMybaitisApplicationTests {
    @Autowired
    private UserMapper mapper;
    @Test
    public void getAllStudents(){
        List<Student> li = mapper.getAllStudents();
        for(Student stu : li){
            System.out.println(stu);
        }
    }
}
```

## 增删改查

```java
 //#预编译 $拼接
@Delete("delete from emp where id = #{id}")
int delete(Integer id);

@Select("select id, name, age, dept_id deptId from emp")
List<Employee> getAllEmp();

@Options(keyProperty = "id",useGeneratedKeys = true)//主键封装到id里，需要返回主键，可在ep里面查看主键
@Insert("insert into emp(name, age, dept_id) VALUES ( #{name}, #{age},#{deptId})")
void insert(Employee ep);

//dept_id deptId sql参数别名
@Select("select id, name, age, dept_id from emp where id=#{id}")
Employee getById(Integer id);
```

### concat拼接

`where name like concat('%',#{name},'%')` 

### 单独使用

sql注解`#{name}`

形参 ：`@Param("name") String name`



## XML

- xml和接口名一致
- xml位于resources和接口同包
- namespace : 接口全类名 ，id：方法名，resultType：单个返回值类型

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="com.example.hellomybaitis.mapper.EmpXmlMapper">
    <select id="getAllEmp" resultType="com.example.hellomybaitis.pojo.Employee">
        select * from emp
    </select>
</mapper>
```



```java
@Mapper
public interface EmpXmlMapper {
    List<Employee> getAllEmp();
}
```

## 动态sql

### if

```xml
<select id="getAllEmp" resultType="com.example.hellomybaitis.pojo.Employee">
    	select * from emp
    	where
    <if test="name != null">
    	name like concat('%',#{name},'%')
    </if>
    <!--name不为空，拼接name-->
 </select>
```

### where

```xml
<where>
	<if test=>
    	...
    </if>
    
    <if test=>
        ...
    </if>   
</where>
```

### set

```xml
<mapper namespace="com.example.hellomybaitis.mapper.EmpXmlMapper">
    <update id="updateEmp">
        update emp
        <set>
            <if test="name !=null">
                name=#{name},
            </if>
            <if test="age!=null">
                age=#{age},
            </if>
            <if test="deptId!=null">
                dept_id=#{deptId}
            </if>
        </set>
        where id=#{id}
    </update>
```

### foreach

`void deleteById(List<Integer> ids);`

list名 每一个物品名 分隔符 左 右    (1,2,3)

```xml
 <delete id="deleteById">
        delete from emp where id in
        <foreach collection="ids" item="id" separator="," open="(" close=")">
            #{id}
        </foreach>
  </delete>

```

### 抽取

```xml
<sql id="xxx">
	sql片段
</sql>

<!--引入-->
<include refid="xxx"/>
```



