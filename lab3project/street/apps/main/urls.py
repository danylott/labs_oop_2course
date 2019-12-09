from django.urls import path

from . import views

app_name = 'main'
urlpatterns = [
    path('', views.search, name='search'),
    path('ajax/', views.search_ajax, name = 'search_ajax'),
    path('<int:street_id>/', views.detail, name='detail'),
]
