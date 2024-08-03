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
    elif c == "." or c == "!" or c == "?":
        numSentances += 1
    elif c == " ":
        numWords += 1

L = numLetters * (100 / numWords)
S = numSentances * (100 / numWords)

# Calculating the colemen-liau index.
index = 0.0588 * L - 0.296 * S - 15.8

# Rounding the index.
index = round(index)

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")
