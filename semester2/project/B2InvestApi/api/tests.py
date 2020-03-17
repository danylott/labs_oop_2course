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

        self.category1 = Category.objects.create(name="test1")
        self.category2 = Category.objects.create(name="test2")
        self.category3 = Category.objects.create(name="test3")

        self.investor = Investor.objects.create(user=self.user,
                                                capital=self.capital)

        self.investor.categories.add(self.category1)
        self.investor.categories.add(self.category2)
        self.investor.save()

        self.user2 = User.objects.create_user(username="test2", password="test2")

        self.entrepreneur = Entrepreneur.objects.create(user=self.user)

        self.project = Project.objects.create(entrepreneur=self.entrepreneur,
                                              capital=self.capital,
                                              name="Project test")

        self.project.categories.set([1, 2])

    def api_authentication(self):
        self.client.credentials(HTTP_AUTHORIZATION="Token " + self.token.key)

    def test_investor_list_authenticated(self):
        response = self.client.get(self.list_url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_investor_list_un_authenticated(self):
        self.client.force_authenticate(user=None)
        response = self.client.get(self.list_url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_investor_detail_retrieve(self):
        response = self.client.get(reverse("investor-detail", kwargs={"pk": 1}))
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.data["user"], 1)

    def test_investor_update_by_owner(self):
        response = self.client.put(reverse("investor-detail", kwargs={"pk": 1}),
                                   {"user": 1, "categories": [1], "capital": 1, "phone": "+380939501698"})
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(response.content),
                         {"id": 1, "user": 1, "image": None, "phone": "+380939501698", "info": None, "categories": [1],
                          "capital": 1, "no_of_projects": 0,"avg_rating": 0})

    def test_investor_update_by_random_user(self):
        random_user = User.objects.create_user(username="random", password="random")
        self.client.force_authenticate(user=random_user)
        response = self.client.put(reverse("investor-detail", kwargs={"pk": 1}),
                                   {"user": 1, "categories": [1], "capital": 1, "phone": "+380939501698"})
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

    def test_investor_find_projects(self):
        response = self.client.get('/api/investors/1/find_projects/')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(response.content),
                         {"message": "Projects found", "result": [
                             {"id": 1, "name": "Project test", "description": None, "image": None, "no_of_ratings": 0,
                              "avg_rating": 0, "capital": 1, "categories": [1, 2],
                              "entrepreneur": 1, "investor": None, "expert": None}]})

    def test_investor_find_projects_not_exist(self):
        self.investor.categories.set([self.category3])
        self.investor.save()
        response = self.client.get('/api/investors/1/find_projects/')
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)

    def test_investor_choose_project_exist(self):
        response = self.client.post('/api/investors/1/choose_project/', {"project": 1})
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_investor_choose_project_not_exist(self):
        response = self.client.post('/api/investors/1/choose_project/', {"project": 2})
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)


class ProjectViewSetTestCase(APITestCase):

    list_url = reverse('project-list')

    def setUp(self):
        self.user = User.objects.create_user(username="test",
                                             password="test")
        self.token = Token.objects.create(user=self.user)
        self.api_authentication()

        self.capital = Capital.objects.create(name="test",
                                              amount_of_money="1000-5000")

        self.category1 = Category.objects.create(name="test1")
        self.category2 = Category.objects.create(name="test2")
        self.category3 = Category.objects.create(name="test3")

        self.investor = Investor.objects.create(user=self.user,
                                                capital=self.capital)

        self.investor.categories.add(self.category1)
        self.investor.categories.add(self.category2)
        self.investor.save()

        self.user2 = User.objects.create_user(username="test2", password="test2")

        self.entrepreneur = Entrepreneur.objects.create(user=self.user)

        self.project = Project.objects.create(entrepreneur=self.entrepreneur,
                                              capital=self.capital,
                                              name="Project test")

        self.project.categories.set([1, 2])

        self.expert = Expert.objects.create(user=self.user, cost=1000)
        self.expert.categories.add(self.category1)
        self.expert.capitals.add(self.capital)
        self.expert.save()

    def api_authentication(self):
        self.client.credentials(HTTP_AUTHORIZATION="Token " + self.token.key)

    def test_project_list_authenticated(self):
        response = self.client.get(self.list_url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_project_list_un_authenticated(self):
        self.client.force_authenticate(user=None)
        response = self.client.get(self.list_url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_project_detail_retrieve(self):
        response = self.client.get(reverse("project-detail", kwargs={"pk": 1}))
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.data["entrepreneur"], 1)

    def test_project_update_by_owner(self):
        response = self.client.put(reverse("project-detail", kwargs={"pk": 1}),
                                   {"entrepreneur": 1, "categories": [1, 2], "capital": 1,
                                    "name": "Changed Project", "description": "Lorem Ipsum"})
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(response.content),
                         {"id": 1, "name": "Changed Project", "description": "Lorem Ipsum", "image": None,
                          "no_of_ratings": 0, "avg_rating": 0, "capital": 1, "categories": [1, 2], "entrepreneur"
                          : 1, "investor": None, "expert": None})

    def test_project_update_by_random_user(self):
        random_user = User.objects.create_user(username="random", password="random")
        self.client.force_authenticate(user=random_user)
        response = self.client.put(reverse("project-detail", kwargs={"pk": 1}),
                                   {"entrepreneur": 1, "categories": [1, 2], "capital": 1,
                                    "name": "Changed Project", "description": "Lorem Ipsum"})
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

    def test_project_find_investors(self):
        response = self.client.get('/api/projects/1/find_investors/')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(response.content),
                         {"message": "Investors found", "result": [
                             {"id": 1, "user": 1, "image": None, "phone": None, "info": None, "categories": [1, 2],
                              "capital": 1, "no_of_projects": 0, "avg_rating":0}]})

    def test_project_find_investors_not_exist(self):
        self.project.categories.set([self.category3])
        self.project.save()
        response = self.client.get('/api/projects/1/find_investors/')
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)

    def test_project_choose_expert_exist(self):
        response = self.client.post('/api/projects/1/choose_expert/', {"expert": 1})
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_project_choose_expert_not_exist(self):
        response = self.client.post('/api/projects/1/choose_expert/', {"expert": 2})
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_rate_project_by_investor(self):
        response = self.client.post('/api/projects/1/rate_project/', {"stars": 5})
        self.assertEqual(response.status_code, status.HTTP_200_OK)
