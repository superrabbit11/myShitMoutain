# coding=utf-8


from django.db import models
from ..user.models import User

# 课程模型
class Course(models.Model):
    name = models.CharField(max_length=30, verbose_name="课程名称")
    desc = models.TextField(default="", verbose_name="课程简介", null=True, blank=True)
    enable = models.BooleanField(default=True, verbose_name="是否有效")

    class Meta:
        verbose_name = u'课程一览'
        verbose_name_plural = u'课程一览'

    def __str__(self):
        return self.name

# 学生选课信息模型，关联学生和课程
class CourseStudent(models.Model):
    student = models.ManyToManyField(User, limit_choices_to={'role': 1}, verbose_name="选课学生", related_name="course")
    course = models.ForeignKey(Course, on_delete=models.CASCADE, limit_choices_to={'enable': True}, verbose_name="课程")

    class Meta:
        verbose_name = u'学生选课信息表'
        verbose_name_plural = u'学生选课信息表'


# 教师任课信息模型，关联教师和课程
class CourseTeacher(models.Model):
    teacher = models.ManyToManyField(User, limit_choices_to={'role': 2}, verbose_name="任课教师")
    course = models.ForeignKey(Course, on_delete=models.CASCADE, limit_choices_to={'enable': True}, verbose_name="课程")

    class Meta:
        verbose_name = u'教师任课表'
        verbose_name_plural = u'教师任课表'

# 学生成绩模型，关联学生、课程和成绩
class StudentScore(models.Model):
    student = models.ForeignKey(User,on_delete=models.CASCADE,limit_choices_to={'role': 1},verbose_name="学生")
    course = models.ForeignKey(Course, on_delete=models.CASCADE, limit_choices_to={'enable': True}, verbose_name="课程")
    score = models.FloatField(default=0, verbose_name="成绩")

    def __str__(self):
        return "%s %s %s" % (self.student, self.course, self.score)

    class Meta:
        verbose_name = u'学生成绩表'
        verbose_name_plural = u'学生成绩表'
