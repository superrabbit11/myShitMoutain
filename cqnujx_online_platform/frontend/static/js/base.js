// 跳转到指定 URL，支持弹出提示框确认
function goToUrl(url, msg) {
    // 如果没有提示信息，直接跳转
    if (msg == null) {
        window.location.href = url;
        return;
    }
    // 如果有提示信息，弹出确认框
    if (msg != "") {
        if (window.confirm(msg)) {
            window.location.href = url;
            return;
        } else {
            return;
        }
    }
    // 如果没有提示，直接跳转
    window.location.href = url;
}

// 发送 Ajax 请求的通用函数
function AjaxSender(urlStr, methodStr, successFun, errorFun, jsonData) {
    $.ajax({
        url: urlStr,
        beforeSend: function (xhr) {
            // 设置请求头
            xhr.setRequestHeader("X-CSRFTOKEN", $.cookie('csrftoken'));
            xhr.setRequestHeader("auth-token", $.cookie('auth-token'));
        },
        type: methodStr, // 请求方法
        data: jsonData,  // 请求数据
        crossDomain: false,
        error: errorFun, // 错误回调
        success: successFun, // 成功回调
        dataType: 'json' // 数据类型
    });
}

// 发送 GET 请求
function EzAjaxGet(url, success, failed) {
    failed = failed || function (data) {
        console.log(data);
    };
    AjaxSender(url, "get", success, failed);
}

// 发送 PUT 请求
function EzAjaxPut(url, json_param, success, failed) {
    failed = failed || function (data) {
        console.log(data);
    };
    AjaxSender(url, "put", success, failed, json_param);
}

// 发送 POST 请求
function EzAjaxPost(url, json_param, success, failed) {
    failed = failed || function (data) {
        console.log(data);
    };
    AjaxSender(url, "post", success, failed, json_param);
}

// 发送 DELETE 请求
function EzAjaxDelete(url, success, failed) {
    failed = failed || function (data) {
        console.log(data);
    };
    AjaxSender(url, "delete", success, failed);
}

// 判断对象是否为空
function isNone(obj) {
    return obj == "" || obj == null || obj == undefined || obj == {};
}

// 获取 URL 中的参数值
function getUrlParam(name) {
    var reg = new RegExp("(^|&)"+ name +"=([^&]*)(&|$)");
    var r = window.location.search.substr(1).match(reg);
    if (r != null) return unescape(r[2]);
    return null;
}

// 格式化日期
Date.prototype.Format = function (fmt) {
    var o = {
        "M+": this.getMonth() + 1, //月份
        "d+": this.getDate(), //日
        "h+": this.getHours(), //小时
        "m+": this.getMinutes(), //分
        "s+": this.getSeconds(), //秒
        "q+": Math.floor((this.getMonth() + 3) / 3), //季度
        "S": this.getMilliseconds() //毫秒
    };
    if (/(y+)/.test(fmt)) fmt = fmt.replace(RegExp.$1, (this.getFullYear() + "").substr(4 - RegExp.$1.length));
    for (var k in o)
        if (new RegExp("(" + k + ")").test(fmt))
            fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
    return fmt;
};

