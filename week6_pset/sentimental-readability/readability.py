from cs50 import get_string

# Getting the user's input.
userStr = get_string("Text: ")

# Iterating over the user's
# input and determining
# the number of words, letters,
# and sentances.
numWords = 0
numLetters = 0
numSentances = 0
for c in userStr:
    if (c >= "a" and c <= "z") or (c >= "A" and c <= "Z"):
        numLetters += 1
    if c == ".":
        numSentances
