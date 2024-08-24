"""It is important to note that both the apology and login_required
functions were directly taken from the Finance pset's helpers.py file. To support these
functions, the libraries used in Finance's helpers.py file were imported."""

import csv
import datetime
import pytz
import requests

import urllib
import uuid

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
shrink numbers and only show their 'important' parts
based on their size. """
def format_number_suffix(num):
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
