from django.contrib import admin
from .models import User

# User模型的管理界面
class UserAdmin(admin.ModelAdmin):
    list_display = ('username', 'number', 'role', 'is_active', 'is_admin')
    search_fields = ('username', 'number')

# 注册User模型管理界面
admin.site.register(User, UserAdmin)