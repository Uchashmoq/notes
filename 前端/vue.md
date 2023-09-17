## 引入

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <script src="js/vue.js"></script>
</head>
<body>
    <div id="app">
        <!-- 
            或<a :href="url">链接</a>
            声明一个叫url的数据
        -->
        <a v-bind:href="url">链接</a>
        <input type="text" v-model="url">
        跳转到{{url}}
        <input type="button" value="显示链接" v-on:click="handler()">

    </div>
</body>
<script>
    new Vue({
        el:"#app",
        data:{
            url : ""
        }，
        methods:{
            handler : function(){
                alert("按钮被点击")
            }
        }
    })
</script>
</html>
```

## 绑定

```vue
<a v-bind:href="变量名"></a> 
<a :href="变量名"></a>
<!--绑定链接值-->

<input type="text" v-model="变量名"> 
<!--绑定表单内容-->

<input type="button" value="显示链接" v-on:click="handler()">
<!--绑定事件-->

<span v-if="age<20"> if </span>
<span v-else-if="age<=20 && < 40"> else_if </span>
<span v-else> else </span>

<span v-show="条件"> v-show </span>
<!--条件渲染-->

<div v-for="e in list"> {{e}} </div>
<div v-for="(e,index) in list"> {{e}} </div>
<!--循环，list是data里的列表-->

```

## 生命周期

```js
//和data平级
mounted(){
	alert("挂载完成")
}
```

## 脚手架

### 结构

src/main.js

```js
import Vue from 'vue';
import App from './App.vue';
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';
Vue.config.productionTip = false

Vue.use(ElementUI)
new Vue({
  render: h => h(App),
}).$mount('#app')
```

src/APP.vue

```html
<template>
  <div id="app">
    <element-view></element-view>  引入element组件
  </div>
</template>

<script>
import ElementView from './views/element/ElementView.vue'
export default {
  components: { ElementView },
  data : function(){
    return {
      //message : "hello vue"
    }
  },
}
</script>
<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
```

src/views/element

```html
<template>
  <div>
    <el-row>
       <!---->
      <el-button>默认按钮</el-button>
      <el-button type="primary">主要按钮</el-button>
      <el-button type="success">成功按钮</el-button>
      <el-button type="info">信息按钮</el-button>
      <el-button type="warning">警告按钮</el-button>
      <el-button type="danger">危险按钮</el-button>
    </el-row>
      
    <br />
     <!--表格-->
    <el-table :data="tableData" style="width: 100%">
      <el-table-column prop="date" label="日期" width="180"> </el-table-column>
      <el-table-column prop="name" label="姓名" width="180"> </el-table-column>
      <el-table-column prop="address" label="地址"> </el-table-column>
    </el-table>
  </div>
</template>

<script>
export default {
  data() {
    return {
      tableData: [
        {
          date: "2016-05-02",
          name: "王小虎",
          address: "上海市普陀区金沙江路 1518 弄",
        },
        {
          date: "2016-05-04",
          name: "王小虎",
          address: "上海市普陀区金沙江路 1517 弄",
        },
        {
          date: "2016-05-01",
          name: "王小虎",
          address: "上海市普陀区金沙江路 1519 弄",
        },
        {
          date: "2016-05-03",
          name: "王小虎",
          address: "上海市普陀区金沙江路 1516 弄",
        },
      ],
    };
  },
};
</script> 

<style>
</style>
```

### 分页

```html
<el-pagination background layout="prev, pager, next,jumper"
    @size-change="handleSizeChange"
    @current-change="handleCurrentChange"
    :total="1000">
</el-pagination>

<script>
  export default {
    methods: {
      handleSizeChange(val) {
        console.log(`每页 ${val} 条`);
      },
      handleCurrentChange(val) {
        console.log(`当前页: ${val}`);
      }
    },
  }
</script>
```

### 对话框

```html
<!-- Table -->
 	<el-button type="text" @click="dialogTableVisible = true"
      >打开嵌套表格的 Dialog</el-button
    >
    <el-dialog title="收货地址" :visible.sync="dialogTableVisible">
      <el-table :data="gridData">
        <el-table-column
          property="date"
          label="日期"
          width="150"
        ></el-table-column>
        <el-table-column
          property="name"
          label="姓名"
          width="200"
        ></el-table-column>
        <el-table-column property="address" label="地址" width="200"></el-table-column>
      </el-table>
    </el-dialog>
```

### 表单

```html
<!--dialog-->
    <el-button type="text" @click="formDialogTableVisible = true"
      >打开表单Dialog</el-button
    >
    <el-dialog title="收货地址" :visible.sync="formDialogTableVisible">
      <el-form ref="form" :model="form" label-width="80px">
        <el-form-item label="活动名称">
          <el-input v-model="form.name"></el-input>
        </el-form-item>
        <el-form-item label="活动区域">
          <el-select v-model="form.region" placeholder="请选择活动区域">
            <el-option label="区域一" value="shanghai"></el-option>
            <el-option label="区域二" value="beijing"></el-option>
          </el-select>
        </el-form-item>   
        <el-form-item>
          <el-button type="primary" @click="onSubmit">立即创建</el-button>
          <el-button>取消</el-button>
        </el-form-item>

      </el-form>
    
</el-dialog>


<script>
export default {
  methods: {
    onSubmit(){
      alert(`提交了${this.form.name},${this.form.region}`)
    },
  },
}
</script>
```

