

# DDL

## 创建表

```sql
create table 表名(
	字段i 字段类型 [约束] [comment 注释],
    ...
)[comment 表注释];
```

约束:

not null,	unique,	primary key,	auto_increment,	default,	foreign key

```sql
#eg
create table department (
	id int unsigned primary key auto_increment comment 'ID',
    name varchar(10) not null unique comment '部门名称'
)comment '部门表';
```



## 修改表

### 添加字段

```sql
alter table 表名
add 字段名 类型
[comment] [约束]
```

### 修改字段类型

```sql
alter table 表名
modify 字段名 新类型
[comment]
```

### 删除字段

```sql
alter table 表名
drop column 字段名
```

### 修改字段名

```sql
alter table 表名
change 字段名 新名字
[comment]
```

# DML

## insert

```sql
insert into emp(name,age,gender) values ('zhangsan',70,1),('lisi',30,2);
```

## update

```sql
update account 
set username='zhangsan' 
where username='lisi' and passwd='8888';
```

## delete

```sql
delete from account where username='zhangsan';
```

# DQL

## 基础语法

```sql
select 字段列表
from 表名列表
where 条件
group by 分组字段 #分组字段要和选择字段相同
having 分组后条件列表
order by 排序字段
limit 起始索引,每页量
```



##  流程控制

```sql
#if
select if(gender = 1,'男','女') 性别,count(*) from emp group by gender;
#case
select(
	case job
		when 1 then '班主任'
		when 2 then '学生'
		else '未分配职位'
	end
) 职位
count(*)
from emp
group by job;
```

# 多表

## 一对多

```sql
create table department (
	id int unsigned primary key auto_increment comment 'ID',
    name varchar(10) not null unique comment '部门名称'
)comment '部门表';

create table emp (
	id int unsigned primary key auto_increment comment '员工ID',
    name varchar(5) not null comment '姓名',
    age tinyint unsigned comment '年龄',
    dept_id int unsigned comment '所属部门id'，
    FOREIGN KEY (dept_id) REFERENCES department (id) #将dept_id与department表的id关联
)comment '员工表';
```

```sql
#添加外键约束
ALTER TABLE emp
ADD CONSTRAINT fk_emp_dept #外键约束名
FOREIGN KEY (dept_id) REFERENCES department (id);
```

## 一对一

任意一方加入 外键 关联另一方的 主键

## 多对多

创建一张中间表

```sql
create table tb_student(
	id int unsigned auto_increment primary key comment '学生id主键',
    name varchar(5) not null
)

create table tb_course(
	id int unsigned auto_increment primary key comment '课程id主键',
    course_name varchar(5) not null
)

create table tb_stu_course(
	id int unsigned auto_increment primary key,
    stu_id int unsigned not null,
	course_id int unsigned not null,
    
    constraint fk_stu_id foreign key(stu_id) references tb_student(id),
    constraint fk_course_id foreign key(course_id) references tb_course(id)
)

```

# 多表查询

```sql
select * from tb_emp,tb_dept where tb_emp.dept = tb_dept.id;
```

## 内连接

```sql
#查询员工以及所在部门
#隐式
select tb_emp.name , tb_dept.name from tb_emp , tb_dept where tb_emp.dept_id = tb_dept.id;
#显式
select tb_emp.name , tb_dept.name from tb_emp , tb_dept inner join tb_dept on tb_emp.dept_id = tb_dept.id;
#若某行 tb_emp.dept_id 为NULL，无法查出
```

## 外连接

```sql
#左
#查询员工以及所在部门,包括部门id为NULL的员工
select e.name , d.name
from tb_emp e
left join tb_dept d
on e.dept_id = d.idl

#右
#查询部门下的员工
select e.name , d.name
from tb_emp e
right join tb_dept d
on e.dept_id = d.idl;
```

## 子查询

```sql
#标量 第一步查出单行单列值
#找出教研部对应的id，查询该id下的所有员工
select * from tb_emp where dept_id = (select id from tb_dept where name = '教研部');

#列子查询 子查询查出一列 in(),not in()
select * from tb_emp where dept_id in( select id from tb_dept where name in('教研部','咨询部'));

#行子查询 查询和韦一笑入职日期，以及职位相同的人
select * from tb_emp where (entrydate , job)=(select entrydate , job from tb_emp where name = '韦一笑');

#表子查询
select e.* , d.name 
from (select * from tb_emp where entrydate > '2006-01-01') e , tb_dept d
where e.dept_id = d.id;
```

## 例

```sql
select name , count(*) from tb_dish d ,tb_category c where d.category_id = c.id and d.status = 1 group by c.name having count(*)>2;

#查询商务套餐A包含的菜品的信息
select * 
from setmeal s,setmeal_dish sd,dish d
where s.id = sd.setmeal_id and sd.dish_id = d.id and s.name = '商务套餐A';

#查询低于平均价的菜品
select * from dish where price < (select avg(price) from dish)
```

# 事务

 ```sql
 start transaction;
 #sql
 commit; #成功
 rollback; #失败
 ```

# 索引

## 创建

```sql
create [unique] index 索引名 on 表名 (字段...);
```

## 查看

```sql
show index from 表名;
```

## 删除

```sql
drop index 索引 on 表名;
```

