from django.urls import path
from django.conf.urls import include

from rest_framework import routers

from .views import CategoryViewSet, CapitalViewSet, InvestorViewSet


router = routers.DefaultRouter()
router.register('category', CategoryViewSet)
router.register('capital', CapitalViewSet)
router.register('investor', InvestorViewSet)


urlpatterns = [
    path('', include(router.urls)),
]