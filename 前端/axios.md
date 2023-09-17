## 引入

`<script src="https://cdn.jsdelivr.net/npm/axios/dist/axios.min.js"></script>`

## 发送请求

```js
const data = {
  username: 'john_doe',
  email: 'john@example.com'
};

// 发送 POST 请求
axios.post('/your-api-endpoint', data)
  .then(response => {
    // 处理成功响应
    console.log('成功响应:', response.data);
  })
  .catch(error => {
    // 处理请求错误
    console.error('请求错误:', error);
  });
```

