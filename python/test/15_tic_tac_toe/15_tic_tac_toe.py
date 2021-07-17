#!/usr/bin/env python3

################################################################################


X = "X"
O = "O"
EMPTY = " "
TIE = "TIE"
NUM_FIELDS = 9

################################################################################


def main():
    print_instructions()

    board = [i for i in range(0, NUM_FIELDS)]
    print_board(board)

    board = [" " for i in range(0, NUM_FIELDS)]

    winner = None
    token = X

    while not winner:
        if token == X:
            human_move(board)
        else:
            computer_move(board)

        token = switch_player(token)

        print_board(board)
        winner = get_winner(board)

        if len(legal_moves(board)) == 0:
            break

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

    if field_id in legal_moves(b):
        b[field_id] = X
        return True

    return False

################################################################################


def human_move(b):
    result = False
    while not result:
        result = pick_field(b)

################################################################################


def computer_move(b):
    for i in legal_moves(b):
        b[i] = O
        break

################################################################################


def switch_player(t):
    if t == X:
        return O
    else:
        return X

################################################################################


def get_winner(b):
    WAYS_TO_WIN = (
        (0, 1, 2),
        (3, 4, 5),
        (6, 7, 8),
        (0, 3, 6),
        (1, 4, 7),
        (2, 5, 8),
        (0, 4, 8),
        (2, 4, 6)
    )

    for seq in WAYS_TO_WIN:
        if b[seq[0]] == b[seq[1]] == b[seq[2]] != EMPTY:
            return b[seq[0]]

    return None

################################################################################


def legal_moves(b):
    lm = []
    for i in range(0, NUM_FIELDS):
        if b[i] == " ":
            lm.append(i)

    return lm

################################################################################


main()

################################################################################