# this script is used to generate
# files for testing operations of MBigInt

import random
import os

EXPERIMENTS_NUM_SMALL = int(1e2)
EXPERIMENTS_NUM_BIG = int(1e4)

UPPER_BOUND_SMALL = int(1e2)
LOWER_BOUND_SMALL = -UPPER_BOUND_SMALL

UPPER_BOUND_BIG = int(1e100)
LOWER_BOUND_BIG = -UPPER_BOUND_BIG

DIR_NAME = "MBigIntSample"
try:
    os.mkdir(DIR_NAME)
except:
    pass
os.chdir(DIR_NAME)

# generating samples for binary operators
binaryOperatorsNames = [
    "Addition",
    "Subtraction",
    "Multiplication",
    "Division",
    "Equal",
    "NotEqual",
    "Gt",
    "Lt",
    "GtEq",
    "LtEq",
    "Modulus"
]

binaryOperatorfunctions = [
    lambda a, b: a + b,
    lambda a, b: a - b,
    lambda a, b: a * b,
    lambda a, b: a // b,
    lambda a, b: a == b,
    lambda a, b: a != b,
    lambda a, b: a > b,
    lambda a, b: a < b,
    lambda a, b: a >= b,
    lambda a, b: a <= b,
    lambda a, b: a % b,
]

for ni, name in enumerate(binaryOperatorsNames):
    if(os.path.isfile(name + ".txt")):
        print("Detected test for", name)
        continue

    print("Writing tests for", name)

    fd = open(name + ".txt", "w", encoding="utf-8")

    function = binaryOperatorfunctions[ni]

    res = []

    for i in range(EXPERIMENTS_NUM_SMALL):
        a = random.randint(LOWER_BOUND_SMALL, UPPER_BOUND_SMALL)
        b = random.randint(LOWER_BOUND_SMALL, UPPER_BOUND_SMALL)
        try:
            c = function(a, b)
            s = str(a) + " " + str(b) + " " + str(c) + "\n"
            fd.write(s)
        except:
            continue

    for i in range(EXPERIMENTS_NUM_BIG):
        a = random.randint(LOWER_BOUND_BIG, UPPER_BOUND_BIG)
        b = random.randint(LOWER_BOUND_BIG, UPPER_BOUND_BIG)
        try:
            c = function(a, b)
            s = str(a) + " " + str(b) + " " + str(c) + "\n"
            fd.write(s)
        except:
            continue

    fd.close()

# generating samples for unary operators
unaryOperatorNames = [
    "UnaryPlus",
    "UnaryMinus",
    "Abs"
]

unaryOperatorFunctions = [
    lambda a: a,
    lambda a: -a,
    lambda a: abs(a)
]

for ni, name in enumerate(unaryOperatorNames):
    if(os.path.isfile(name + ".txt")):
        print("Detected test for", name)
        continue

    print("Writing tests for", name)

    fd = open(name + ".txt", "w", encoding="utf-8")

    function = unaryOperatorFunctions[ni]

    for i in range(EXPERIMENTS_NUM_SMALL):
        a = random.randint(LOWER_BOUND_SMALL, UPPER_BOUND_SMALL)
        try:
            b = function(a)
            s = str(a) + " " + str(b) + "\n"
            fd.write(s)
        except:
            continue
    
    for i in range(EXPERIMENTS_NUM_BIG):
        a = random.randint(LOWER_BOUND_BIG, UPPER_BOUND_BIG)
        try:
            b = function(a)
            s = str(a) + " " + str(b) + "\n"
            fd.write(s)
        except:
            continue

    fd.close()

# generating samples for casting to string operator
if(os.path.isfile("StringCasting.txt")):
    print("Detected test for string casting")
else:
    print("Writing tests for string casting")

    fd = open("StringCasting.txt", "w", encoding="utf-8")

    for i in range(EXPERIMENTS_NUM_SMALL):
        a = random.randint(LOWER_BOUND_SMALL, UPPER_BOUND_SMALL)
        fd.write(str(a) + "\n")

    for i in range(EXPERIMENTS_NUM_BIG):
        a = random.randint(LOWER_BOUND_BIG, UPPER_BOUND_BIG)
        fd.write(str(a) + "\n")

    fd.close()

# generating samples for power function
if(os.path.isfile("Power.txt")):
    print("Detected test for power")
else:
    print("Writing tests for power")

    fd = open("Power.txt", "w", encoding="utf-8")

    for i in range(EXPERIMENTS_NUM_SMALL):
        a = random.randint(LOWER_BOUND_SMALL, UPPER_BOUND_SMALL)
        b = random.randint(0, UPPER_BOUND_SMALL)

        try:
            c = a ** b
            s = str(a) + " " + str(b) + " " + str(c) + "\n"
            fd.write(c)
        except:
            continue

    for i in range(EXPERIMENTS_NUM_BIG):
        a = random.randint(LOWER_BOUND_BIG, UPPER_BOUND_BIG)
        b = random.randint(0, UPPER_BOUND_SMALL)

        try:
            c = a ** b
            s = str(a) + " " + str(b) + " " + str(c) + "\n"
            fd.write(c)
        except:
            continue

    fd.close()