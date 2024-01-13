from colorama import Fore, Back, Style


class KOmegaSST(object):

    def __init__(self):
        self.rho = 1.225
        self.mu = 0.0000181206
        self.nu = self.mu / self.rho


    def process(self):
        print(Style.BRIGHT + "k-omega SST" + Style.RESET_ALL)
        self.printParametersValues()
    

    def printParametersValues(self):
        print("Default parameters:")
        print("Air density         rho : " + str(self.rho) + " [kg/m^3]")
        print("Dynamic viscosity   mu  : " + '{:.2e}'.format(self.mu)  + " [Pa*s]")
        print("Kinematic viscosity nu  : " + '{:.2e}'.format(self.nu)  + " [m^2/s]")