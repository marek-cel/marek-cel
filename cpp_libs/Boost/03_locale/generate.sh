#!/bin/bash

xgettext --keyword=translate:1,1t --keyword=translate:1c,2,2t       \
         --keyword=translate:1,2,3t --keyword=translate:1c,2,3,4t   \
         --keyword=gettext:1 --keyword=pgettext:1c,2                \
         --keyword=ngettext:1,2 --keyword=npgettext:1c,2,3          \
         src/main.cpp \
         --output="locales/hello.pot"
sed --in-place locales/hello.pot --expression='s/CHARSET/UTF-8/'

msginit --input="locales/hello.pot" --output-file="locales/pl/LC_MESSAGES/hello.po" --locale="pl"
msginit --input="locales/hello.pot" --output-file="locales/de/LC_MESSAGES/hello.po" --locale="de"
msginit --input="locales/hello.pot" --output-file="locales/en_US/LC_MESSAGES/hello.po" --locale="en_US"