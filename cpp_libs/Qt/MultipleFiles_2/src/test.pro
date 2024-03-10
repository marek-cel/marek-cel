TEMPLATE = subdirs

SUBDIRS = \
    gui \
    test

gui.depends = test
