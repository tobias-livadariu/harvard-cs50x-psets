import csv
import sys


def main():
    # Check for command-line usage.
    commandLineArgs = sys.argv
    if (len(commandLineArgs) != 3):
        print("Usage: python dna.py [csv file containing STR counts] [txt file contianing the DNA sequence]")
        return

    # Read database file into a variable.
    database = csv.DictReader(sys.argv[1])

    # Read DNA sequence file into a variable.
    dnaSequence = open(sys.argv[2], "r")

    # Find longest match of each STR in DNA sequence.
    strCounts = {}
    for i in range(1, len(database.fieldnames)):
        curSTR = database.fieldnames[i]
        strCounts[curSTR] = longest_match(dnaSequence, curSTR)

    # TODO: Check database for matching profiles
    isFound = False
    for row in database:
        if isFound == True:
            break
        for i in range(1, len(database.fieldnames)):
            curSTR = database.fieldnames[i]
            if row[curSTR] != strCounts[curSTR]:
                break
            print(row["name"])
            isFound = True
    if isFound == False:
        print("No match")

    close(dnaSequence)
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
