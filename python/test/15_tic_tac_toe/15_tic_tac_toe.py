#!/usr/bin/env python3

################################################################################


def print_instructions():
    print("This is a tic-tac-toe game")

################################################################################


def print_board(b):
    print()
    print("", b[0], "|", b[1], "|", b[2])
    print("---+---+---")
    print("", b[3], "|", b[4], "|", b[5])
    print("---+---+---")
    print("", b[6], "|", b[7], "|", b[8])

################################################################################


def pick_field(b):
    field_id = int(input("Pick field "))

    if field_id in range(0, 9, 1):
        if b[field_id] == " ":
            b[field_id] = "X"
            return True, b

    return False, b

################################################################################


def computer_move(b):
    for i in range(0, len(b), 1):
        if b[i] == " ":
            b[i] = "O"
            break

################################################################################


def is_finished():
    return False

################################################################################


print_instructions()

board = [i for i in range(0, 9, 1)]
print_board(board)

board = [" " for i in range(0, 9, 1)]

finished = False
player = 0

while not finished:
    if player == 0:
        result = False
        while not result:
            result, board = pick_field(board)
    else:
        computer_move(board)

    if player == 0:
        player = 1
    else:
        player = 0

    print_board(board)
    finished = is_finished()

################################################################################
