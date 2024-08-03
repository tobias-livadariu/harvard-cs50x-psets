# Defining a function that will
# be used to determine if an inputted
# credit card is valid
def isValid(number)
    # Calculating the digit sum.
    strNumber = str(number)
    strNumber = strNumber[::-1]
    digitSum = 0
    for i in range(0, len(strNumber), 2):
        digitSum += int(strNumber[i])
    for i in range(1, len(strNumber), 2):
        digitSum += (int(strNumber[i] * 2))

    # Finding if the digit sum is valid.
    if digitSum % 10 == 0:
        return True
    else:
        return False

def cardType(number)

