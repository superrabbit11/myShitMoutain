from django.shortcuts import render
from django.contrib.auth.decorators import login_required

# 首页视图
def index(request):
    return render(request, 'chat/index.html', {})


@login_required
# 房间视图，传入房间名称
def room(request, room_name):
    return render(request, 'chat/room.html', {
        'room_name': room_name,  # 房间名称
        'user_name': request.user.name if hasattr(request.user, 'name') else request.user.username  # 用户名
    })
