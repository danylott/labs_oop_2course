
import json
from django.urls import reverse
from django.contrib.auth.models import User
from rest_framework.authtoken.models import Token
from rest_framework.test import APITestCase
from rest_framework import status

from .serializer import ProfileSerializer
from .models import Project, Capital, Entrepreneur, Profile


class RegistrationTestCase(APITestCase):

    def test_registration(self):
        data = {
            "username": "test",
            "password": "test",
        }
        response = self.client.post("/api/users/", data)
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
