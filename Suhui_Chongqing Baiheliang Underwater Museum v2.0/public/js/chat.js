// 连接socketio服务
var socket = io('http://localhost:8000')
var username, avatar

// 选择头像时添加选中样式
$('#login_avatar li').on('click', function () {
  // 给当前点击的元素添加类名now，表示当前选中
  $(this)
   .addClass('now')
   .siblings()
    //确保只有一个被选中
   .removeClass('now')
})

// 点击时执行登录相关操作
$('#loginBtn').on('click', function () {
  //获取输入框中输入的用户名
  var username = $('#username')
   .val()
   .trim()
  // 用户名未输入，弹出提示并终止操作
  if (!username) {
    alert('请输入用户名')
    return
  }
  // 获取当前选中头像的作为头像
  var avatar = $('#login_avatar li.now img').attr('src')
  // 向服务器发送登录请求，传递用户名和头像信息
  socket.emit('login', {
    username: username,
    avatar: avatar
  })
})

// 登录失败
socket.on('loginError', data => {
  alert('用户名已经存在')
})

// 登录成功
socket.on('loginSuccess', data => {
  // 淡出登录框
  $('.login_box').fadeOut()
  // 淡入聊天容器，显示聊天界面
  $('.chat_container').fadeIn()
  console.log(data)
  //头像
  $('.avatar_url').attr('src', data.avatar)
  //用户名
  $('.user-list.username').text(data.username)

  username = data.username
  avatar = data.avatar
})

//添加用户的消息
socket.on('addUser', data => {
  $('.box-bd').append(`
    <div class="system">
      <p class="message_system">
        <span class="content">${data.username}加入了群聊</span>
      </p>
    </div>
  `)
})

// 用户列表消息
socket.on('userList', data => {
  // 先清空用户列表的原有内容
  $('.user-list ul').html('')
  data.forEach(item => {
    $('.user-list ul').append(`
      <li class="user">
        <div class="avatar"><img src="${item.avatar}" alt="" /></div>
        <div class="name">${item.username}</div>
      </li>      
    `)
  })
  // 当前用户列表的长度
  $('#userCount').text(data.length)
})

// 用户离开消息
socket.on('delUser', data => {
  $('.box-bd').append(`
    <div class="system">
      <p class="message_system">
        <span class="content">${data.username}离开了群聊</span>
      </p>
      </div>
    `)
})

// 聊天功能
$('.btn-send').on('click', () => {
  // 获取聊天输入框中的内容
  var content = $('#content').html()
  // 清空聊天输入框内容
  $('#content').html('')
  // 如果内容为空，弹出提示并终止后续操作
  if (!content) return alert('请输入内容')

  // 向服务器发送聊天消息，传递消息内容、用户名和头像信息
  socket.emit('sendMessage', {
    msg: content,
    username: username,
    avatar: avatar
  })
})

// 监听服务器发送的聊天消息，若收到则在聊天记录区域添加相应聊天记录展示
socket.on('receiveMessage', data => {
  // 记录聊天记录区域当前的滚动位置，方便后续恢复
  var scrollPosition = $('.box-bd').scrollTop()

  if (data.username === username) {
    $('.box-bd').append(`
      <div class="message-box">
        <div class="my message">
          <img class="myavatar" src="${data.avatar}" alt="" />
          <div class="content">
            <div class="bubble">
              <div class="bubble_cont">${data.msg}</div>
            </div>
          </div>
        </div>
      </div>
    `)
  } else {
    $('.box-bd').append(`
      <div class="message-box">
        <div class="other message">
          <img class="avatar" src="${data.avatar}" alt="" />
          <div class="content">
            <div class="nickname">${data.username}</div>
            <div class="bubble">
              <div class="bubble_cont">${data.msg}</div>
            </div>
          </div>
        </div>
      </div>
    `)
  }

  // 恢复聊天记录区域的滚动位置到之前记录的位置
  $('.box-bd').scrollTop(scrollPosition)
})

// 发送图片功能，为文件选择框绑定change事件，选择文件后进行发送图片相关操作
$('#file').on('change', function () {
  var file = this.files[0]
  var fr = new FileReader()
  fr.readAsDataURL(file)
  fr.onload = function () {
    // 向服务器发送图片消息，传递用户名、头像和图片数据（转换后的DataURL格式）
    socket.emit('sendImage', {
      username: username,
      avatar: avatar,
      img: fr.result
    })
  }
})

// 初始化jquery-emoji插件，为表情按钮绑定点击事件，点击时配置并显示表情选择框
$('.face').on('click', function () {
  $('#content').emoji({
    button: '.face',
    showTab: false,
    animation: 'slide',
    position: 'topRight',
    icons: [
      {
        name: '表情包',
        path: 'lib/jquery-emoji/img/emoji/',
        maxNum: 16,
        excludeNums: [41, 45, 54],
        file: '.gif'
      }
    ]
  })
})