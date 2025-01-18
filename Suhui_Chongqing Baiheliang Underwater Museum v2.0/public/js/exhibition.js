  function showEventId(){ 
    //获取观光点的按钮
    var eventpoints = document.getElementsByClassName("buttons");
    //定义一个数组，存放已被点击的日期按钮区内容和按钮
    var shows = new Array(document.getElementById("event7"),document.getElementsByClassName("buttonsOver")[0]);
    //被修改的图片
    var changeImg;
     for(i=0;i<eventpoints.length;i++){
        //当前按钮创建一个属性存放按钮序号
        eventpoints[i].ii = i;
        eventpoints[i].onmouseover = function(){
        //如果之前已经触碰过按钮则把之前显示的内容隐藏
        if(shows != null){
            shows[0].setAttribute("style","display:none");
            shows[1].setAttribute("class","buttons");
        }
        var eventId = "event"+this.ii;
        //寻找观光点对应内容
        var event = document.getElementById(eventId);
        //显示内容
        event.setAttribute("style","");
        this.setAttribute("class","buttonsOver");
        shows[0] = event;
        shows[1] = this;
        }     
    }
}
     
window.onload = showEventId;
     
