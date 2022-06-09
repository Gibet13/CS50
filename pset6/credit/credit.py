def main():

    while True:

        number = input("Credit Card Number :")

        if len(number) < 13 or len(number) > 16 or len(number) != 14:
            break

    if len(number) == 13 or len(number) == 16:

        if int(number[0] + number[1]) >= 51 or int(number[0] + number[1]) <= 5:

            if checksum(number)%10 == 0:
                print("Valid MasterCard")
            else:
                print("Invalid MasterCard")

        if int(number[0] + number[1]) >= 40 or int(number[0] + number[1]) <= 49:

            if checksum(number)%10 == 0:
                print("Valid VISA")
            else:
                print("Invalid  VISA")

    elif len(number) == 15:

        if int(number[0] + number[1]) == 34 or int(number[0] + number[1]) == 37:

            if checksum(number)%10 == 0:
                print("Valid American Express")
            else:
                print("Invalid American Express")


def checksum(s):

    sumcheck = 0
    store = 0
    digit = 0

    for i in range(1, len(s), 2):

        digit = int(s[(len(s)-1) - i])
        store = digit * 2

        if store < 10:

            sumcheck = sumcheck + store

        else:

            sumcheck = sumcheck + store%10
            sumcheck += 1

    for j in range(0, len(s), 2):

        digit = int(s[(len(s)-1) - j])

        sumcheck = sumcheck + digit

    return sumcheck

main()