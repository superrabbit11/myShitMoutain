//尝试从localStorage中获取名为'comments'的数据，并进行相应处理
const loadComments = () => {
    try {
        const data = localStorage.getItem('comments');
        if (data) {
            return JSON.parse(data); 
        } else {
            return []; 
        }
    } catch (error) {
        console.error('Error loading comments from localStorage:', error);
        return []; 
    }
};

// 接收一个留言数据数组作为参数
const saveComments = (comments) => {
    try {
        localStorage.setItem('comments', JSON.stringify(comments)); 
    } catch (error) {
        // 如果在保存数据过程中出现错误，在控制台打印错误信息
        console.error('Error saving comments to localStorage:', error);
    }
};

// 调用loadComments函数加载留言列表数据，将获取到的数据赋值给commentslist变量
let commentslist = loadComments();

const commentsBox = document.querySelector('#commentslist');
const btnSubmit = document.querySelector('#btn-submit');
let nameInput = document.querySelector('#name');
let commentInput = document.querySelector('#comment');

// 渲染留言到页面
// 接收一个留言列表数据（包含留言对象的数组）作为参数，用于将留言展示在页面上
const renderComments = (commentslist) => {
    commentsBox.innerHTML = ""; 

    // 遍历留言列表中的每一条留言数据（每个元素是一个留言对象）
    commentslist.forEach((item) => {
        commentsBox.insertAdjacentHTML(
            'beforeend',
            `<hr>
            <h4>
                <span>${item.name}</span>
                <span class="date">${item.time}</span>
            </h4>
            <p>${item.comment1}</p>`
        );
    });
};

//将加载好的留言列表数据渲染到页面上，展示初始的留言内容
renderComments(commentslist);


btnSubmit.onclick = function () {
    // 获取昵称输入框中的值
    let nameStr = nameInput.value.replace(/<(\/?\w+)>/g, "&lt;$1&gt;");
    // 获取留言内容输入框中的值
    let commentStr = commentInput.value.replace(/<(\/?\w+)>/g, "&lt;$1&gt;");

    // 检查昵称和留言内容输入框是否都填写了内容
    if (nameStr!== "" && commentStr!== "") {
        // 创建一个新的留言对象，包含昵称、留言内容以及当前时间
        const newComment = {
            name: nameStr,
            comment1: commentStr,
            time: new Date().toLocaleString(), 
        };

        // 将新创建的留言对象添加到留言列表的头部
        commentslist.unshift(newComment);

        //将更新后的留言列表数据保存到localStorage中
        saveComments(commentslist);

        //重新渲染页面，将包含新留言的列表展示出来
        renderComments(commentslist);

        // 清空昵称输入框和留言内容输入框的值，方便用户继续输入新的留言
        commentInput.value = "";
        nameInput.value = "";
    } else {
        alert('请输入昵称和内容！');
    }
};