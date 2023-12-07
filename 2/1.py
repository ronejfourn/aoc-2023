import re

sumid = 0
bagcontains = {'red': 12, 'green': 13, 'blue': 14}

with open("input", "r") as inp:
    lines = inp.readlines()
    for i, line in enumerate(lines):
        cubes = re.split('; |, |: ', line[:-1])
        possible = True

        for s in cubes[1:]:
            cube = s.split(' ')
            color = cube[1]
            count = int(cube[0])

            if count > bagcontains[color]:
                possible = False
                break

        if possible:
            sumid += i + 1

print(sumid)
