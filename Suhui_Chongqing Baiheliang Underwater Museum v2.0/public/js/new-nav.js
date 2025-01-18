// 当DOM内容加载完成后执行此回调函数，这个函数主要用于实现新闻列表的分页展示及相关交互功能
document.addEventListener("DOMContentLoaded", function () {
    // 定义每页显示的新闻条目数量，这里设置为固定值10条，后续会根据这个数量来划分页面展示新闻
    const itemsPerPage = 10; 
    // 通过CSS选择器选取所有类名为'newnav'的元素内的<ul>元素下的<li>元素，且排除那些类名为'page'的元素，这些被选取的<li>元素代表新闻条目
    const newsItems = document.querySelectorAll(".newnav ul li:not(.page)"); 
    // 获取新闻条目的总数量，通过查询到的新闻条目元素列表的长度来确定一共有多少条新闻
    const totalItems = newsItems.length; 
    // 计算总页数，通过将新闻总数除以每页显示的条目数，并向上取整（使用Math.ceil函数）得到总共需要多少页来展示所有新闻
    const totalPages = Math.ceil(totalItems / itemsPerPage); 
    // 初始化当前页为第1页，后续会根据用户点击分页按钮等操作来更新这个当前页的值
    let currentPage = 1; 

    // 定义一个函数用于显示指定页面的新闻条目，根据当前页码来控制哪些新闻条目显示，哪些隐藏
    function displayPage(page) {
        // 遍历所有新闻条目元素
        newsItems.forEach((item, index) => {
            // 通过判断当前新闻条目的索引位置是否在当前页应该显示的范围内（索引范围根据每页条目数和当前页码来确定）
            // 如果在范围内，则将该新闻条目的display样式设置为'block'，使其显示出来；否则设置为'none'，将其隐藏
            item.style.display =
                index >= (page - 1) * itemsPerPage && index < page * itemsPerPage
                   ? "block"
                    : "none";
        });
    }

    // 定义一个函数用于更新分页按钮的状态，比如禁用或启用上一页、下一页按钮，以及改变按钮颜色来体现是否可点击等状态
    function updatePagination() {
        // 通过CSS选择器选取所有类名为'newnav'的元素内的<ul>元素下类名为'page'的<li>元素内的<a>链接元素，这些就是分页按钮对应的链接元素
        const pageLinks = document.querySelectorAll(".newnav ul li.page a");
        // 判断当前页是否为第1页，如果是，则禁用上一页按钮（通过设置pointerEvents为'none'，让按钮无法响应点击事件），并将按钮颜色设置为灰色体现禁用状态
        pageLinks[1].style.pointerEvents = currentPage === 1? "none" : "auto"; 
        pageLinks[1].style.color = currentPage === 1? "gray" : ""; 
        // 判断当前页是否为最后一页（总页数对应的那一页），如果是，则禁用下一页按钮（同样设置pointerEvents和改变颜色来体现禁用）
        pageLinks[2].style.pointerEvents = currentPage === totalPages? "none" : "auto"; 
        pageLinks[2].style.color = currentPage === totalPages? "gray" : ""; 
    }

    // 为各个分页按钮绑定点击事件，以实现点击分页按钮切换页面并更新页面展示和按钮状态的功能

    // 获取所有分页按钮对应的链接元素
    const pageLinks = document.querySelectorAll(".newnav ul li.page a");
    // 为首页按钮（索引为0的分页按钮链接）绑定点击事件，点击时将当前页设置为第1页，然后调用displayPage函数显示第1页的新闻条目，再调用updatePagination函数更新分页按钮状态
    pageLinks[0].addEventListener("click", () => {
        currentPage = 1;
        displayPage(currentPage);
        updatePagination();
    });

    // 为上一页按钮（索引为1的分页按钮链接）绑定点击事件，点击时先判断当前页是否大于1（不是第1页才可以点击上一页），如果是则将当前页减1，然后显示对应页面的新闻条目并更新分页按钮状态
    pageLinks[1].addEventListener("click", () => {
        if (currentPage > 1) {
            currentPage--;
            displayPage(currentPage);
            updatePagination();
        }
    });

    // 为下一页按钮（索引为2的分页按钮链接）绑定点击事件，点击时先判断当前页是否小于总页数，如果是则将当前页加1，接着显示对应页面的新闻条目并更新分页按钮状态
    pageLinks[2].addEventListener("click", () => {
        if (currentPage < totalPages) {
            currentPage++;
            displayPage(currentPage);
            updatePagination();
        }
    });

    // 为尾页按钮（索引为3的分页按钮链接）绑定点击事件，点击时将当前页设置为总页数对应的那一页，然后显示该页新闻条目并更新分页按钮状态
    pageLinks[3].addEventListener("click", () => {
        currentPage = totalPages;
        displayPage(currentPage);
        updatePagination();
    });

    // 初始化操作，在页面加载完成后，首先显示第1页的新闻条目，并更新分页按钮的初始状态
    displayPage(currentPage);
    updatePagination();
});