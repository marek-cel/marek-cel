#!/bin/bash

# xgettext -o messages.pot src/main.cpp
# xgettext --keyword=translate:1,1t --keyword=translate:1,2,3t src/main.cpp

# xgettext --keyword="translate" --output="locales/my-domain.pot" src/main.cpp
# msginit --input="locales/my-domain.pot" --output-file="locales/en/my-domain.po" --locale="en"
# msginit --input="locales/my-domain.pot" --output-file="locales/pl/my-domain.po" --locale="pl"
# msgfmt "locales/en/my-domain.po" --output-file="locales/en/my-domain.mo"
# msgfmt "locales/pl/my-domain.po" --output-file="locales/pl/my-domain.mo"