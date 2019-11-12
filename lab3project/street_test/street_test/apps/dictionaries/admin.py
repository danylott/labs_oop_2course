from django.db import models
from django.contrib.gis.db import models
from django.contrib.gis import admin
from .models import *
# Register your models here.

admin.site.register(DictStreetDocuments)
admin.site.register(DictStreetGeomType)
admin.site.register(DictStreetTopocode)
admin.site.register(DictStreetTract)
admin.site.register(DictStreetType)
admin.site.register(DictDistricts)
