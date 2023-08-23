# Kółko i krzyżyk
# Komputer gra w kółko i krzyżyk przeciwko człowiekowi
   
# stałe globalne
X = "X"
O = "O"
EMPTY = " "
TIE = "TIE"
NUM_SQUARES = 9


def display_instruct():
    """Wyświetl instrukcję gry."""  
    print(
    """
    Witaj w największym intelektualnym wyzwaniu wszech czasów, jakim jest
    gra 'Kółko i krzyżyk'. Będzie to ostateczna rozgrywka między Twoim
    ludzkim mózgiem a moim krzemowym procesorem.  

    Swoje posunięcie wskażesz poprzez wprowadzenie liczby z zakresu 0 - 8.
    Liczba ta odpowiada pozycji na planszy zgodnie z poniższym schematem:
    
                    0 | 1 | 2
                    ---------
                    3 | 4 | 5
                    ---------
                    6 | 7 | 8

    Przygotuj się, Człowieku.  Ostateczna batalia niebawem się rozpocznie. \n
    """
    )


def ask_yes_no(question):
    """Zadaj pytanie, na które można odpowiedzieć tak lub nie."""
    response = None
    while response not in ("t", "n"):
        response = input(question).lower()
    return response


def ask_number(question, low, high):
    """Poproś o podanie liczby z odpowiedniego zakresu."""
    response = None
    while response not in range(low, high):
        response = int(input(question))
    return response


def pieces():
    """Ustal, czy pierwszy ruch należy do gracza, czy do komputera."""
    go_first = ask_yes_no("Czy chcesz mieć prawo do pierwszego ruchu? (t/n): ")
    if go_first == "t":
        print("\nWięc pierwszy ruch należy do Ciebie.  Będzie Ci potrzebny.")
        human = X
        computer = O
    else:
        print("\nTwoja odwaga Cię zgubi... Ja wykonuję pierwszy ruch.")
        computer = X
        human = O
    return computer, human


def new_board():
    """Utwórz nową planszę gry."""
    board = []
    for square in range(NUM_SQUARES):
        board.append(EMPTY)
    return board


def display_board(board):
    """Wyświetl planszę gry na ekranie."""
    print("\n\t", board[0], "|", board[1], "|", board[2])
    print("\t", "---------")
    print("\t", board[3], "|", board[4], "|", board[5])
    print("\t", "---------")
    print("\t", board[6], "|", board[7], "|", board[8], "\n")


def legal_moves(board):
    """Utwórz listę prawidłowych ruchów."""
    moves = []
    for square in range(NUM_SQUARES):
        if board[square] == EMPTY:
            moves.append(square)
    return moves


def winner(board):
    """Ustal zwycięzcę gry."""
    WAYS_TO_WIN = ((0, 1, 2),
                   (3, 4, 5),
                   (6, 7, 8),
                   (0, 3, 6),
                   (1, 4, 7),
                   (2, 5, 8),
                   (0, 4, 8),
                   (2, 4, 6))
    
    for row in WAYS_TO_WIN:
        if board[row[0]] == board[row[1]] == board[row[2]] != EMPTY:
            winner = board[row[0]]
            return winner

    if EMPTY not in board:
        return TIE

    return None


def human_move(board, human):
    """Odczytaj ruch człowieka."""  
    legal = legal_moves(board)
    move = None
    while move not in legal:
        move = ask_number("Jaki będzie Twój ruch? (0 - 8):", 0, NUM_SQUARES)
        if move not in legal:
            print("\nTo pole jest już zajęte, niemądry Człowieku.  Wybierz inne.\n")
    print("Znakomicie...")
    return move


def computer_move(board, computer, human):
    """Spowoduj wykonanie ruchu przez komputer."""
    # utwórz kopię roboczą, ponieważ funkcja będzie zmieniać listę
    board = board[:]
    # najlepsze pozycje do zajęcia według kolejności
    BEST_MOVES = (4, 0, 2, 6, 8, 1, 3, 5, 7)

    print("Wybieram pole numer", end=" ")
    
    # jeśli komputer może wygrać, wykonaj ten ruch
    for move in legal_moves(board):
        board[move] = computer
        if winner(board) == computer:
            print(move)
            return move
        # ten ruch został sprawdzony, wycofaj go
        board[move] = EMPTY
    
    # jeśli człowiek może wygrać, zablokuj ten ruch
    for move in legal_moves(board):
        board[move] = human
        if winner(board) == human:
            print(move)
            return move
        # ten ruch został sprawdzony, wycofaj go
        board[move] = EMPTY

    # ponieważ nikt nie może wygrać w następnym ruchu, wybierz najlepsze wolne pole
    for move in BEST_MOVES:
        if move in legal_moves(board):
            print(move)
            return move


def next_turn(turn):
    """Zmień wykonawcę ruchu."""
    if turn == X:
        return O
    else:
        return X

    
def congrat_winner(the_winner, computer, human):
    """Pogratuluj zwycięzcy."""
    if the_winner != TIE:
        print(the_winner, "jest zwycięzcą!\n")
    else:
        print("Remis!\n")

    if the_winner == computer:
        print("Jak przewidywałem, Człowieku, jeszcze raz zostałem triumfatorem.  \n" \
              "Dowód na to, że komputery przewyższają ludzi pod każdym względem.")

    elif the_winner == human:
        print("No nie!  To niemożliwe!  Jakoś udało Ci się mnie zwieść, Człowieku. \n" \
              "Ale to się nigdy nie powtórzy!  Ja, komputer, przyrzekam Ci to!")

    elif the_winner == TIE:
        print("Miałeś mnóstwo szczęścia, Człowieku, i jakoś udało Ci się ze mną " \
              "zremisować. \nŚwiętuj ten dzień... bo to najlepszy wynik, jaki możesz " \
              "kiedykolwiek osiągnąć.")


def main():
    display_instruct()
    computer, human = pieces()
    turn = X
    board = new_board()
    display_board(board)

    while not winner(board):
        if turn == human:
            move = human_move(board, human)
            board[move] = human
        else:
            move = computer_move(board, computer, human)
            board[move] = computer
        display_board(board)
        turn = next_turn(turn)

    the_winner = winner(board)
    congrat_winner(the_winner, computer, human)


# rozpocznij program
main()
input("\n\nAby zakończyć grę, naciśnij klawisz Enter.")
