#!/bin/python3

import numpy as np
import pandas

def readFile(filename):
    df = pandas.read_csv(filename)
    data = df.to_numpy().transpose()
    return data

if __name__ == "__main__":
    beta = readFile("data/NACA_TR-1309_beta.csv")
    b_d = readFile("data/NACA_TR-1309_b_D.csv")
    cld = readFile("data/NACA_TR-1309_cld.csv")
    h_b = readFile("data/NACA_TR-1309_h_b.csv")

    start = 0.2
    stop = 1.0
    step = 0.025
    for r in np.arange(start, stop + step, step):
        rr = round(r,3)
        output = str(rr)
        output += "," + str(round(np.interp(rr, beta[0], beta[1]), 2))
        output += "," + str(round(np.interp(rr, b_d[0], b_d[1]), 5))
        output += "," + str(round(np.interp(rr, cld[0], cld[1]), 4))
        output += "," + str(round(np.interp(rr, h_b[0], h_b[1]), 5))

        print(output)
