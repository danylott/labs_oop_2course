# Generated by Django 2.2.6 on 2019-11-11 16:02

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('main', '0001_initial'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='segment',
            options={'verbose_name': 'Сегмент', 'verbose_name_plural': 'Перелік сегментів'},
        ),
        migrations.AlterModelOptions(
            name='segmentstreet',
            options={'verbose_name': "Зв'язок між вулицею та сегментом", 'verbose_name_plural': "Зв'язки між вулицями та сегментами"},
        ),
        migrations.AlterModelOptions(
            name='street',
            options={'verbose_name': 'Вулиця', 'verbose_name_plural': 'Перелік вулиць'},
        ),
    ]