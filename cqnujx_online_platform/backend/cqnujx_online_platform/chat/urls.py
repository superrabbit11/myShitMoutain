from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),  # 根路径，调用index视图
    path('<str:room_name>/', views.room, name='room'),  # 带房间名的路径，调用room视图
]
