key = "ETAOINSHRFLCUMPGJBVKXQYDWZ"
alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

map = {}
offset = ord('A')
for i in range(0, 26):
    map = {**map, key[i]: chr(offset + i)}


str = ""
with open("encrypted_text.txt") as file:
    lines = file.readlines()

    for line in lines:
        for character in line:
            if character >= 'A' and character <= 'Z':
                str += map[character]
            else:
                str += character

with open("output.txt", "w") as file:
    file.writelines(str)