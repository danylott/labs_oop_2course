from django.urls import path
from django.conf.urls import include

from rest_framework import routers

from .views import CategoryViewSet, CapitalViewSet, InvestorViewSet, EntrepreneurViewSet, ExpertViewSet,\
    ProjectViewSet, RatingViewSet, UserViewSet


router = routers.DefaultRouter()
router.register('users', UserViewSet)
router.register('categories', CategoryViewSet)
router.register('capitals', CapitalViewSet)
router.register('investors', InvestorViewSet)
router.register('entrepreneurs', EntrepreneurViewSet)
router.register('experts', ExpertViewSet)
router.register('projects', ProjectViewSet)
router.register('ratings', RatingViewSet)


urlpatterns = [
    path('', include(router.urls)),
]