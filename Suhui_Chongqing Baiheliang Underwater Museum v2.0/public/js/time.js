$(function () {
    // 存储定时器的标识
    var order_time = null;

    // 时间计算函数
    function endTime(endDate) {
        // 给定结束时间与当前时间之间的时间差
        var leftTime = (new Date(endDate)) - new Date(); 
        // 计算剩余的天数
        var days = parseInt(leftTime / 1000 / 60 / 60 / 24, 10); 
        // 计算剩余的小时数
        var hours = parseInt(leftTime / 1000 / 60 / 60 % 24, 10); 
        // 计算剩余的分钟数
        var minutes = parseInt(leftTime / 1000 / 60 % 60, 10);
        // 计算剩余的秒数
        var seconds = parseInt(leftTime / 1000 % 60, 10);

        //对计算得到的天、小时、分钟、秒进行格式化处理
        days = checkTime(days);
        hours = checkTime(hours);
        minutes = checkTime(minutes);
        seconds = checkTime(seconds);

        if (days >= 0 || hours >= 0 || minutes >= 0 || seconds >= 0) {
            $("p.day").text(days);
            $("p.hour").text(hours);
            $("p.min").text(minutes);
            $("p.sec").text(seconds);
        }
    }

    // 格式化时间的函数
    function checkTime(i) {
        // 如果传入的数字小于 10，就在其前面添加 '0'
        if (i < 10) {
            i = "0" + i;
        }
        // 返回格式化后的时间数字
        return i;
    }

    // 刷新时间
    function runTime(time) {
        var futureDate = new Date(time);
        order_time = setInterval(function () { endTime(futureDate) }, 1000);
    }

    $(function () {
        // 定义一个未来时间的字符串，格式为 'YYYY-MM-DD HH:mm:ss'
        var futureTime = "2025-1-29 09:00:00";
        // 传入设定好的未来时间，启动定时器开始倒计时并更新时间显示
        runTime(futureTime);
        // 提示用户倒计时对应的目标时间
        $(".tips").text(futureTime);
    });
});