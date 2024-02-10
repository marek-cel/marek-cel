#!/bin/python3

if __name__ == "__main__":
    number = int(input("Enter a number: "))
    print(str(number))

    dividers = []

    for x in range(1,number,1):
        if number % x == 0:
            dividers.append(x)
    
    print(dividers)
