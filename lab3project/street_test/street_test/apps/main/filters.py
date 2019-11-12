from .models import Street
import django_filters

class StreetFilter(django_filters.FilterSet):
    name = django_filters.CharFilter(lookup_expr='icontains')

    class Meta:
        model = Street
        fields = ['name', 'type']
