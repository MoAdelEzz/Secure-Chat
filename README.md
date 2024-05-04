# Secure-Chat

# Description
C++ secure chatting application over sockets that uses Deffie Hellman for exchanging session keys, Elgamal Digital Signature for signing key exchange messages and AES for actual messages encryption.

![image](https://github.com/MoAdelEzz/Secure-Chat/assets/96543783/75e55dc7-f4f8-4379-ab10-7e92027daebe)

# Dependencies
- you have to install python 3 version or higher 
- install this package 'pip install pycryptodome'
- install this package 'pip install random2'


# How to Run 
## First Method

1. in Application Directory, run a CMD window
2. run the python script Runner.py using "python Runner.py"
3. this will be enough to open one instance of server and one instance of client 

## Second Method
in case the script didn't work you can do the following
1. in Application/binaries directory open two different terminals
2. to open a server run "SecureChat.exe config_server.txt"
3. to open a client run "SecureChat.exe config_client.txt"

## Changing Keys
in case you want to test another set of keys, a random prime number generator is provided
1. generate a random prime using "RandomPrimeGenerator.py" by running the following command
"python RandomPrimeGenerator.py number_of_bits"
2. in Application/binaries there are two text files "config_server" & "config_client" you can replace the current keys with any prime number you want
# Demo Video

https://github.com/MoAdelEzz/Secure-Chat/assets/96543783/f6889235-7cb2-494b-b285-3fcff46c1952


