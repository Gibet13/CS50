import cs50

change = 0
coins = 0

change = cs50.get_float("change owed : ")

cents  = change * 100

while True:
    if cents >= 25:
        cents -= 25;
        coins += 1;

    elif cents >= 10 and cents < 25:
        cents -= 10;
        coins += 1;

    elif cents >= 5 and cents < 10:
        cents -= 5;
        coins += 1;

    else:
        cents -= 1;

    if cents == 0:
        break
print(f"{coins} coins")