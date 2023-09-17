

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
	id int unsigned auto_increment primary key '学生id主键',
    name varchar(5) not null
)

create table tb_course(
	id int unsigned auto_increment primary key '课程id主键',
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

