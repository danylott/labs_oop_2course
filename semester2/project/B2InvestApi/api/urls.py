from django.urls import path
from django.conf.urls import include

from rest_framework import routers

from .views import CategoryViewSet, CapitalViewSet, InvestorViewSet, EntrepreneurViewSet, ExpertViewSet,\
    ProjectViewSet, RatingViewSet, UserViewSet


router = routers.DefaultRouter()
router.register('users', UserViewSet)
router.register('category', CategoryViewSet)
router.register('capital', CapitalViewSet)
router.register('investor', InvestorViewSet)
router.register('entrepreneur', EntrepreneurViewSet)
router.register('expert', ExpertViewSet)
router.register('project', ProjectViewSet)
router.register('rating', RatingViewSet)


urlpatterns = [
    path('', include(router.urls)),
]