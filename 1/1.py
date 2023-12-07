with open("input", "r") as inp:
    sum = 0
    lines = inp.readlines()
    for line in lines:
        for c in line[::+1]:
            if c.isdigit():
                sum += (ord(c) - ord('0')) * 10
                break

        for c in line[::-1]:
            if c.isdigit():
                sum += ord(c) - ord('0')
                break

    print(sum)
