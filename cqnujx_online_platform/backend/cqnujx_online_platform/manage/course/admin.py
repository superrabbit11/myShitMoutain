from django.contrib import admin
from .models import *


class CourseAdmin(admin.ModelAdmin):
    pass
admin.site.register(Course, CourseAdmin)


class CourseStudentAdmin(admin.ModelAdmin):
    pass
admin.site.register(CourseStudent, CourseStudentAdmin)


class CourseTeacherAdmin(admin.ModelAdmin):
    pass
admin.site.register(CourseTeacher, CourseTeacherAdmin)


class StudentScoreAdmin(admin.ModelAdmin):
    pass
admin.site.register(StudentScore, StudentScoreAdmin)