#### NOTE: All descriptions were taken from Harvard's problem set specifications for CS50x 2024.
#### [Here is a link to those specifications.](https://cs50.harvard.edu/x/2024/psets/)

## Week 1
### Hello, It's Me
In a file called hello.c in a folder called me, implement a program in C that prompts the user for their name and then says hello to that user. For instance, if the user’s name is Adele, your program should print hello, Adele\n!

### Mario - Harder Version
In a file called mario.c in a folder called mario-more, implement a program in C that recreates that pyramid, using hashes (#) for bricks, as in the below:
<pre>
   #  #
  ##  ##
 ###  ###
####  ####
</pre>

### Credit
A credit (or debit) card, of course, is a plastic card with which you can pay for goods and services. Printed on that card is a number that’s also stored in a database somewhere, so that when your card is used to buy something, the creditor knows whom to bill. There are a lot of people with credit cards in this world, so those numbers are pretty long: American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers. And those are decimal numbers (0 through 9), not binary, which means, for instance, that American Express could print as many as 10^15 = 1,000,000,000,000,000 unique cards! (That’s, um, a quadrillion.)

Actually, that’s a bit of an exaggeration, because credit card numbers actually have some structure to them. All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers which we won’t concern ourselves with for this problem); and all Visa numbers start with 4. But credit card numbers also have a “checksum” built into them, a mathematical relationship between at least one number and others. That checksum enables computers (or humans who like math) to detect typos (e.g., transpositions), if not fraudulent numbers, without having to query a database, which can be slow. Of course, a dishonest mathematician could certainly craft a fake number that nonetheless respects the mathematical constraint, so a database lookup is still necessary for more rigorous checks.

In a file called credit.c in a folder called credit, implement a program in C that checks the validity of a given credit card number.

