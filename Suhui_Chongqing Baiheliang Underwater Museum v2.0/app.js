// 引入依赖
const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const bodyParser = require('body-parser');
const path = require('path');
const cors = require('cors');

// 创建 Express 应用和 HTTP 服务器
const app = express();
const server = http.Server(app);
const io = socketIo(server);
const PORT = 8000;

// 中间件配置
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static(path.join(__dirname, 'public')));
app.use(cors()); // 允许所有跨域请求

// 默认用户信息
const defaultUser = {
  username: 'tourist',
  password: '123456'
};

// 处理登录请求
app.post('/login', (req, res) => {
  const { username, password } = req.body;

  if (username === defaultUser.username && password === defaultUser.password) {
    // 登录成功，跳转到 chat.html
    return res.redirect('/chat.html');
  } else {
    // 登录失败，返回错误提示
    res.send(`
      <h1>登录失败！</h1>
      <a href="/">返回登录页面</a>
    `);
  }
});


// 存储已登录的游客信息
const users = [];
// 启动服务器
server.listen(PORT, '0.0.0.0', () => {
  console.log(`服务器启动成功了，监听地址为 http://0.0.0.0:${PORT}`);
});
// 设置静态资源目录
app.use(express.static('public'));
// 处理默认首页请求
app.get('/', (req, res) => {
  res.redirect('/index.html');
});
// 监听 Socket 连接
io.on('connection', (socket) => {
  console.log('有用户连接到服务器');
  // 用户登录
  socket.on('login', (data) => {
    const user = users.find((item) => item.username === data.username);
    if (user) {
      // 登录失败，用户已存在
      socket.emit('loginError', { msg: '登录失败，用户名已存在' });
    } else {
      // 登录成功，保存用户信息
      users.push(data);
      // 告知用户登录成功
      socket.emit('loginSuccess', data);
      // 通知所有用户新用户加入
      io.emit('addUser', data);
      // 通知所有用户更新用户列表
      io.emit('userList', users);
      // 保存当前登录用户的信息
      socket.username = data.username;
      socket.avatar = data.avatar;
    }
  });
  // 用户断开连接
  socket.on('disconnect', () => {
    /**
     * 查找用户在用户列表中的索引。
     * 
     * socket 工作流程：
     * 1. 客户端与服务器建立连接，服务器会为每个连接创建一个 socket 对象。
     * 2. 服务器通过 socket 对象与客户端进行通信，接收和发送消息。
     * 3. 每个 socket 对象包含连接用户的相关信息，例如用户名、连接时间等。
     * 4. 在处理用户相关操作时，可以通过 socket 对象获取当前连接用户的信息。
     * 5. 通过 socket.username 获取当前连接用户的用户名，并在用户列表中查找其索引。
     */
    const idx = users.findIndex((item) => item.username === socket.username);
    if (idx !== -1) {
      // 从用户列表中删除
      users.splice(idx, 1);
      // 通知有人离开聊天室
      io.emit('delUser', {
        username: socket.username,
        avatar: socket.avatar,
      });
      // 通知更新用户列表
      io.emit('userList', users);
    }
  });
  // 接收聊天消息
  socket.on('sendMessage', (data) => {
    console.log('收到消息:', data);
    io.emit('receiveMessage', data); // 广播消息
  });
  // 接收图片消息
  socket.on('sendImage', (data) => {
    io.emit('receiveImage', data); // 广播图片
  });
});
