# Generated by Django 2.2.8 on 2019-12-03 20:50

import datetime
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        ('dictionaries', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='DocumentsStreet',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('document', models.FileField(blank=True, upload_to='files/%Y/%m/%d', verbose_name='Документ')),
                ('date', models.DateField(blank=True, null=True, verbose_name='Дата додавання документу')),
                ('path_pdf', models.TextField(blank=True, null=True, verbose_name='Шлях до PDF')),
                ('pub_date', models.DateTimeField(blank=True, default=datetime.datetime(2019, 12, 3, 22, 50, 0, 160142), null=True, verbose_name='Дата публікації  документу')),
                ('name', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='dictionaries.DictStreetOperations', verbose_name='Назва документу')),
            ],
            options={
                'verbose_name': 'Документ',
                'verbose_name_plural': 'Таблиця документів',
                'db_table': 'dit_documents_street',
            },
        ),
        migrations.CreateModel(
            name='OperationSegment',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('date', models.DateField(blank=True, null=True, verbose_name='Дата проведення операції над сегментом')),
                ('document', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='main.DocumentsStreet')),
            ],
            options={
                'verbose_name': 'Операція над сегментом',
                'verbose_name_plural': 'Операції над сегментами',
                'db_table': 'dit_operation_segment',
            },
        ),
        migrations.CreateModel(
            name='OperationSegmentStreet',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('date', models.DateField(blank=True, null=True, verbose_name='Дата проведення операції над парою вулиця-сегмент')),
                ('document', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='main.DocumentsStreet')),
            ],
            options={
                'verbose_name': "Операція над проведенням зв'язку сегмент-вулиця",
                'verbose_name_plural': "Операції над проведенням зв'язку сегмент-вулиця",
                'db_table': 'dit_operation_segment_street',
            },
        ),
        migrations.CreateModel(
            name='OperationStreet',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('date', models.DateField(blank=True, null=True, verbose_name='Дата проведення операції над вулицею')),
                ('document', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='main.DocumentsStreet')),
            ],
            options={
                'verbose_name': 'Операція над вулицею',
                'verbose_name_plural': 'Операції над вулицями',
                'db_table': 'dit_operation_street',
            },
        ),
        migrations.CreateModel(
            name='Segment',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('description', models.TextField(blank=True, null=True, verbose_name='Опис сегменту')),
                ('stream_amount', models.IntegerField(blank=True, null=True, verbose_name='Кількість потоків')),
                ('road_index', models.TextField(blank=True, null=True, verbose_name='Індекс дороги')),
                ('road_type_significance', models.TextField(blank=True, null=True, verbose_name='Значення дороги')),
                ('road_destination', models.TextField(blank=True, null=True, verbose_name='Сполучення')),
                ('district', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='dictionaries.DictDistricts')),
                ('geom_type', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='dictionaries.DictStreetGeomType')),
                ('operation', models.ManyToManyField(through='main.OperationSegment', to='main.Segment')),
                ('tract_mtz', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='dictionaries.DictStreetTract')),
            ],
            options={
                'verbose_name': 'Сегмент',
                'verbose_name_plural': 'Перелік сегментів',
                'db_table': 'dit_segment',
            },
        ),
        migrations.CreateModel(
            name='SegmentStreet',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('date_start', models.DateField(blank=True, null=True, verbose_name='Дата початку')),
                ('date_end', models.DateField(blank=True, null=True, verbose_name='Дата кінця')),
                ('operation', models.ManyToManyField(through='main.OperationSegmentStreet', to='main.SegmentStreet')),
                ('segment', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='main.Segment')),
            ],
            options={
                'verbose_name': "Зв'язок між вулицею та сегментом",
                'verbose_name_plural': "Зв'язки між вулицями та сегментами",
                'db_table': 'dit_segment_street',
            },
        ),
        migrations.CreateModel(
            name='Street',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(blank=True, max_length=100, null=True, verbose_name='Назва вулиці')),
                ('prev_id', models.IntegerField(blank=True, null=True, verbose_name='Попередній ID')),
                ('description', models.CharField(blank=True, max_length=100, null=True, verbose_name='Опис вулиці')),
                ('significance', models.CharField(blank=True, max_length=100, null=True, verbose_name='Значення')),
                ('geom_type', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='dictionaries.DictStreetGeomType')),
                ('operation', models.ManyToManyField(through='main.OperationStreet', to='main.Street')),
                ('segments', models.ManyToManyField(through='main.SegmentStreet', to='main.Segment')),
                ('topocode', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='dictionaries.DictStreetTopocode')),
                ('type', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='dictionaries.DictStreetType')),
            ],
            options={
                'verbose_name': 'Вулиця',
                'verbose_name_plural': 'Перелік вулиць',
                'db_table': 'dit_street',
            },
        ),
        migrations.CreateModel(
            name='StreetAlternativeName',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(blank=True, max_length=100, null=True, verbose_name='Назва вулиці')),
                ('street', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='main.Street')),
            ],
            options={
                'verbose_name': 'Альтернативна назва вулиці',
                'verbose_name_plural': 'Альтернативні назви вулиць',
                'db_table': 'dit_street_alternative_name',
            },
        ),
        migrations.AddField(
            model_name='segmentstreet',
            name='street',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.DO_NOTHING, to='main.Street'),
        ),
        migrations.AddField(
            model_name='operationstreet',
            name='new',
            field=models.ForeignKey(blank=True, db_column='new', null=True, on_delete=django.db.models.deletion.DO_NOTHING, related_name='new', to='main.Street', verbose_name='Нова вулиця'),
        ),
        migrations.AddField(
            model_name='operationstreet',
            name='old',
            field=models.ForeignKey(blank=True, db_column='old', null=True, on_delete=django.db.models.deletion.DO_NOTHING, related_name='old', to='main.Street', verbose_name='Стара вулиця'),
        ),
        migrations.AddField(
            model_name='operationsegmentstreet',
            name='new',
            field=models.ForeignKey(blank=True, db_column='new', null=True, on_delete=django.db.models.deletion.DO_NOTHING, related_name='new', to='main.SegmentStreet', verbose_name="Новий зв'язок"),
        ),
        migrations.AddField(
            model_name='operationsegmentstreet',
            name='old',
            field=models.ForeignKey(blank=True, db_column='old', null=True, on_delete=django.db.models.deletion.DO_NOTHING, related_name='old', to='main.SegmentStreet', verbose_name="Старий зв'язок"),
        ),
        migrations.AddField(
            model_name='operationsegment',
            name='new',
            field=models.ForeignKey(blank=True, db_column='new', null=True, on_delete=django.db.models.deletion.DO_NOTHING, related_name='new', to='main.Segment', verbose_name='Новий сегмент'),
        ),
        migrations.AddField(
            model_name='operationsegment',
            name='old',
            field=models.ForeignKey(blank=True, db_column='old', null=True, on_delete=django.db.models.deletion.DO_NOTHING, related_name='old', to='main.Segment', verbose_name='Старий сегмент'),
        ),
    ]