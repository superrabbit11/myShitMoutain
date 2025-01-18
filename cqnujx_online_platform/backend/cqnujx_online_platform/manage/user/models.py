# coding=utf-8


from django.db import models
from django.contrib.auth.models import AbstractBaseUser
from .managers import UserManager
from django.db.models.signals import pre_save
from django.dispatch import receiver


# coding=utf-8

from django.db import models
from django.contrib.auth.models import AbstractBaseUser  # 导入AbstractBaseUser类，作为自定义用户模型的基类
from .managers import UserManager  # 导入自定义的用户管理器
from django.db.models.signals import pre_save  # 导入pre_save信号，在保存前触发
from django.dispatch import receiver  # 导入接收器，用于接收信号

class User(AbstractBaseUser):  # 自定义用户模型，继承AbstractBaseUser
    # 定义角色常量
    ROLES = (
        ("1", "学生"),
        ("2", "教师"),
        ("3", "教务员"),
    )

    # 定义用户模型字段
    username = models.CharField(max_length=30, verbose_name="用户名", unique=True, null=False)  # 用户名
    number = models.CharField(max_length=15, verbose_name="学号", unique=True, null=False)  # 学号
    role = models.CharField(max_length=1, choices=ROLES, default=1, verbose_name="角色")  # 角色
    name = models.CharField(max_length=30, verbose_name="姓名")  # 姓名
    address = models.CharField(max_length=100, verbose_name="居住地址", null=True, blank=True)  # 居住地址
    birthday = models.DateField(null=True, verbose_name="出生年月", blank=True)  # 出生日期
    mobile = models.CharField(max_length=20, null=True, blank=True)  # 手机号
    is_active = models.BooleanField(verbose_name="是否激活", default=False)  # 用户是否激活
    is_superuser = models.BooleanField(verbose_name="超级用户", default=False)  # 是否为超级用户
    is_admin = models.BooleanField(verbose_name="管理员", default=False)  # 是否为管理员

    objects = UserManager()  # 使用自定义的UserManager来管理用户

    USERNAME_FIELD = 'number'  # 用学号作为登录的字段
    REQUIRED_FIELDS = ['username']  # 必填字段，注册时必须提供用户名

    def has_perm(self, perm, obj=None):  # 判断用户是否拥有指定权限
        return True  # 简化处理，直接返回True

    def has_module_perms(self, app_label):  # 判断用户是否有权限查看指定app
        return True  # 简化处理，直接返回True

    @property
    def is_staff(self):  # 判断用户是否为工作人员
        return self.is_admin  # 只有管理员才是工作人员

    def __str__(self):  # 返回用户的显示名称，优先显示姓名
        return self.name or self.username

    def __unicode__(self):
        return self.username if not self.nickname else self.nickname

    class Meta:
        verbose_name = u'用户'  # 在后台显示的模型名称
        verbose_name_plural = u'用户表'  # 在后台显示的模型复数名称


@receiver(pre_save, sender=User)  # 在保存User模型之前触发信号
def comment_after(sender, instance, **kwargs):  # 修改角色为教务员时自动设置为管理员
    if instance.role == "3":
        instance.is_admin = True  # 如果角色是教务员，设置为管理员
    else:
        instance.is_admin = False  # 否则，不是管理员
