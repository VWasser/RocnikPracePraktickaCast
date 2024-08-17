QT += core gui widgets network

CONFIG += c++20 ordered

TEMPLATE = subdirs

SUBDIRS = \
    BackendlessQt \
    App

App.depends = BackendlessQt
