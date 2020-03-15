from django.contrib import admin
from .models import Category, Capital, Profile, Investor, Entrepreneur, Expert, Project, Rating, Article, Release

admin.site.register(Category)
admin.site.register(Capital)
admin.site.register(Investor)
admin.site.register(Entrepreneur)
admin.site.register(Expert)
admin.site.register(Project)
admin.site.register(Rating)
admin.site.register(Article)
admin.site.register(Release)

