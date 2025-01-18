// 设置随机出现的文字数组
// 这个数组存放了多条诗句（或优美的语句），后续会随机从中选取一条显示在页面上
var arr = [
    "春日游，杏花吹满头，陌上谁家年少，足风流",
    "当时年少春衫薄，骑马倚斜桥，满楼红袖招",
    "立如芝兰玉树，笑如朗月入怀",
    "且将新火试新茶，诗酒趁年华",
    "才子词人，自是白衣卿相",
    "银鞍照白马,飒沓如流星",
    "玉堂金马，正年少归来，风流如画",
    "宣父犹能畏后生，丈夫未可轻年少",
    "欲买桂花同载酒，终不似，少年游",
    "一点浩然气，千里快哉风",
    "须知少时拏云志，曾许人间第一流",
    "愿如风有信，长与日俱中",
    "少年心事当拏云，谁念幽寒坐呜呃",
    "会当凌绝顶，一览众山小",
    "春风得意马蹄疾，一日看尽长安花",
    "长风破浪会有时，直挂云帆济沧海",
    "乘风好去，长空万里，直下看山河" 
];

// 为整个文档添加点击事件监听器，当在页面上任意位置点击时，会执行以下回调函数内的逻辑
document.addEventListener("click", function (event) {
    // 获取页面的宽度，即浏览器可视区域的宽度（不包含滚动条等额外宽度），用于确定文字显示的横向边界范围
    var pageWidth = document.documentElement.clientWidth;
    // 获取页面的高度，即浏览器可视区域的高度（不包含滚动条等额外高度），用于确定文字显示的纵向边界范围
    var pageHeight = document.documentElement.clientHeight;
    // 获取页面在水平方向上的滚动偏移量，考虑了不同浏览器获取方式（window.scrollX 或 document.documentElement.scrollLeft），用于准确计算文字的显示位置
    var scrollX = window.scrollX || document.documentElement.scrollLeft;
    // 获取页面在垂直方向上的滚动偏移量，同样考虑不同浏览器获取方式（window.scrollY 或 document.documentElement.scrollTop），用于准确计算文字的显示位置
    var scrollY = window.scrollY || document.documentElement.scrollTop;

    // 创建一个新的 span 元素，后续将用这个元素来承载并显示随机选取的诗句内容
    var span = document.createElement("span");

    // 设置随机的诗句
    // 通过生成一个随机索引（在数组长度范围内），从预先定义的诗句数组中选取一条诗句，并设置为 span 元素的内容（innerHTML）
    span.innerHTML = arr[Math.floor(Math.random() * arr.length)];

    // 确定显示位置，避免超出页面边界
    // 计算文字在水平方向上的初始显示位置，基于鼠标点击的横坐标位置（event.clientX）加上页面的水平滚动偏移量（scrollX），再往右偏移 10px，使得文字出现在鼠标点击位置的右侧一点
    var x = event.clientX + scrollX + 10; 
    // 计算文字在垂直方向上的初始显示位置，基于鼠标点击的纵坐标位置（event.clientY）加上页面的垂直滚动偏移量（scrollY），再往下偏移 10px，使得文字出现在鼠标点击位置的下方一点
    var y = event.clientY + scrollY + 10; 

    // 判断如果按照上述计算的水平位置加上大致的文字宽度（这里假设文字宽度约为 200px）会超出页面宽度（考虑滚动偏移后的实际页面宽度）
    if (x + 200 > pageWidth + scrollX) { 
        // 则将水平位置调整为页面宽度内的最大位置，即页面宽度（包含滚动偏移后的实际宽度）减去文字大致宽度，确保文字在页面内显示
        x = pageWidth + scrollX - 200;  
    }
    // 判断如果按照上述计算的垂直位置加上大致的文字高度（这里假设文字高度约为 20px）会超出页面高度（考虑滚动偏移后的实际页面高度）
    if (y + 20 > pageHeight + scrollY) { 
        // 则将垂直位置调整为页面高度内的最大位置，即页面高度（包含滚动偏移后的实际高度）减去文字高度，确保文字在页面内显示
        y = pageHeight + scrollY - 20;  
    }

    // 设置 span 元素的定位方式为绝对定位，这样才能通过设置 left 和 top 属性来精确控制它在页面上的位置
    span.style.position = "absolute";
    // 设置 span 元素在页面上的水平位置，将之前计算好的 x 坐标值（单位为像素）赋给 left 属性
    span.style.left = x + "px";
    // 设置 span 元素在页面上的垂直位置，将之前计算好的 y 坐标值（单位为像素）赋给 top 属性
    span.style.top = y + "px";

    // 添加样式
    // 设置文字颜色为一种带有透明度的蓝色（#0057b3c3），使文字看起来更美观且有一定的通透感
    span.style.color = "#0057b3c3";
    // 设置文字大小为 20 像素，控制文字显示的大小规格
    span.style.fontSize = "20px";
    // 设置文字不进行换行显示，保证诗句以一行的形式展示，避免换行影响美观和阅读体验
    span.style.whiteSpace = "nowrap"; 
    // 设置文字初始透明度为 1，即完全不透明，正常显示
    span.style.opacity = "1";
    // 设置元素的过渡动画效果，在后续改变样式属性（如透明度、位置等）时会以 1.5 秒的时长、ease-out（缓出）的方式进行平滑过渡，让动画看起来更自然流畅
    span.style.transition = "all 1.5s ease-out"; 
    // 设置元素的堆叠顺序（z-index）为 9999，确保文字元素显示在页面其他元素之上，避免被遮挡
    span.style.zIndex = "9999";

    // 添加到页面中
    // 将设置好样式和内容的 span 元素添加到页面的 <body> 元素内，使其在页面上显示出来
    document.body.appendChild(span);

    // 添加动画效果
    // 使用 setTimeout 设置一个定时器，延迟 100 毫秒后执行以下函数内的逻辑，用于实现文字出现后的动画效果
    setTimeout(function () {
        // 改变 span 元素的样式，使其在垂直方向上向上移动 50px（通过设置 translateY 变换属性），模拟文字向上飘走的动画效果
        span.style.transform = "translateY(-50px)"; 
        // 同时将文字的透明度逐渐变为 0，使其慢慢消失，与向上移动的动画配合，实现渐变消失的效果
        span.style.opacity = "0"; 
    }, 100);

    // 动画结束后移除元素
    // 使用 setTimeout 设置另一个定时器，延迟 1600 毫秒后执行以下函数内的逻辑，在文字动画效果（向上移动并渐变消失）结束后，将 span 元素从页面中移除，避免元素一直留在页面上占用资源
    setTimeout(function () {
        document.body.removeChild(span);
    }, 1600);
});