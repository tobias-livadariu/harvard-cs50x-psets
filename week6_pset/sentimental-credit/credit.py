from cs50 import get_int

# Defining a function that will
# be used to determine if an inputted
# credit card is valid.
def isValid(number):
    # Calculating the digit sum.
    strNumber = str(number)
    strNumber = strNumber[::-1]
    digitSum = 0
    for i in range(0, len(strNumber), 2):
        digitSum += int(strNumber[i])
    for i in range(1, len(strNumber), 2):
        numAdding = int(strNumber[i]) * 2
        if numAdding > 9:
            digitSum += numAdding % 10

    # Finding if the digit sum is valid.
    if digitSum % 10 == 0:
        return True
    else:
        return False

# Defining a function that will
# be used to determine the
# type of a card number.
def cardType(number):
    strNumber = str(number)
    firstTwoDigits = strNumber[:2]
    firstTwoDigits = int(firstTwoDigits)
    if (len(strNumber) == 15) and (firstTwoDigits == 34 or firstTwoDigits == 37):
        return "AMEX"
    elif (len(strNumber) == 16) and (firstTwoDigits > 50 and firstTwoDigits < 56):
        return "MASTERCARD"
    elif (len(strNumber) == 13 or len(strNumber) == 16) and (strNumber[0] == "4"):
        return "VISA"
    else:
        return "INVALID"

# Getting user input and
# running the functions defined
# above.
def main():
    cardNumber = get_int("Number: ")
    isValidNum = isValid(cardNumber)
    if isValidNum == False:
        print("INVALID")
        return 1
    userCardType = cardType(cardNumber)
    print(userCardType)

main()
