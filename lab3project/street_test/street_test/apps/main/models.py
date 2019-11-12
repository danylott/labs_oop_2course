from django.contrib.gis.db import models
from dictionaries.models import *

# class DocumentsStreet(models.Model):
#     name = models.TextField('Назва документу', blank=True, null=True)
#     ext = models.TextField('?', blank=True, null=True)
#     description = models.TextField('Опис документу', blank=True, null=True)
#     path = models.TextField('Шлях до документу', blank=True, null=True)
#     date = models.DateField('Дата додавання документу', blank=True, null=True)
#     path_pdf = models.TextField('Шлях до PDF', blank=True, null=True)
#     pub_date = models.DateTimeField('Дата публікації  документу', blank=True, null=True)
#     dit_directory_street = models.ForeignKey(DictStreetDocuments, models.DO_NOTHING, blank=True, null=True)
#
#     class Meta:
        #
#
#         db_table = 'dit_documents_street'


# class OperationSegment(models.Model):
#     # new = models.ForeignKey('DitSegment', models.DO_NOTHING, db_column='new', blank=True, null=True)
#     old = models.ForeignKey('Segment', models.DO_NOTHING, db_column='old', blank=True, null=True)
#     date = models.DateField('Дата проведення операції над сегментом', blank=True, null=True)
#     dit_documents_street = models.ForeignKey(DocumentsStreet, models.DO_NOTHING, blank=True, null=True)
#
#     class Meta:
        #
#
#         db_table = 'dit_operation_segment'


# class OperationSegmentStreet(models.Model):
#     # new = models.ForeignKey('DitSegmentStreet', models.DO_NOTHING, db_column='new', blank=True, null=True)
#     old = models.ForeignKey('SegmentStreet', models.DO_NOTHING, db_column='old', blank=True, null=True)
#     date = models.DateField('Дата проведення операції над парою вулиця-сегмент', blank=True, null=True)
#     dit_documents_street = models.ForeignKey(DocumentsStreet, models.DO_NOTHING, blank=True, null=True)
#
#     class Meta:
        #
#
#         db_table = 'dit_operation_segment_street'


# class OperationStreet(models.Model):
#     # new = models.ForeignKey('DitStreet', models.DO_NOTHING, db_column='new', blank=True, null=True)
#     old = models.ForeignKey('Street', models.DO_NOTHING, db_column='old', blank=True, null=True)
#     date = models.DateField('Дата проведення операції над вулицею', blank=True, null=True)
#     dit_documents_street = models.ForeignKey(DocumentsStreet, models.DO_NOTHING, blank=True, null=True)
#
#     class Meta:
#
#
#         db_table = 'dit_operation_street'


class Segment(models.Model):
    description = models.TextField('Опис сегменту', blank=True, null=True)
    stream_amount = models.IntegerField('Кількість потоків', blank=True, null=True)
    district = models.ForeignKey(DictDistricts, models.DO_NOTHING, blank=True, null=True)
    road_index = models.TextField('Індекс дороги', blank=True, null=True)
    road_type_significance = models.TextField('Значення дороги', blank=True, null=True)
    road_destination = models.TextField('Сполучення', blank=True, null=True)
    topocode = models.ForeignKey(DictStreetTopocode, models.DO_NOTHING, blank=True, null=True)
    type = models.ForeignKey(DictStreetType, models.DO_NOTHING, blank=True, null=True)
    geom_type = models.ForeignKey(DictStreetGeomType, models.DO_NOTHING, blank=True, null=True)
    tract_mtz = models.ForeignKey(DictStreetTract, models.DO_NOTHING, blank=True, null=True)

    class Meta:

        db_table = 'dit_segment'
        verbose_name = 'Сегмент'
        verbose_name_plural = 'Перелік сегментів'

    def __str__(self):
        return "id: " + str(self.id) + " " + self.type.name


class Street(models.Model):
    name = models.CharField('Назва вулиці', max_length= 100, blank=True, null=True)
    prev_id = models.IntegerField('Попередній ID', blank=True, null=True)
    topocode = models.ForeignKey(DictStreetTopocode, models.DO_NOTHING, blank=True, null=True)
    description = models.CharField('Опис вулиці', max_length= 100, blank=True, null=True)
    type = models.ForeignKey(DictStreetType, models.DO_NOTHING, blank=True, null=True)
    geom_type = models.ForeignKey(DictStreetGeomType, models.DO_NOTHING, blank=True, null=True)
    significance = models.CharField('Значення', max_length= 100, blank=True, null=True)
    segments = models.ManyToManyField(Segment, through='SegmentStreet')

    class Meta:

        db_table = 'dit_street'
        verbose_name = 'Вулиця'
        verbose_name_plural = 'Перелік вулиць'

    def __str__(self):
        return self.name


class SegmentStreet(models.Model):
    street = models.ForeignKey(Street, models.DO_NOTHING, blank=True, null=True)
    segment = models.ForeignKey(Segment, models.DO_NOTHING, blank=True, null=True)
    date_start = models.DateField('Дата початку', blank=True, null=True)
    date_end = models.DateField('Дата кінця', blank=True, null=True)

    class Meta:

        db_table = 'dit_segment_street'
        verbose_name = "Зв'язок між вулицею та сегментом"
        verbose_name_plural = "Зв'язки між вулицями та сегментами"

    def __str__(self):
        return "Вулиця: " + str(self.street) + " Сегмент: " + str(self.segment)
