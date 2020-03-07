from rest_framework import viewsets
from .models import Category, Capital, Investor, Entrepreneur, Expert, Project, Rating
from .serializer import CategorySerializer, CapitalSerializer, InvestorSerializer


class CategoryViewSet(viewsets.ModelViewSet):
    queryset = Category.objects.all()
    serializer_class = CategorySerializer


class CapitalViewSet(viewsets.ModelViewSet):
    queryset = Capital.objects.all()
    serializer_class = CapitalSerializer


class InvestorViewSet(viewsets.ModelViewSet):
    queryset = Investor.objects.all()
    serializer_class = InvestorSerializer
