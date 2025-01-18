# coding=utf-8

from django.shortcuts import render, redirect, get_object_or_404
from .models import Course, CourseStudent, StudentScore
from ..user.models import User
from django.contrib.auth.decorators import login_required

@login_required
# 教师课程管理页面
def teacher_course(request, course_id):
    # 渲染教师课程页面
    return render(request, "course_student.html", {
        "course": Course.objects.get(id=int(course_id)),  # 获取课程信息
        "students": list(CourseStudent.objects.get(course__id=int(course_id)).student.all()),  # 获取课程学生列表
    })

@login_required
# 学生选择课程页面
def course_choose(request):
    choosed = [c.course for c in request.user.course.all()]  # 获取已选课程
    for item in choosed:
        score_record = StudentScore.objects.filter(course=item, student=request.user).first()  # 获取成绩记录
        if score_record:
            setattr(item, "score", score_record.score)  # 设置成绩
        else:
            setattr(item, "score", "未出成绩")  # 设置默认成绩

    return render(request, "choose_course.html", {
        "choosed": choosed,  # 已选课程
        "unchoosed": list(set(Course.objects.all()).difference(set(choosed))),  # 未选课程
    })

@login_required
# 修改学生成绩
def change_grade(request, course_id, student_id):
    course = Course.objects.get(id=int(course_id))  # 获取课程信息
    student = User.objects.get(id=int(student_id))  # 获取学生信息
    score_record = StudentScore.objects.filter(course=course, student=student).first()  # 获取成绩记录
    if score_record:
        score = score_record.score  # 获取成绩
    else:
        score = 0  # 默认成绩为0
    if request.method == "GET":
        return render(request, "course_student_grade.html", {
            "score": score,  # 成绩
            "student": student.name,  # 学生姓名
            "course": course.name  # 课程名称
        })
    else:
        score = float(request.POST.get("score", 0))  # 获取提交的成绩
        score_record = StudentScore.objects.filter(student=student, course=course)
        if not score_record:
            score_record = StudentScore(student=student, course=course, score=score)  # 创建成绩记录
            score_record.save()
        else:
            score_record.score = score  # 更新成绩
            score_record.save()

        return render(request, "course_student_grade.html", {
            "score": score,  # 成绩
            "student": student.name,  # 学生姓名
            "course": course.name  # 课程名称
        })

@login_required
# 学生选择课程
def student_choose_course(request, course_id, student_id):
    course = get_object_or_404(Course, id=course_id)  # 获取课程信息
    student = get_object_or_404(User, id=student_id)  # 获取学生信息
    cs, created = CourseStudent.objects.get_or_create(course=course)  # 获取或创建课程学生关系
    cs.student.add(student)  # 添加学生到课程
    cs.save()
    return redirect("/course/choose")  # 重定向到选择课程页面

@login_required
# 学生取消选择课程
def student_unchoose_course(request, course_id, student_id):
    course = get_object_or_404(Course, id=course_id)  # 获取课程信息
    student = get_object_or_404(User, id=student_id)  # 获取学生信息
    cs = get_object_or_404(CourseStudent, course=course)  # 获取课程学生关系
    cs.student.remove(student)  # 从课程中移除学生
    cs.save()
    return redirect("/course/choose")  # 重定向到选择课程页面

@login_required
# 课程学生成绩页面
def course_student_grade(request, course_id):
    course = get_object_or_404(Course, id=course_id)  # 获取课程信息
    students = CourseStudent.objects.filter(course=course).values_list('student', flat=True)  # 获取课程学生ID列表
    student_list = User.objects.filter(id__in=students)  # 获取学生列表
    if request.method == "POST":
        student_id = request.POST.get("student_id")  # 获取提交的学生ID
        score = request.POST.get("score")  # 获取提交的成绩
        student = get_object_or_404(User, id=student_id)  # 获取学生信息
        score_record, _ = StudentScore.objects.get_or_create(course=course, student=student)  # 获取或创建成绩记录
        score_record.score = score  # 更新成绩
        score_record.save()
        return redirect('course_student_grade', course_id=course_id)  # 重定向到课程学生成绩页面
    return render(request, "course_student_grade.html", {
        "course": course,  # 课程信息
        "students": student_list,  # 学生列表
    })
    
@login_required
# 录入学生成绩页面
def input_grade(request, student_id):
    student = get_object_or_404(User, id=student_id)  # 获取学生信息
    course = get_object_or_404(Course, name="计算机网络")  # 获取课程信息
    score_record, created = StudentScore.objects.get_or_create(course=course, student=student)  # 获取或创建成绩记录
    
    if request.method == "POST":
        score = request.POST.get("score")  # 获取提交的成绩
        score_record.score = score  # 更新成绩
        score_record.save()
        return redirect('input_grade', student_id=student_id)  # 重定向到录入成绩页面
    
    return render(request, "course_student_grade.html", {
        "student": student.name,  # 学生姓名
        "student_id": student.id,  # 学生ID
        "score": score_record.score,  # 成绩
    })
