
blob = open('bits.txt', 'rb').read()

arr = []

for x in blob:
    arr.append(x)

shiftAmount = 1

# Right Shift
prev = 0
for x in arr:
    #print( chr(prev | (x >> shiftAmount)), end='')
    prev = (x << 8 - shiftAmount)


# Left Shift
arr.reverse()
ans = []
prev = 0
for x in arr:
    ans.append((prev | (x << shiftAmount)) & 255)
    prev = ( x >> (8 - shiftAmount) )
ans.append(prev)

ans.reverse()

with open("flag.txt", "w") as f:
    for x in ans:
        f.write(chr(x))