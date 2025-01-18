import os
from pathlib import Path
from django.middleware.security import SecurityMiddleware

# Build paths inside the project like this: BASE_DIR / 'subdir'.
BASE_DIR = Path(__file__).resolve().parent.parent.parent.parent

# Quick-start development settings - unsuitable for production
# See https://docs.djangoproject.com/en/4.2/howto/deployment/checklist/

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = "django-insecure-l1ce73(%8v(_r$ue*5*65@cbc^ls66pz2+gr1f&n)n(g57di4q"

# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = True

ALLOWED_HOSTS = ['*']

AUTH_USER_MODEL = 'user.User'


# Application definition
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    'channels',
    'chat',
    'manage.course',
    'manage.user',
]

MIDDLEWARE = [
    "django.middleware.security.SecurityMiddleware",
    "django.contrib.sessions.middleware.SessionMiddleware",
    "django.middleware.common.CommonMiddleware",
    "django.middleware.csrf.CsrfViewMiddleware",
    "django.contrib.auth.middleware.AuthenticationMiddleware",
    "django.contrib.messages.middleware.MessageMiddleware",
    "django.middleware.clickjacking.XFrameOptionsMiddleware",
]

ROOT_URLCONF = "cqnujx_online_platform.urls"
DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'
# 静态文件的根目录
STATIC_URL = '/static/'

# 设置静态文件目录为 frontend/static（确保目录存在）
STATICFILES_DIRS = [
    os.path.join(BASE_DIR, "frontend", "static")
]

# 在生产环境中收集静态文件时的存储位置
STATIC_ROOT = BASE_DIR / 'staticfiles'  # 这是收集到的静态文件存放位置

# 模板配置
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [
            os.path.join(BASE_DIR, "frontend", "templates"),
        ],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
            ],
        },
    },
]

WSGI_APPLICATION = "cqnujx_online_platform.wsgi.application"

# Database
# https://docs.djangoproject.com/en/4.2/ref/settings/#databases
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3',
        'NAME': BASE_DIR / 'backend/cqnujx_online_platform/db.sqlite3',
    }
}

# Password validation
# https://docs.djangoproject.com/en/4.2/ref/settings/#auth-password-validators
AUTH_PASSWORD_VALIDATORS = [
    {
        "NAME": "django.contrib.auth.password_validation.UserAttributeSimilarityValidator",
    },
    {"NAME": "django.contrib.auth.password_validation.MinimumLengthValidator",},
    {"NAME": "django.contrib.auth.password_validation.CommonPasswordValidator",},
    {"NAME": "django.contrib.auth.password_validation.NumericPasswordValidator",},
]

# 国际化设置
LANGUAGE_CODE = 'zh-hans'
TIME_ZONE = 'Asia/Shanghai'
USE_I18N = True
USE_L10N = True
USE_TZ = True

# 安全设置
CSRF_COOKIE_HTTPONLY = True  # CSRF token 设置为只读
X_FRAME_OPTIONS = 'DENY'  # 防止网页被嵌入在 iframe 中
SECURE_BROWSER_XSS_FILTER = True  # 启用浏览器的 XSS 保护
SECURE_CONTENT_TYPE_NOSNIFF = True  # 防止浏览器嗅探文件类型


# Static file# https://docs.djangoproject.com/en/4.2/howto/static-files/
#
# DEFAULT_AUTO_FIELD = "django.db.models.BigAutoField"
#
# LOGGING_CONFIG = Nones (CSS, JavaScript, Images)
ASGI_APPLICATION = 'cqnujx_online_platform.asgi.application'  # 设置 ASGI 应用程序入口


CHANNEL_LAYERS = {
    "default": {
        "BACKEND": "channels.layers.InMemoryChannelLayer"
    }
}

