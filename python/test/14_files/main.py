#!/usr/bin/env python3

################################################################################

text_file = open("input.txt", "r")

print(text_file.read(1))
print(text_file.read(7))

text_file.close()

################################################################################

print()

text_file = open("input.txt", "r")

whole_thing = text_file.read()
print(whole_thing)

text_file.close()

################################################################################

print()

text_file = open("input.txt", "r")

print(text_file.readline())

print(text_file.readline(1))
print(text_file.readline(7))

text_file.close()

################################################################################

print()

text_file = open("input.txt", "r")

lines = text_file.readlines()

for line in lines:
    print(line)

text_file.close()

################################################################################

print()

text_file = open("input.txt", "r")

for line in text_file:
    print(line)

text_file.close()

################################################################################

print()

text_file = open("output.txt", "w")

text_file.write("1st line\n")
text_file.write("2nd line\n")
text_file.write("3rd line\n")

text_file.close()

################################################################################
