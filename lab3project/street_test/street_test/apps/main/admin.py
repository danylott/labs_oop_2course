from django.db import models
from django.contrib.gis.db import models
from django.contrib.gis import admin
from .models import *

class SegmentStreetInline(admin.TabularInline):
    model = SegmentStreet
    autocomplete_fields = ['street', 'segment']
    extra = 1
    ordering = ('id',)

class AdminStreet(admin.ModelAdmin):
    list_display = ['id', 'name', 'type', 'description']
    fieldsets = [
        (None,               {'fields': ['name', 'description', 'significance']}),
        ('Дані з довідників', {'fields': ['type']}),
    ]
    search_fields = ['name']
    list_filter = ['type', 'segmentstreet__segment__district']
    inlines = (SegmentStreetInline,)
    ordering = ('id',)

class AdminSegment(admin.ModelAdmin):
    list_display = ['id','type', 'district', 'description']
    fieldsets = [
        (None,               {'fields': ['description']}),
        ('Дані з довідників', {'fields': ['type', 'district', 'topocode', 'geom_type', 'tract_mtz']}),
    ]
    list_filter = ['type', 'district']
    search_fields = ['id']
    inlines = (SegmentStreetInline,)
    ordering = ('id',)


admin.site.register(Street, AdminStreet)
# admin.site.register(SegmentStreet)
admin.site.register(Segment, AdminSegment)
