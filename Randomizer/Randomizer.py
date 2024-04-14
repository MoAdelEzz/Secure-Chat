from Crypto.Util import number
import sys 

numOfBits = int(sys.argv[1])
filePath = sys.argv[2]

st = 0
en=-1

if len(sys.argv) >= 4:
    st = int(sys.argv[3])

if len(sys.argv) >= 5:
    en = int(sys.argv[4])

primeNumber = -500

while primeNumber < st or (en != -1 and primeNumber > en): 
    primeNumber = number.getPrime(numOfBits)


with open(filePath, 'w') as file:
    file.write(str(primeNumber)) 


exit(200)