def main():

    text = input("Text :")

    textparser(text)

def textparser(s):

    l = len(s)
    letters = 0
    words = 0
    sentences = 0

    for i in range(0, l, 1):

        if s[i] == ' ':
            words += 1

        elif s[i] in{'.','?','!'}:
            sentences += 1

        elif s[i].isupper or s[i].islower:
            letters += 1

    print(f"{letters} letters")
    print(f"{words} words")
    print(f"{sentences} sentences")

    letters = letters * 100/words
    sentences = sentences * 100/words

    textgrade = 0.0588 * letters - 0.296 * sentences - 15.8

    if textgrade < 1:
        print("Grade 1")
    elif textgrade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(textgrade)}")

main()
