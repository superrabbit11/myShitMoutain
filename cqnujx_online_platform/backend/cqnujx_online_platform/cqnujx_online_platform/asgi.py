import os
from channels.auth import AuthMiddlewareStack
from channels.routing import ProtocolTypeRouter, URLRouter
from django.core.asgi import get_asgi_application
import backend.cqnujx_online_platform.chat.routing

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'cqnujx_online_platform.settings')

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": AuthMiddlewareStack(
        URLRouter(
            backend.cqnujx_online_platform.chat.routing.websocket_urlpatterns
        )
    ),
})