## Week 2
### Scrabble
In the game of [Scrabble](https://scrabble.hasbro.com/en-us/rules), players create words to score points, and the number of points is the sum of the point values of each letter in the word.
| A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">3</div> | <div style="background-color:#f2f2f2;">3</div> | <div style="background-color:#f2f2f2;">2</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">4</div> | <div style="background-color:#f2f2f2;">2</div> | <div style="background-color:#f2f2f2;">4</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">8</div> | <div style="background-color:#f2f2f2;">5</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">3</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">3</div> | <div style="background-color:#f2f2f2;">10</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">1</div> | <div style="background-color:#f2f2f2;">4</div> | <div style="background-color:#f2f2f2;">8</div> | <div style="background-color:#f2f2f2;">4</div> | <div style="background-color:#f2f2f2;">10</div> |

For example, if we wanted to score the word “CODE”, we would note that the ‘C’ is worth 3 points, the ‘O’ is worth 1 point, the ‘D’ is worth 2 points, and the ‘E’ is worth 1 point. Summing these, we get that “CODE” is worth 7 points.

In a file called scrabble.c in a folder called scrabble, implement a program in C that determines the winner of a short Scrabble-like game. Your program should prompt for input twice: once for “Player 1” to input their word and once for “Player 2” to input their word. Then, depending on which player scores the most points, your program should either print “Player 1 wins!”, “Player 2 wins!”, or “Tie!” (in the event the two players score equal points).

### Readability
According to [Scholastic](https://www.scholastic.com/teachers/teaching-tools/collections/guided-reading-book-lists-for-every-level.html), E.B. White’s Charlotte’s Web is between a second- and fourth-grade reading level, and Lois Lowry’s The Giver is between an eighth- and twelfth-grade reading level. What does it mean, though, for a book to be at a particular reading level?

Well, in many cases, a human expert might read a book and make a decision on the grade (i.e., year in school) for which they think the book is most appropriate. But an algorithm could likely figure that out too!

In a file called readability.c in a folder called readability, you’ll implement a program that calculates the approximate grade level needed to comprehend some text. Your program should print as output “Grade X” where “X” is the grade level computed, rounded to the nearest integer. If the grade level is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output “Grade 16+” instead of giving the exact index number. If the grade level is less than 1, your program should output “Before Grade 1”.

### Substitution
In a substitution cipher, we “encrypt” (i.e., conceal in a reversible way) a message by replacing every letter with another letter. To do so, we use a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when we encrypt it. To “decrypt” the message, the receiver of the message would need to know the key, so that they can reverse the process: translating the encrypt text (generally called ciphertext) back into the original message (generally called plaintext).

A key, for example, might be the string NQXPOMAFTRHLZGECYJIUWSKDVB. This 26-character key means that A (the first letter of the alphabet) should be converted into N (the first character of the key), B (the second letter of the alphabet) should be converted into Q (the second character of the key), and so forth.

A message like HELLO, then, would be encrypted as FOLLE, replacing each of the letters according to the mapping determined by the key.

In a file called substitution.c in a folder called substitution, create a program that enables you to encrypt messages using a substitution cipher. At the time the user executes the program, they should decide, by providing a command-line argument, on what the key should be in the secret message they’ll provide at runtime.

## Week 3
### Sort
Recall from lecture that we saw a few algorithms for sorting a sequence of numbers: selection sort, bubble sort, and merge sort.

- **Selection sort** iterates through the unsorted portions of a list, selecting the smallest element each time and moving it to its correct location.
- **Bubble sort** compares pairs of adjacent values one at a time and swaps them if they are in the incorrect order. This continues until the list is sorted.
- **Merge sort** recursively divides the list into two repeatedly and then merges the smaller lists back into a larger one in the correct order.

In this problem, you’ll analyze three (compiled!) sorting programs to determine which algorithms they use. In a file called answers.txt in a folder called sort, record your answers, along with an explanation for each program, by filling in the blanks marked TODO.

### Plurality
Elections come in all shapes and sizes. In the UK, the [Prime Minister](https://www.parliament.uk/education/about-your-parliament/general-elections/) is officially appointed by the monarch, who generally chooses the leader of the political party that wins the most seats in the House of Commons. The United States uses a multi-step [Electoral College](https://www.archives.gov/federal-register/electoral-college/about.html) process where citizens vote on how each state should allocate Electors who then elect the President.

Perhaps the simplest way to hold an election, though, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” or “winner take all”). In the plurality vote, every voter gets to vote for one candidate. At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

For this problem, you’ll implement a program that runs a plurality election, per the below.

### Tideman
You already know about plurality elections, which follow a very simple algorithm for determining the winner of an election: every voter gets one vote, and the candidate with the most votes wins.

But the plurality vote does have some disadvantages. What happens, for instance, in an election with three candidates, and the ballots below are cast?

**Ballot 1**  
Alice

**Ballot 2**  
Alice

**Ballot 3**  
Bob

**Ballot 4**  
Bob

**Ballot 5**  
Charlie

A plurality vote would here declare a tie between Alice and Bob, since each has two votes. But is that the right outcome?

There's another kind of voting system known as a ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate. Instead of just voting for their top choice, they can rank the candidates in order of preference. The resulting ballots might therefore look like the below.

**Ballot 1**  
1. Alice  
2. Bob  
3. Charlie

**Ballot 2**  
1. Alice  
2. Charlie  
3. Bob

**Ballot 3**  
1. Bob  
2. Alice  
3. Charlie

**Ballot 4**  
1. Bob  
2. Alice  
3. Charlie

**Ballot 5**  
1. Charlie  
2. Alice  
3. Bob

Here, each voter, in addition to specifying their first preference candidate, has also indicated their second and third choices. And now, what was previously a tied election could now have a winner. The race was originally tied between Alice and Bob. But the voter who chose Charlie preferred Alice over Bob, so Alice could here be declared the winner.

Ranked choice voting can also solve yet another potential drawback of plurality voting. Take a look at the following ballots.

**Ballot 1**  
1. Alice  
2. Charlie  
3. Bob

**Ballot 2**  
1. Alice  
2. Charlie  
3. Bob

**Ballot 3**  
1. Bob  
2. Alice  
3. Charlie

**Ballot 4**  
1. Bob  
2. Alice  
3. Charlie

**Ballot 5**  
1. Bob  
2. Alice  
3. Charlie

**Ballot 6**  
1. Charlie  
2. Alice  
3. Bob

**Ballot 7**  
1. Charlie  
2. Alice  
3. Bob

**Ballot 8**  
1. Charlie  
2. Alice  
3. Bob

**Ballot 9**  
1. Charlie  
2. Bob  
3. Alice

Who should win this election? In a plurality vote where each voter chooses their first preference only, Charlie wins this election with four votes compared to only three for Bob and two for Alice. (Note that, if you're familiar with the instant runoff voting system, Charlie wins here under that system as well). Alice, however, might reasonably make the argument that she should be the winner of the election instead of Charlie: after all, of the nine voters, a majority (five of them) preferred Alice over Charlie, so most people would be happier with Alice as the winner instead of Charlie.

Alice is, in this election, the so-called "Condorcet winner" of the election: the person who would have won any head-to-head matchup against another candidate. If the election had been just Alice and Bob, or just Alice and Charlie, Alice would have won.

The Tideman voting method (also known as "ranked pairs") is a ranked-choice voting method that's guaranteed to produce the Condorcet winner of the election if one exists. In a file called `tideman.c` in a folder called `tideman`, create a program to simulate an election by the Tideman voting method.

## Week 4
### Volume
[WAV files](https://docs.fileformat.com/audio/wav/) are a common file format for representing audio. WAV files store audio as a sequence of “samples”: numbers that represent the value of some audio signal at a particular point in time. WAV files begin with a 44-byte “header” that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample. After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.

Scaling each sample value by a given factor has the effect of changing the volume of the audio. Multiplying each sample value by 2.0, for example, will have the effect of doubling the volume of the origin audio. Multiplying each sample by 0.5, meanwhile, will have the effect of cutting the volume in half.

In a file called volume.c in a folder called volume, write a program to modify the volume of an audio file.

### Filter - Harder Version


## Week 5

## Week 6

## Week 7

## Week 8

## Week 9
