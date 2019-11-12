from .models import Street, Segment
from django.shortcuts import render
from .filters import StreetFilter
from django.http import Http404
from datetime import datetime, date
from django.db.models import Q

def search(request):
    street_list = Street.objects.all()
    street_filter = StreetFilter(request.GET, queryset=street_list)
    return render(request, 'main/street_list.html', {'filter': street_filter})

def detail(request, street_id):
    street = Street.objects.get(id = street_id)
    segment_list = Segment.objects.filter(
        Q(street__id=street_id),
        Q(segmentstreet__date_start__lt = date.today())|Q(segmentstreet__date_start=None),
        Q(segmentstreet__date_end__gte = date.today())|Q(segmentstreet__date_end=None),
    )
    return render(request, 'main/detail.html', {'street': street, 'segment_list': segment_list})
