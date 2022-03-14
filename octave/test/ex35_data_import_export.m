clear all

pkg load io

data_txt = fileread('data/ex35_data.txt')
data_csv = csvread('data/ex35_data.csv')
data_xls = xlsread('data/ex35_data.xlsx')
data_ods = odsread('data/ex35_data.ods') % octave only