#!/bin/bash

cd bin; valgrind --tool=memcheck --leak-check=yes ./execfile; cd ..
