- this part of code is a mixture of both cpp and python as i'm using a python package pycrypto to generate the prime number and the communication is done 
using text file where the cpp program initialize python instance and wait untill it finishes and writes the generated prime number in the file


- to call the python process
    - python Randomizer.py [num_of_bits] [output_file_name] {start_range} {end_range}