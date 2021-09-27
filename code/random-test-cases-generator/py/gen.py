from random import randint, choices
from os import system
import sys

def generate():
    sys.stdout = open("in", "w")
    # generate input
    print(randint(1, 100))
    sys.stdout = sys.__stdout__

def clear(files):
    statement = "rm"
    for file in files:
        statement = statement + " " + file
    system(statement)

iterations = 100

system("echo Compiling wa.cpp")
system("g++ wa.cpp -o wa")

system("echo Compiling ac.cpp")
system("g++ ac.cpp -o ac")

for _ in range(iterations):
    print("Test Case {}: ".format(_ + 1), end="")
    generate()
    system("./wa < in > wa_out")
    system("./ac < in > ac_out")
    wa_out = open("wa_out", "r").read().strip()
    ac_out = open("ac_out", "r").read().strip()
    if wa_out != ac_out:
        print("Wrong Answer")
        clear(["wa", "ac"])
        exit(0)
    print("Correct")

print("Accepted")
clear(["wa", "ac", "in", "wa_out", "ac_out"])
