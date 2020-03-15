# Generated by Django 2.2.4 on 2020-03-15 20:17

from django.db import migrations, models
import phonenumber_field.modelfields


class Migration(migrations.Migration):

    dependencies = [
        ('api', '0001_initial'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='entrepreneur',
            name='profile',
        ),
        migrations.RemoveField(
            model_name='expert',
            name='profile',
        ),
        migrations.RemoveField(
            model_name='investor',
            name='profile',
        ),
        migrations.AddField(
            model_name='entrepreneur',
            name='image',
            field=models.ImageField(blank=True, null=True, upload_to='images/profiles/'),
        ),
        migrations.AddField(
            model_name='entrepreneur',
            name='info',
            field=models.TextField(blank=True, null=True),
        ),
        migrations.AddField(
            model_name='entrepreneur',
            name='phone',
            field=phonenumber_field.modelfields.PhoneNumberField(blank=True, max_length=128, null=True, region=None),
        ),
        migrations.AddField(
            model_name='expert',
            name='image',
            field=models.ImageField(blank=True, null=True, upload_to='images/profiles/'),
        ),
        migrations.AddField(
            model_name='expert',
            name='info',
            field=models.TextField(blank=True, null=True),
        ),
        migrations.AddField(
            model_name='expert',
            name='phone',
            field=phonenumber_field.modelfields.PhoneNumberField(blank=True, max_length=128, null=True, region=None),
        ),
        migrations.AddField(
            model_name='investor',
            name='image',
            field=models.ImageField(blank=True, null=True, upload_to='images/profiles/'),
        ),
        migrations.AddField(
            model_name='investor',
            name='info',
            field=models.TextField(blank=True, null=True),
        ),
        migrations.AddField(
            model_name='investor',
            name='phone',
            field=phonenumber_field.modelfields.PhoneNumberField(blank=True, max_length=128, null=True, region=None),
        ),
        migrations.DeleteModel(
            name='Profile',
        ),
    ]