import sys as windows
from os import system
import pip


def import_or_install(package, download):
    try:
        __import__(package)
        print("Package (" + package + ") found importing ..." )
    except ImportError:
        print("Package (" + package + ") not found do you want to download it ? (y/n)")
        answer = input()

        if answer[0] == "y":
            print("installing .... (if failed, please try to download it using powershell or raising administration)")
            pip.main(['install', download])

            import_or_install(package, download)
        else:
            print("Exiting ...")


print("Checking For Python Packages Please Wait .....")
import_or_install("Crypto", "pycryptodome")
import_or_install("random", "random2")


print("Initializing Two Instances For Server And Client, Please Standby")

def createCommand(instructions):
    command = ""
    for instruction in instructions:
        command += instruction + " "
    print(command)
    return command

# Define the paths to the executable files
exe_path = "SecureChat.exe"
server_config = "config_server.txt"
client_config = "config_client.txt"


instructions = ["cd", "binaries", "&&", "start", exe_path, server_config]
process = system(createCommand(instructions))

instructions = ["cd", "binaries", "&&", "start", exe_path, client_config]
process = system(createCommand(instructions))

