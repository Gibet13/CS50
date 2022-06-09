import csv
import sys

def main():

    # Verify the number of arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE SEQUENCE")

    individuals = []
    STR = []

    # Assing names to each argument
    file1 = sys.argv[1]
    file2 = sys.argv[2]

    with open(file1) as database:

        reader = csv.DictReader(database)
        STR = reader.fieldnames
        for name in reader:
            for i in range(1, len(STR)):
                name[STR[i]] = int(name[STR[i]])
                individuals.append(name)

    print(STR)

    with open(file2) as subject:

            sequence = subject.read()

    STR_result = {}

    for i in range(1, len(STR)):

        STR_result[STR[i]] = STR_count(sequence, STR[i])

    print(STR_result)

    for name in individuals:

        match = False

        for i in range(1, len(STR)):

            if STR_result[STR[i]] == name[STR[i]]:

                match = True

            else:
                match = False
                break
        if match:

            print(name)
            break
    if not match:

        print("No match")

# Count the number of STR
def STR_count(s, seq):


    highest = 0

    for i in range(0, len(s), 1):

        repeat = 0

        if s[i:i + len(seq)] == seq:

            repeat += 1
            j = i

            while True:

                j += len(seq)

                if s[j:j + len(seq)] == seq:

                    repeat += 1
                else:
                    break

        if repeat > highest:
            highest = repeat

    return highest

main()
