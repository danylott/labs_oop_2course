from .models import *
from django.shortcuts import render
from django.http import Http404
from datetime import datetime, date
from django.db.models import Q
import copy
from django.http import Http404, HttpResponseRedirect
from django.http import JsonResponse
from django.urls import reverse

def search(request):
    if request.method == 'POST' and 'date' in request.POST:
        dat = request.POST['date']
    else:
        dat = date.today()
    date_now = date.today()
    street_list = actual_streets(dat)
    street_count = street_list.count()
    return render(request, 'main/street_list.html', {'street_list': street_list, 'street_count': street_count, 'date_now': str(date_now)})

def search_ajax(request):
    if request.is_ajax():
        searchDate = request.GET['searchDate']
        if not searchDate:
            searchDate = date.today()
        searchName = request.GET['searchName']
        street = actual_streets(searchDate)
        street = street.filter(Q(name__icontains=searchName) | Q(streetalternativename__name__icontains=searchName))
        street = street.distinct()
        # street = street[:100]
        # count_of_segments = []
        # for str in street:
        #     count_of_segments.append(str.count_segments_by_date(searchDate))
        street_list = list(street.values_list('id', 'name', 'type__name'))
        # response = {'street_list': street_list, 'count_of_segments': count_of_segments}
        return JsonResponse(street_list, safe=False)
    else:
        raise Http404

def detail(request, street_id):
    street = Street.objects.get(id = street_id)
    segment_list = Segment.objects.filter(
        Q(street__id=street_id),
        Q(segmentstreet__date_start__lt = date.today())|Q(segmentstreet__date_start=None),
        Q(segmentstreet__date_end__gte = date.today())|Q(segmentstreet__date_end=None),
    )
    return render(request, 'main/detail.html', {'street': street, 'segment_list': segment_list})

#Осторожно : Писал Германюк!!!
def free_segments(request):
    not_free_id = SegmentStreet.objects.values('segment').distinct()
    segment_list = Segment.objects.exclude(id__in=not_free_id)
    return render(request, 'main/detail.html', {'free_segments': segment_list})

def street_rename(street_id, street_name, doc_id, operation_date):
    street = Street.objects.get(id = street_id)
    new_street = copy.copy(street)
    new_street.name = street_name
    segments = street.segments.all()
    new_street.id = None
    segment_list = list(segments)
    pairs = SegmentStreet.objects.filter(street=street.id).filter(segment__in = segment_list)
    for p in pairs:
        p.date_end = operation_date
        p.save()
    for s in segments:
        new_street.segments.add(s)
    new_street.save()
    pairs = SegmentStreet.objects.filter(street=new_street.id)
    for p in pairs:
        p.date_start = operation_date
        p.save()
    operation = OperationStreet(old = street.id, new = new_street.id, document = doc_id, date = operation_date)
    operation.save()
    return new_street.id

def actual_streets(date):
    result_list = []
    pairs = SegmentStreet.objects.all()
    actual_pairs = pairs.filter(
        Q(date_start__lt = date)|Q(date_start=None),
        Q(date_end__gte = date)|Q(date_end=None),
    )
    streetsInPairs = pairs.values_list('street',flat = True).distinct()
    result_list += actual_pairs.values_list('street',flat = True).distinct()
    streets = Street.objects.values_list('id', flat = True).exclude(id__in=streetsInPairs)
    result_list += streets
    ret = Street.objects.filter(id__in=result_list)
    return ret
