import csv
import sys


def main():
    # Check for command-line usage.
    commandLineArgs = sys.argv
    if (len(commandLineArgs) != 3):
        print("Usage: python dna.py [csv file containing STR counts] [txt file contianing the DNA sequence]")
        return

    # Read database file into a variable.
    with open(commandLineArgs[1], "r") as file:
        database = list(csv.DictReader(file))

    # Read DNA sequence file into a variable.
    with open(commandLineArgs[2], "r") as file:
        dnaSequence = file.read()

    # Find longest match of each STR in DNA sequence.
    strCounts = {}
    for key in database[0].keys():
        if key != "name":
            strCounts[key] = longest_match(dnaSequence, key)

    # TODO: Check database for matching profiles
    isFound = False
    matches = 0
    for row in database:
        if isFound == True:
            break
        for key in database[0].keys():
            if key == "name":
                continue
            elif int(row[key]) == strCounts[key]:
                matches += 1
        if matches == len(database[0]) - 1:
            print(row["name"])
            isFound = True
        matches = 0
    if isFound == False:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
