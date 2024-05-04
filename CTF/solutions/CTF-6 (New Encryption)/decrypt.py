import string

START = ord("a")
CHARSET = string.ascii_lowercase[:16]

def decode_b16(encoded):
  decoded = ""
  for i in range(0, len(encoded), 2):
    first_char_index = CHARSET.index(encoded[i])
    second_char_index = CHARSET.index(encoded[i+1])
    binary = f"{first_char_index:04b}{second_char_index:04b}"
    # print(int(binary, 2),"-",chr(int(binary, 2)))
    decoded += chr(int(binary, 2))
  return decoded

def inv_caesar_shift(m, k):
    return CHARSET[(CHARSET.find(m) - 1 - ord(k) + 2 * START) % len(CHARSET)]


enc = "jikmkjgekjkckjkbknkjlhgekflgkjgekbkfkpknkcklgekfgekbkdlkkjgcgejlkjgekckjkjkigelikdgekfkhligekkkflhligc"
# hint: key is a single letter
key = "e"

b16 = ""

for i, m in enumerate(enc):
    b16 += inv_caesar_shift(m, key[i % len(key)])

txt = decode_b16(b16)

with open("flag.txt", "w") as f:
   f.writelines(txt)

