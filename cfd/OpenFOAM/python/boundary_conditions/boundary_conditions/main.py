from enum import Enum
from colorama import Fore, Back, Style
from boundary_conditions.komegasst import KOmegaSST


class Models(Enum):
    KOMEGASST = 1
    SPALARTALLMARAS = 2

    @classmethod
    def has_value(self, value):
        return value in set(item.value for item in self) 


def main():
    print("OpenFOAM boundary conditions calculator for turbulance models")
    model = chooseTurbulencyModel()
    if model == Models.KOMEGASST.value:
        model = KOmegaSST()
        model.process()


def chooseTurbulencyModel():
    model = 0
    while (not Models.has_value(model)):
        print("Choose turbulency model")
        print("[1] k-omega SST")
        print("[2] Spalart-Allmaras")
        model = int(input() or 0)
        if (not Models.has_value(model)):
            print(Fore.RED + "Wrong model." + Style.RESET_ALL)
            input("Press Enter to continue...")
    return model
