# coding=utf-8

from django.shortcuts import render, redirect
from django.contrib import auth, messages
from django.contrib.auth import authenticate, login
from ..course.models import CourseTeacher, StudentScore,Course
from django.contrib.auth.decorators import login_required
from .models import User


@login_required
def index(request):
    if request.user.role == "1":  # 判断用户角色是否为学生
        return render(request, "student_index.html")  # 渲染学生首页
    elif request.user.role == "2":  # 判断用户角色是否为教师
        course_list = Course.objects.filter(name="计算机网络")  # 筛选出特定课程
        return render(request, "teacher_index.html", {"course_list": course_list})  # 渲染教师首页


def user_login(request):
    if request.method == "GET":  # GET请求，返回登录页面
        return render(request, "login.html")
    elif request.method == "POST":  # POST请求，处理登录逻辑
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(request, username=username, password=password)  # 认证用户
        if user is not None:  # 用户存在且密码正确
            login(request, user)  # 登录用户
            if user.is_admin:  # 如果是管理员（教务员）
                return redirect("/admin")  # 重定向到管理员后台
            return redirect('/')  # 重定向到主页
        else:  # 用户名或密码错误
            messages.error(request, '账号不存在或者密码错误')  # 显示错误消息
            return redirect('login')  # 重定向回登录页
    return redirect("/user/login")  # 默认跳转到登录页面


@login_required  # 需要登录才能访问
def user_logout(request):
    auth.logout(request)  # 注销用户
    return redirect("/user/login")  # 重定向到登录页面


@login_required  # 需要登录才能访问
def user_edit(request):
    if request.method == "GET":  # GET请求，渲染编辑页面
        return render(request, "student_edit.html")
    else:  # POST请求，处理用户信息更新
        name = request.POST.get("name")
        mobile = request.POST.get("mobile")
        address = request.POST.get("address")
        user = request.user  # 获取当前登录用户
        user.name = name
        user.mobile = mobile
        user.address = address
        user.save()  # 保存用户修改的信息
        return redirect("/")  # 重定向到主页


@login_required  # 需要登录才能访问
def user_query(request):
    if request.method == "GET":  # GET请求，渲染查询页面
        return render(request, "student_query.html")
    else:  # POST请求，处理学生信息查询
        number = request.POST.get("number")
        student = User.objects.filter(number=number, role=1).first()  # 查询学生
        return render(request, "student_query.html", {
            "name": student.name if student else "查询无此学生",  # 显示查询结果
            "address": student.address if student else "查询无此学生",
            "mobile": student.mobile if student else "查询无此学生",
            "username": student.username if student else "查询无此学生",
            "number": student.number if student else "查询无此学生"
        })


def user_register(request):
    if request.method == "GET":  # GET请求，渲染注册页面
        return render(request, "register.html")
    else:  # POST请求，处理注册逻辑
        number = request.POST.get("number")
        username = request.POST.get("username")
        password = request.POST.get("password")
        try:
            User.objects.create_user(number=number, username=username, password=password, is_active=False)  # 创建用户
        except Exception:
            return render(request, "system_info.html", {
                'msg': 'failed',
                'title': '错误',
                'content': '学号或用户名可能已经注册！',  # 注册失败，学号或用户名已存在
                'url': ''
            })
        return render(request, "system_info.html", {
            'msg': 'success',
            'title': '恭喜',
            'content': '注册成功！',  # 注册成功
            'url': '/user/login'
        })


@login_required  # 需要登录才能访问
def change_pwd(request):
    if request.method == "GET":  # GET请求，渲染修改密码页面
        return render(request, "change_pwd.html")
    else:  # POST请求，处理密码修改
        new_pwd = request.POST.get("password")
        request.user.set_password(new_pwd)  # 设置新密码
        request.user.save()  # 保存新密码
        return redirect("/user/logout")  # 修改后退出登录


@login_required  # 需要登录才能访问
def student_grade_query(request):
    if request.method == "GET":  # GET请求，渲染成绩查询页面
        return render(request, "student_grade_query.html")
    else:  # POST请求，处理成绩查询
        number = request.POST.get("number")
        student = User.objects.filter(number=number, role=1).first()  # 查询学生
        if not student:  # 如果学生不存在
            return render(request, "student_grade_query.html")
        all_score = StudentScore.objects.filter(student=student)  # 查询学生所有成绩
        return render(request, "student_grade_query.html", {
            "all_score": all_score  # 显示成绩
        })


@login_required  # 需要登录才能访问
def chat_index(request):
    return render(request, 'chat/index.html')  # 渲染聊天首页