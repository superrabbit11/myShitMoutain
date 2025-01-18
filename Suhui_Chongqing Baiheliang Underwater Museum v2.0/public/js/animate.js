function animate(obj, target, callback) {
    // 先清除以前的定时器，只保留当前的一个定时器
    clearInterval(obj.timer);
    obj.timer = setInterval(function() {
        // 步长值写到定时器的里面
        // 把步长值改为整数
        var step = (target - obj.offsetLeft) / 10;
        step = step > 0 ? Math.ceil(step) : Math.floor(step);
        if (obj.offsetLeft == target) {
            // 停止定时器
            clearInterval(obj.timer);
            // 回调函数写到定时器结束里面
            callback && callback();
        }
        // 把这个步长值改为一个慢慢变小的值
        obj.style.left = obj.offsetLeft + step + 'px';

    }, 15);
}