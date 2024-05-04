from Crypto.Util import number
import random
import sys 

filePath = sys.argv[1]

lower_bound = int(sys.argv[2])
upper_bound = int(sys.argv[3])

lower_bits = lower_bound.bit_length()
upper_bits = upper_bound.bit_length()

primeNumber = -500

while primeNumber < lower_bound or primeNumber > upper_bound: 
    num_of_bits = random.randint(lower_bits, upper_bits)
    primeNumber = number.getPrime(num_of_bits)


with open(filePath, 'w') as file:
    file.write(str(primeNumber)) 


exit(200)