import re

sumpower = 0

with open("input", "r") as inp:
    lines = inp.readlines()
    for line in lines:
        cubes = re.split('; |, |: ', line[:-1])
        minrequired = {}

        for s in cubes[1:]:
            cube = s.split(' ')
            color = cube[1]
            count = int(cube[0])

            if count > minrequired.get(color, 0):
                minrequired[color] = count

        power = 1
        for count in minrequired.values():
            power *= count
        sumpower += power

print(sumpower)
