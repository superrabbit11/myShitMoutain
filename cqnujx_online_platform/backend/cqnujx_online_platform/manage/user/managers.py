# coding=utf-8

from django.contrib.auth.models import BaseUserManager


class UserManager(BaseUserManager):  # 自定义用户管理类
    """通过用户名，密码创建用户"""

    def create_user(self, number, username, password, **kwargs):  # 创建普通用户
        if not number:  # 学号不能为空
            raise ValueError(u'用户必须要有学号')
        if not username:  # 用户名不能为空
            raise ValueError(u'用户必须要有用户名')
        user = self.model(number=number, username=username)
        user.set_password(password)  # 设置密码
        user.is_active = True  # 激活用户
        if kwargs:
            user.role = kwargs.get('role', 1)
        user.save(using=self._db)
        return user

    def create_superuser(self, number, username, password):  # 创建超级管理员
        user = self.create_user(number=number, username=username, password=password)
        user.is_admin = True  # 设置管理员权限
        user.save(using=self._db)
        return user
