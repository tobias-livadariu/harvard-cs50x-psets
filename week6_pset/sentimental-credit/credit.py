# Defining a function that will
# be used to determine if an inputted
# credit card is valid
def isValid(number)
    strNumber = str(number)
    digitSum = 0
    for i in range(0, len(strNumber), 2):
        digitSum += int(strNumber[i])
    for i in range(1, len(strNumber), 2):
        digitSum += (int(strNumber[i] * 2))

