"""It is important to note that both the apology and login_required
functions were directly taken from the Finance pset's helpers.py file. To support these
functions, the libraries used in Finance's helpers.py file were imported."""

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function

"""Writing a function that can be used to
shrink numbers based on their size using suffixes."""
def formatNumberSuffix(num):
    """
    Format a number with a suffix:
    'k' for thousand,
    'm' for million,
    'b' for billion,
    't' for trillion,
    'q' for quadrillion,
    'Q' for quintillion,
    's' for sextillion,
    'S' for septillion,
    'o' for octillion
    """
    if num >= 1_000_000_000_000_000_000_000_000_000:
        return f"{num / 1_000_000_000_000_000_000_000_000_000:.2f}o"
    elif num >= 1_000_000_000_000_000_000_000_000:
        return f"{num / 1_000_000_000_000_000_000_000_000:.2f}S"
    elif num >= 1_000_000_000_000_000_000_000:
        return f"{num / 1_000_000_000_000_000_000_000:.2f}s"
    elif num >= 1_000_000_000_000_000_000:
        return f"{num / 1_000_000_000_000_000_000:.2f}Q"
    elif num >= 1_000_000_000_000_000:
        return f"{num / 1_000_000_000_000_000:.2f}q"
    elif num >= 1_000_000_000_000:
        return f"{num / 1_000_000_000_000:.2f}t"
    elif num >= 1_000_000_000:
        return f"{num / 1_000_000_000:.2f}b"
    elif num >= 1_000_000:
        return f"{num / 1_000_000:.2f}m"
    elif num >= 1_000:
        return f"{num / 1_000:.2f}k"
    else:
        return str(num)

"""Below are a couple of functions used throughout my program
to determine the cost and power of certain upgrades. """
# Defining a function to calculate the cost of buying the next tier of shovel
# Note that ChatGPT gave me ideas for how this function should look
def calculateShovelCost(curShovel, baseCost, multiplier):
    return int(baseCost * (multiplier ** (curShovel ** 2)))

# Defining a simple exponential function to calculate the cost of buying the next autodigger
def calculateAutodiggerCost(numAutodiggers, baseCost, growthRate):
    return int(baseCost * (growthRate ** numAutodiggers))

# Defining a function to calculate how many skeletons each tier of shovel should provide per click
# Note that, like with the calculateShovelCost function, ChatGPT gave me ideas for this function
def shovelSkeletonsPerClick(curShovel, baseValue=10, polyPower=1.5, exponentialKicker=1.02):
    return int(baseValue * ((curShovel + 1) ** polyPower) * (exponentialKicker ** ((curShovel + 1) ** 0.5)))
