from django.db import models
from django.contrib.auth.models import User
from django.core.validators import MinValueValidator, MaxValueValidator

from phonenumber_field.modelfields import PhoneNumberField


class Category(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)

    def __str__(self):
        return self.name


class Capital(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    amount_of_money = models.CharField(max_length=100, null=False, blank=False)

    def __str__(self):
        return self.amount_of_money


def upload_user(instance, filename):
    return '/'.join(['users', str(instance.user.username), filename])


class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, null=False, blank=False)
    image = models.ImageField(upload_to=upload_user, null=True, blank=True)
    phone = PhoneNumberField(null=True, blank=True)
    info = models.TextField(null=True, blank=True)

    class Meta:
        abstract = True


class Investor(Profile):
    categories = models.ManyToManyField(Category, related_name='investor_categories')
    capital = models.ForeignKey(Capital, on_delete=models.DO_NOTHING, null=False, blank=False)

    def __str__(self):
        return self.user.username

    def no_of_projects(self):
        projects = Project.objects.filter(investor=self)
        return len(projects)

    def avg_rating(self):
        sum = 0
        projects = Project.objects.filter(investor=self)
        for project in projects:
            sum += project.avg_rating()
        if len(projects) == 0:
            return 0
        else:
            return sum / len(projects)


class Entrepreneur(Profile):

    def __str__(self):
        return self.user.username


class Expert(Profile):
    categories = models.ManyToManyField(Category, related_name='expert_categories')
    capitals = models.ManyToManyField(Capital, related_name='capitals')
    cost = models.IntegerField(blank=False, null=False)

    def __str__(self):
        return self.user.username

    def avg_rating(self):
        sum = 0
        projects = Project.objects.filter(expert=self)
        for project in projects:
            sum += project.avg_rating()
        if len(projects) == 0:
            return 0
        else:
            return sum / len(projects)


def upload_article(instance, filename):
    return '/'.join(['projects', str(instance.name), filename])


class Project(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    description = models.TextField(null=True, blank=True)
    image = models.ImageField(upload_to=upload_article, null=True, blank=True)
    categories = models.ManyToManyField(Category, related_name='project_categories')
    capital = models.ForeignKey(Capital, on_delete=models.DO_NOTHING, null=False, blank=False)
    entrepreneur = models.ForeignKey(Entrepreneur, on_delete=models.CASCADE, null=False, blank=False)
    investor = models.ForeignKey(Investor, on_delete=models.DO_NOTHING, null=True, blank=True)
    expert = models.ForeignKey(Expert, on_delete=models.DO_NOTHING, null=True, blank=True)

    def __str__(self):
        return self.name

    def no_of_ratings(self):
        ratings = Rating.objects.filter(project=self)
        return len(ratings)

    def avg_rating(self):
        sum = 0
        ratings = Rating.objects.filter(project=self)
        for rating in ratings:
            sum += rating.stars

        if len(ratings) > 0:
            return sum / len(ratings)
        else:
            return 0


class Rating(models.Model):
    project = models.ForeignKey(Project, on_delete=models.CASCADE, null=False, blank=False)
    user = models.ForeignKey(User, on_delete=models.CASCADE, null=False, blank=False)
    stars = models.IntegerField(validators=[MinValueValidator(1), MaxValueValidator(5)])

    class Meta:
        unique_together = (('user', 'project'),)
        index_together = (('user', 'project'),)

    def __str__(self):
        return self.stars


def upload_article(instance, filename):
    return '/'.join(['articles', str(instance.name), filename])


class Article(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    description = models.TextField(null=True, blank=True)
    image = models.ImageField(upload_to=upload_article, null=True, blank=True)


def upload_release(instance, filename):
    return '/'.join(['releases', str(instance.name), filename])


class Release(models.Model):
    name = models.CharField(max_length=100, null=False, blank=False)
    description = models.TextField(null=True, blank=True)
    image = models.ImageField(upload_to=upload_release, null=True, blank=True)
