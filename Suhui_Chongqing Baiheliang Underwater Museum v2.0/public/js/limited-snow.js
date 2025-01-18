function snow() {
    //创建一片雪花的基础模板
    var flake = document.createElement('div');
    flake.innerHTML = '❅';
    flake.style.cssText = 'position:absolute;color:#fff;';

    //获取页面的高度和宽度，用于确定雪花出现的范围以及飘落的终点位置等
    //限制页面高度
    var documentHeight = 2600;
    var documentWidth = window.innerWidth;
    //定义生成一片雪花的时间间隔
    var millisec = 35; 

    //设置定时器，周期性地生成雪花
    setInterval(function () {
        var startLeft = Math.random() * documentWidth;
        var endLeft = Math.random() * documentWidth;

        //随机生成雪花的大小和透明度
        var flakeSize = 10 + 30 * Math.random();
        //起始透明度
        var startOpacity = 0.7 + 0.3 * Math.random();
        //结束透明度
        var endOpacity = 0.2 + 0.2 * Math.random();
        //雪花的下落持续时间
        var durationTime = 20000 + 12000 * Math.random();
        //克隆一个雪花模板
        var cloneFlake = flake.cloneNode(true);

        //为克隆出来的雪花设置初始样式
        cloneFlake.style.cssText += `
            left: ${startLeft}px;
            opacity: ${startOpacity};
            font-size: ${flakeSize}px;
            top: -25px;
            position: absolute;
            transition: all ${durationTime}ms linear;
        `;

        document.body.appendChild(cloneFlake);

        cloneFlake.addEventListener('transitionend', function () {
            cloneFlake.remove();
        });

        setTimeout(function () {
            cloneFlake.style.cssText += `
                left: ${endLeft}px;
                top: ${documentHeight}px;
                opacity: ${endOpacity};
            `;
        }, 0);
    }, millisec);
}
snow();