# coding=utf-8
from .models import User


class CustomAuth(object):  # 自定义认证类
    def authenticate(self, username=None, password=None):  # 认证方法
        try:
            user = User.objects.get(username=username)  # 获取用户
            if user.check_password(password):  # 检查密码是否正确
                return user
        except User.DoesNotExist:  # 用户不存在时返回None
            return None

    def get_user(self, user_id):  # 获取用户方法
        try:
            user = User.objects.get(pk=user_id)  # 根据ID获取用户
            if user.is_active:  # 如果用户激活则返回用户
                return user
            return None
        except User.DoesNotExist:  # 用户不存在时返回None
            return None