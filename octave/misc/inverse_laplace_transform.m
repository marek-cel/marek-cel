pkg load symbolic
syms s t
Fun_s=1/(s/a+1)
ilaplace(Fun_s,s,t)

Fun_s=4/(s^2 + 4*0.02*s + 4)
ilaplace(Fun_s,s,t)
