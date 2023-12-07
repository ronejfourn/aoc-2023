def checknum(line):
    nums = [
        'one',
        'two',
        'three',
        'four',
        'five',
        'six',
        'seven',
        'eight',
        'nine'
    ]

    if line[0].isdigit():
        return ord(line[0]) - ord('0')
    else:
        for i, n in enumerate(nums):
            if (line.startswith(n)):
                return i + 1
    return 0


with open("input", "r") as inp:
    sum = 0
    lines = inp.readlines()
    for line in lines:
        num = 0

        while num == 0:
            n = checknum(line)
            if n > 0:
                num = n
            else:
                line = line[1:]
        sum += num * 10

        while line != '':
            n = checknum(line)
            if n > 0:
                num = n
            line = line[1:]
        sum += num

    print(sum)
