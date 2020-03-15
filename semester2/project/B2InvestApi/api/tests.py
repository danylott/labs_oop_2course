import json
from django.urls import reverse
from django.contrib.auth.models import User
from rest_framework.authtoken.models import Token
from rest_framework.test import APITestCase
from rest_framework import status

from .models import Category, Capital, Investor, Profile, Entrepreneur, Expert, Project, Rating
from .serializer import CategorySerializer, CapitalSerializer, InvestorSerializer, ExpertSerializer, \
    EntrepreneurSerializer, ProjectSerializer, RatingSerializer, UserSerializer


class RegistrationTestCase(APITestCase):

    def test_registration(self):
        data = {
            "username": "test",
            "password": "test",
        }
        response = self.client.post("/api/users/", data)
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)


class InvestorViewSetTestCase(APITestCase):

    list_url = reverse("investor-list")

    def setUp(self):
        self.user = User.objects.create_user(username="test",
                                             password="test")
        self.token = Token.objects.create(user=self.user)
        self.api_authentication()

        self.capital = Capital.objects.create(name="test",
                                              amount_of_money="1000-5000")
        self.investor = Investor.objects.create(user=self.user,
                                                capital=self.capital)
        category1 = Category.objects.create(name="test1")
        category2 = Category.objects.create(name="test2")
        self.categories = [category1, category2]

        self.profile = Profile.objects.create(phone="+380939501698",
                                              info="Lorem Ipsum Text")

    def api_authentication(self):
        self.client.credentials(HTTP_AUTHORIZATION="Token " + self.token.key)

    def test_investor_list_authenticated(self):
        response = self.client.get(self.list_url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_investor_list_un_authenticated(self):
        self.client.force_authenticate(user=None)
        response = self.client.get(self.list_url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_investor_detail_retreive(self):
        response = self.client.get(reverse("investor-detail", kwargs={"pk": 1}))
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.data["user"], 1)

    def test_investor_update_by_owner(self):
        response = self.client.put(reverse("investor-detail", kwargs={"pk": 1}),
                                   {"categories": self.categories})
        print(response.content)
        print("dddddddddddddddddddddddddddddddd")
        # self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(response.content),
                         {"user": 1, "categories": [1, 2], "profile": None, "capital": 1})

    def test_investor_update_by_random_user(self):
        random_user = User.objects.create_user(username="random", password="random")
        self.client.force_authenticate(user=random_user)
        response = self.client.put(reverse("investor-detail", kwargs={"pk": 1}),
                                   {"categories": self.categories, "profile": self.profile})
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)
