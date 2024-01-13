################################################################################
# Copyright (c) 2024 Marek M. Cel
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
################################################################################

from enum import Enum
import math
import os
import platform
from colorama import Fore, Back, Style

################################################################################


def clear_screen():
    os_name = platform.system()
    if os_name == "Linux":
        os.system('clear')
    elif os_name == "Windows":
        os.system('cls')


def print_red(msg):
    print(Fore.RED + str(msg) + Style.RESET_ALL)


def print_bold(msg):
    print(Style.BRIGHT + str(msg) + Style.RESET_ALL)


def print_value(name, value, units, description = "", val_format = "",
                n_len = 4, v_len = 9, u_len = 8):
    fn = '{0: <' + str(n_len) + '}'
    fv = '{0: <' + str(v_len) + '}'
    fu = '{0: <' + str(u_len) + '}'
    val = str(value)
    if len(val_format) > 0:
        val = val_format.format(value)
    msg = fn.format(name) + ": " + fv.format(val) + fu.format("[" + units + "]")
    if len(description) > 0:
        msg = msg + " (" + description + ")"
    print(msg)


def ask_yes_or_no(msg):
    return ask_quetion(msg, ("y", "n"), (True, False))


def ask_quetion(msg, options, values):
    msg_full = msg
    msg_full = msg_full + " ["
    first = True
    for option in options:
        if not first:
            msg_full = msg_full + " or "
        msg_full = msg_full + "\"" + option + "\""
        first = False
    msg_full = msg_full + "] "
    answer = input(msg_full)
    while not answer in options:
        print("\033[A" + (80 * " ") + "\033[A")
        answer = input(msg_full)
    index = options.index(answer)
    return values[index]


def input_float(msg = ""):
    text = input(msg)
    while not is_convertible_to_float(text):
        print("\033[A" + (80 * " ") + "\033[A")
        text = input(msg)
    return float(text)


def is_convertible_to_float(str):
    try:
        result = float(str)
        return True;
    except ValueError:
        return False;


################################################################################


class Models(Enum):
    KOMEGASST = 1
    SPALARTALLMARAS = 2


    @classmethod
    def has_value(self, value):
        return value in set(item.value for item in self) 
    

################################################################################


def chooseTurbulencyModel():
    model = 0
    while (not Models.has_value(model)):
        clear_screen()
        print("Choose turbulency model")
        print("[1] k-omega SST")
        print("[2] Spalart-Allmaras")
        print()
        text = input()
        model = int(text) if text.isdigit() else 0
    return model


################################################################################


class KOmegaSST(object):


    def __init__(self):
        self.reset_to_defaults()
    

    def reset_to_defaults(self):
        self.rho = 1.225
        self.mu = 0.0000181206
        self.nu = self.mu / self.rho
        self.vel = 0.0
        self.len = 0.0
        self.lin = 0.0
        self.model_params_default = True


    def process(self):
        self.printHeader()
        self.askIfChangeAirParametersValues()
        self.printHeader()
        if self.model_params_default:
            self.changeModelParametersValues()
            self.askIfChangeModelParametersValues()
        else:
            self.askIfChangeModelParametersValues()
        self.printHeader()
        self.printAllParametersValues()
        self.compute()
    

    def askIfChangeAirParametersValues(self):
        self.printHeader()
        self.printAirParametersValues()
        print()
        if not ask_yes_or_no("Are these values correct?"):
            self.changeAirParametersValues();
            self.askIfChangeAirParametersValues()


    def askIfChangeModelParametersValues(self):
        self.printHeader()
        self.printModelParametersValues()
        print()
        if not ask_yes_or_no("Are these values correct?"):
            self.changeModelParametersValues();
            self.askIfChangeModelParametersValues()


    def printHeader(self):
        clear_screen()
        print_bold(">>> k-omega SST")
        print()
    

    def printAirParametersValues(self):
        print("Air parameters:")
        print_value("rho" , self.rho , "kg/m^3" , "air density")
        print_value("mu"  , self.mu  , "Pa*s"   , "dynamic viscosity"   , val_format='{:.2e}')
        print_value("nu"  , self.nu  , "m^2/s"  , "kinematic viscosity" , val_format='{:.2e}')
    

    def printModelParametersValues(self):
        print("Model parameters:")
        print_value("vel", self.vel, "m/s" , "airspeed")
        print_value("len", self.len, "m"   , "reference length")
        print_value("lin", self.lin, "m"   , "inlet size")


    def printAllParametersValues(self):
        self.printAirParametersValues()
        print()
        self.printModelParametersValues()
    

    def changeAirParametersValues(self):
        print("Set air density (rho) expressed in [kg/m^3]")
        self.rho = input_float()
        print("Set dynamic viscosity (mu) expressed in [Pa*s]")
        self.mu  = input_float()
        self.nu  = self.mu / self.rho
    

    def changeModelParametersValues(self):
        print()
        print("Set airspeed expressed in [m/s]")
        self.vel = input_float()
        print()
        print("Set reference length (eg. MAC) expressed in [m]")
        self.len = input_float()
        print()
        print("Set inlet size (eg. diameter) expressed in [m]")
        self.lin = input_float()
        self.model_params_default = False

    
    def compute(self):
        Re = round((self.vel * self.len) / self.nu)
        C_mu = 0.09
        L = 0.07 * self.lin
        Ti = 0.16 * Re ** (-1.0/8.0)
        k = 1.5 * (self.vel*Ti) ** 2.0
        omega = math.sqrt(k) / (C_mu * L)

        print()
        print("Re = " + str(Re))

        print()
        print("Turbulency model parameters:")
        print_value("turbulentKE", k, "m^2/s^2",
                    "turbulent kinetic energy", val_format='{:.2f}',
                    n_len = 15, u_len = 10)
        print_value("turbulentOmega", omega, "1/s",
                    "specific turbulence dissipation rate", val_format='{:.2f}',
                    n_len = 15, u_len = 10)
        print()


################################################################################


class ModelsPool(object):


    def __init__(self):
        self.komegasst = KOmegaSST()


################################################################################


if __name__ == "__main__":
    pool = ModelsPool()
    quit = False
    while not quit:
        model = chooseTurbulencyModel()
        if model == Models.KOMEGASST.value:
            model = pool.komegasst
            model.process()
        quit = ask_quetion("Do you want to quit?")