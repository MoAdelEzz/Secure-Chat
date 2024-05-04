from Crypto.Util import number
import random
from sys import argv

number_of_bits = int(argv[1])
primeNumber = number.getPrime(number_of_bits)

print(primeNumber)