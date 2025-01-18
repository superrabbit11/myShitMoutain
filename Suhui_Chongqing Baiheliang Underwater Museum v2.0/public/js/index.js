window.addEventListener('load', function() {
    var arrow_l = document.querySelector('.arrow-l');
    var arrow_r = document.querySelector('.arrow-r');
    var show = document.querySelector('.show');
    var showWidth = show.offsetWidth;

    // 当鼠标进入轮播图展示区域时触发的事件处理函数
    show.addEventListener('mouseenter', function() {
        arrow_l.style.display = 'block';
        arrow_r.style.display = 'block';
        clearInterval(timer);
        timer = null; // 清除定时器变量，避免内存泄漏等问题
    });

    // 当鼠标离开轮播图展示区域时触发的事件处理函数
    show.addEventListener('mouseleave', function() {
        arrow_l.style.display = 'none';
        arrow_r.style.display = 'none';
        timer = setInterval(function() {
            // 手动触发右箭头按钮的点击事件，模拟用户点击来切换到下一张图片，实现自动播放
            arrow_r.click();
        }, 2000);
    });

    // 根据轮播图中图片列表（ul）的子元素数量来生成对应的小圆圈
    var ul = show.querySelector('ul');
    var ol = show.querySelector('.circle');
    // 循环创建小圆圈（li元素）并添加到对应的父元素（ol）中，同时为每个小圆圈绑定点击事件
    for (var i = 0; i < ul.children.length; i++) {
        // 创建一个新的li元素，用于作为小圆圈
        var li = document.createElement('li');
        // 为新创建的小圆圈li元素设置自定义属性index，值为当前循环的索引，方便后续获取对应的图片索引
        li.setAttribute('index', i);
        ol.appendChild(li);

        // 为每个新创建的小圆圈li元素绑定点击事件处理函数
        li.addEventListener('click', function() {
            for (var i = 0; i < ol.children.length; i++) {
                ol.children[i].className = '';
            }
            this.className = 'current';
            var index = this.getAttribute('index');
            num = index;
            circle = index;
            num = circle = index; 
            console.log(showWidth);
            console.log(index);
            animate(ul, -index * showWidth);
        })
    }

    // 默认将第一个小圆圈设置为选中状态
    ol.children[0].className = 'current';

    // 克隆轮播图图片列表（ul）中的第一个元素（通常是第一张图片），并添加到列表末尾
    var first = ul.children[0].cloneNode(true);
    ul.appendChild(first);

    var num = 0;
    var circle = 0;
    var flag = true;

    // 为轮播图的右箭头按钮绑定点击事件处理函数，用于切换到下一张图片并更新相关状态
    arrow_r.addEventListener('click', function() {
        if (flag) {
            flag = false;
            // 如果当前显示的是最后一张图片
            if (num == ul.children.length - 1) {
                // 将图片列表的left样式属性设置为0，实现无缝切换
                ul.style.left = 0;
                num = 0;
            }
            num++;
            // 调用animate函数实现图片切换动画效果，切换完成后恢复flag为true，允许下次点击操作
            animate(ul, -num * showWidth, function() {
                flag = true; 
            });
            // 点击右侧按钮后，小圆圈也要跟随一起变化，更新小圆圈的索引
            circle++;
            if (circle == ol.children.length) {
                circle = 0;
            }
            circleChange();
        }
    });

    // 为轮播图的左箭头按钮绑定点击事件处理函数，用于切换到上一张图片并更新相关状态
    arrow_l.addEventListener('click', function() {
        if (flag) {
            flag = false;
            if (num == 0) {
                num = ul.children.length - 1;
                ul.style.left = -num * showWidth + 'px';
            }
            num--;
            animate(ul, -num * showWidth, function() {
                flag = true;
            });
            circle--;
            circle = circle < 0? ol.children.length - 1 : circle;
            circleChange();
        }
    });

    // 定义一个函数用于更新小圆圈的显示状态，将当前对应的小圆圈设置为选中状态
    function circleChange() {
        for (var i = 0; i < ol.children.length; i++) {
            ol.children[i].className = '';
        }
        ol.children[circle].className = 'current';
    }

    // 设置自动播放定时器，每隔2000毫秒手动触发一次右箭头按钮的点击事件，实现轮播图自动播放
    var timer = setInterval(function() {
        // 手动调用右箭头按钮的点击事件，模拟用户点击切换到下一张图片，实现自动播放功能
        arrow_r.click();
    }, 2000);

})