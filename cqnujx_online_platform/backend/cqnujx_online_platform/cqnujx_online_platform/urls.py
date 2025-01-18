"""
URL configuration for cqnujx_online_platform project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include
from manage.user.views import user_login, index, user_logout, user_edit, user_query, user_register, change_pwd, student_grade_query, chat_index
from manage.course.views import teacher_course, change_grade, course_choose, student_choose_course, student_unchoose_course, course_student_grade, input_grade
from django.conf import settings
from django.conf.urls.static import static
from chat import views as chat_views

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', index, name='index'),
    path('user/login/', user_login, name='login'),
    path('accounts/login/', user_login, name='accounts_login'),
    path('user/logout/', user_logout),
    path('user/change-pwd/', change_pwd),
    path('user/query/', user_query),
    path('user/edit-info/', user_edit),
    path('user/query/grade/', student_grade_query),
    path('user/register/', user_register),
    path('course/<int:course_id>/', teacher_course),
    path('course/choose/', course_choose),
    path('course/<int:course_id>/<int:student_id>/change-grade/', change_grade),
    path('course/<int:course_id>/<int:student_id>/add/', student_choose_course, name='student_choose_course'),
    path('course/<int:course_id>/<int:student_id>/delete/', student_unchoose_course, name='student_unchoose_course'),
    path('course/<int:course_id>/grade/', course_student_grade, name='course_student_grade'),
    path('input_grade/<int:student_id>/', input_grade, name='input_grade'),
    path('chat/', include('chat.urls')),
    path('chat/index/', chat_index, name='chat_index'),
    path('chat/room/cs/', chat_views.room, {'roomName': 'cs'}, name='chat_room_default'),
] + static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)
