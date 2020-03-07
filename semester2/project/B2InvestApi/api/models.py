from django.db import models
from django.contrib.auth.models import User
from django.core.validators import MinValueValidator, MaxValueValidator


class Category(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)

    def __str__(self):
        return self.name


class Capital(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    amount_of_money = models.CharField(max_length=100, null=False, blank=False)

    def __str__(self):
        return self.amount_of_money


class Investor(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, null=False, blank=False)
    categories = models.ManyToManyField(Category, related_name='investor_categories')
    capital = models.ForeignKey(Capital, on_delete=models.DO_NOTHING)

    def __str__(self):
        return self.user.name


class Entrepreneur(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, null=False, blank=False)

    def __str__(self):
        return self.user.name


class Expert(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, null=False, blank=False)
    categories = models.ManyToManyField(Category, related_name='expert_categories')
    capital = models.ManyToManyField(Capital, related_name='capitals')

    def __str__(self):
        return self.user.name


class Project(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    description = models.TextField(null=True, blank=True)
    image = models.ImageField(upload_to="images/projects/", null=True, blank=True)
    entrepreneur = models.ForeignKey(Entrepreneur, on_delete=models.CASCADE, null=False, blank=False)
    investor = models.ForeignKey(Investor, on_delete=models.DO_NOTHING, null=True, blank=True)
    expert = models.ForeignKey(Expert, on_delete=models.DO_NOTHING, null=True, blank=True)

    def __str__(self):
        return self.name


class Rating(models.Model):
    project = models.ForeignKey(Project, on_delete=models.CASCADE, null=False, blank=False)
    user = models.ForeignKey(User, on_delete=models.CASCADE, null=False, blank=False)
    stars = models.IntegerField(validators=[MinValueValidator(1), MaxValueValidator(5)])

    class Meta:
        unique_together = (('user', 'project'),)
        index_together = (('user', 'project'),)

    def __str__(self):
        return self.stars


class Article(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    description = models.TextField(null=True, blank=True)
    image = models.ImageField(upload_to="images/articles/", null=True, blank=True)


class Release(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    description = models.TextField(null=True, blank=True)
    image = models.ImageField(upload_to="images/releases/", null=True, blank=True)
