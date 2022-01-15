TEMPLATE = subdirs

SUBDIRS = \
    gui \
    test1 \
    test2

gui.subdir = $$PWD/gui
test1.subdir = $$PWD/testlib1
test2.subdir = $$PWD/testlib2

gui.depends = test1 test2
