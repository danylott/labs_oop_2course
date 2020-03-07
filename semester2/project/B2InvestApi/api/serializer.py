from rest_framework import serializers
from rest_framework.relations import PrimaryKeyRelatedField

from .models import Category, Capital, Investor, Entrepreneur, Expert, Project, Rating


class CategorySerializer(PrimaryKeyRelatedField, serializers.ModelSerializer):
    class Meta:
        model = Category
        fields = ('id', 'name')


class CapitalSerializer(serializers.ModelSerializer):
    class Meta:
        model = Capital
        fields = ('id', 'name', 'amount_of_money')


class InvestorSerializer(serializers.ModelSerializer):
    investor_categories = CategorySerializer(many=True, queryset=Category.objects.all()
                                             , source='categories')

    class Meta:
        model = Investor
        fields = ('id', 'user', 'investor_categories', 'capital')
