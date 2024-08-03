from cs50 import get_int

# Getting the pyramid's
# height from the user.
height = get_int("Height: ")

# Checking if the height
# is valid.
while True:
    if height > 0 and height < 9:
        break
    else:
        print("You must input a integer height value between 1 and 8 inclusively!")
        height = get_int("Height: ")

# Printing out
# the pyramid.
for i in range(height):
    
