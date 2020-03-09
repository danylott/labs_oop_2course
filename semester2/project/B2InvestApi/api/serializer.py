from django.contrib.auth.models import User
from rest_framework import serializers
from rest_framework.authtoken.models import Token

from .models import Category, Capital, Investor, Entrepreneur, Expert, Project, Rating


class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ('id', 'username', 'password')
        extra_kwargs = {'password': {'write_only': True, 'required': True}}

    def create(self, validated_data):
        user = User.objects.create_user(**validated_data)
        Token.objects.create(user=user)
        return user


class CategorySerializer(serializers.ModelSerializer):
    class Meta:
        model = Category
        fields = ('id', 'name')


class CapitalSerializer(serializers.ModelSerializer):
    class Meta:
        model = Capital
        fields = ('id', 'name', 'amount_of_money')


class InvestorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Investor
        fields = ('id', 'user', 'categories', 'capital', 'no_of_projects', 'avg_rating')


class EntrepreneurSerializer(serializers.ModelSerializer):
    class Meta:
        model = Entrepreneur
        fields = ('id', 'user')


class ExpertSerializer(serializers.ModelSerializer):

    class Meta:
        model = Expert
        fields = ('id', 'user', 'categories', 'capitals')


class ProjectSerializer(serializers.ModelSerializer):
    class Meta:
        model = Project
        fields = ('id', 'name', 'description', 'image', 'no_of_ratings', 'avg_rating',
                  'capital', 'categories', 'entrepreneur', 'investor', 'expert')


class RatingSerializer(serializers.ModelSerializer):
    class Meta:
        model = Rating
        fields = ('id', 'project', 'user', 'stars')
