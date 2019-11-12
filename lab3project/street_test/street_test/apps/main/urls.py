from django.urls import path

from . import views

app_name = 'main'
urlpatterns = [
    path('', views.search, name='search'),
    path('<int:street_id>/', views.detail, name='detail'),
]
