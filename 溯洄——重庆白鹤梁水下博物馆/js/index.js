window.addEventListener('load', function() {
    // 获取元素
    var arrow_l = document.querySelector('.arrow-l');
    var arrow_r = document.querySelector('.arrow-r');
    var show = document.querySelector('.show');
    var showWidth = show.offsetWidth;
    //鼠标经过show 就显示隐藏左右按钮
    show.addEventListener('mouseenter', function() {
        arrow_l.style.display = 'block';
        arrow_r.style.display = 'block';
        clearInterval(timer);
        timer = null; // 清除定时器变量
    });
    show.addEventListener('mouseleave', function() {
        arrow_l.style.display = 'none';
        arrow_r.style.display = 'none';
        timer = setInterval(function() {
            //手动调用点击事件
            arrow_r.click();
        }, 2000);
    });
    //有几张图片，我就生成几个小圆圈
    var ul = show.querySelector('ul');
    var ol = show.querySelector('.circle');
    // console.log(ul.children.length);
    for (var i = 0; i < ul.children.length; i++) {
        // 创建一个小li 
        var li = document.createElement('li');
        li.setAttribute('index', i);
        ol.appendChild(li);
        //我们可以直接在生成小圆圈的同时直接绑定点击事件
        li.addEventListener('click', function() {
            for (var i = 0; i < ol.children.length; i++) {
                ol.children[i].className = '';
            }
            //当前的小li 设置current 类名
            this.className = 'current';
            // 当我们点击了某个小li 
            var index = this.getAttribute('index');
            num = index;
            circle = index;
            // num = circle = index;
            console.log(showWidth);
            console.log(index);

            animate(ul, -index * showWidth);
        })
    }
    ol.children[0].className = 'current';
    var first = ul.children[0].cloneNode(true);
    ul.appendChild(first);
    var num = 0;
    var circle = 0;
    var flag = true;
    arrow_r.addEventListener('click', function() {
        if (flag) {
            flag = false;
            if (num == ul.children.length - 1) {
                ul.style.left = 0;
                num = 0;
            }
            num++;
            animate(ul, -num * showWidth, function() {
                flag = true; 
            });
            // 点击右侧按钮，小圆圈跟随一起变化 
            circle++;
            if (circle == ol.children.length) {
                circle = 0;
            }
            circleChange();
        }
    });

    // 左侧按钮做法（基本与上方相同，不再赘述）
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
            circle = circle < 0 ? ol.children.length - 1 : circle;
            circleChange();
        }
    });

    function circleChange() {
        for (var i = 0; i < ol.children.length; i++) {
            ol.children[i].className = '';
        }
		
        ol.children[circle].className = 'current';
    }
    //自动播放轮播图
    var timer = setInterval(function() {
        //手动调用点击事件
        arrow_r.click();
    }, 2000);

})