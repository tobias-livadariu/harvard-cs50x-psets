"""Note that the following sqlite3 table creation prompt
was heavily inspired by the 'users' table used in Finance.

CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL,
    skeletonCount INTEGER NOT NULL DEFAULT 0,
    totalSkeletons INTEGER NOT NULL DEFAULT 0
);
CREATE TABLE sqlite_sequence(name,seq);
CREATE UNIQUE INDEX username ON users (username);
CREATE TABLE simple_upgrades (
    user_id INTEGER
);
CREATE TABLE stats ::todo
"""

"""Note that the libraries imported below were taken
from the Finance pset."""
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

# Configuring the flask application
app = Flask(__name__)

"""The three blocks of code below were taken from Finance in the
week 9 pset.

The purpose of the first block is to allow Flask to use server-side sessions
rather than cookies on the client side, helping to support user sessions
such as logging in and out.

The purpose of the second block (more like a single line) is to link the
calcium_clicker.db sqlite3 database to the db variable using the cs50 library,
allowing sqlite3 prompts to be run directly within the app.py file.

The purpose of the third block is to ensure that user responses in my
web app are not cached in their browser. This is important because
information in my app changes very quickly, and I need to ensure that users
always see the most up-to-date information.
"""
# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///calcium_clicker.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Defining the list of shovels that the user can buy
shovels = ["Wooden", "Stone", "Iron", "Gold", "Diamond", "Mythril", "Adamantite", "Runeite", "Dragon", "Infernal", "Super"]
maxShovel = len(shovels) - 1

"""Updating the skeleton count asyncronously through AJAX without
visually refreshing the webpage. Note that the code below is my own,
but ChatGPT gave me the idea to use AJAX."""
@app.route("/digUpSkeletons", methods=["POST"])
@login_required
def digUpSkeletons():
    # Updating the skeleton count and total skeleton count
    db.execute("UPDATE users SET skeletonCount = skeletonCount + 1 WHERE id = ?", session["user_id"])
    db.execute("UPDATE users SET totalSkeletons = totalSkeletons + 1 WHERE id = ?", session["user_id"])
    # Fetching the updating skeleton count
    skeletonCountRow = db.execute("SELECT skeletonCount FROM users WHERE id = ?", session["user_id"])
    skeletonCount = skeletonCountRow[0]["skeletonCount"]
    # Returning the updated skeleton count as JSON
    return jsonify({"skeletonCount": skeletonCount})

"""Updating the number of autodiggers that the user has
through AJAX."""
@app.route("/buyAutodigger", methods=["POST"])
@login_required
def buyAutodigger():
    #TODO: implement

"""Updating the user's shovel through AJAX."""
@app.route("/buyShovel", methods=["POST"])
@login_required
def buyShovel():
    #TODO: implement

@app.route("/refreshStats", methods=["GET"])
@login_required
def refreshStats():
    #TODO: implement

@app.route("/", methods=["GET"])
@login_required #NOTE: the @login_required decorator was taken from Finance
def index():
    # If the homepage was accessed via get, rendering it.
    # Getting the current skeleton count
    skeletonCountRow = db.execute("SELECT skeletonCount FROM users WHERE id = ?", session["user_id"])
    skeletonCount = skeletonCountRow[0]["skeletonCount"]
    # Getting the total skeleton count
    totalSkeletonsRow = db.execute("SELECT skeletonCount FROM users WHERE id = ?", session["user_id"])
    totalSkeletons = totalSkeletonsRow[0]["totalSkeletons"]
    return render_template("index.html", skeletonCount=skeletonCount, totalSkeletons=totalSkeletons)

"""NOTE: the login route was taken from my work in Finance."""
@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

"""NOTE: the logout route was taken from the distribution code
in Finance."""
@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

"""NOTE: the register route was taken from my work in Finance."""
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        """Checking if the user's input is valid."""
        if not username:
            return apology("You must choose a username!")

        if not password:
            return apology("You must choose a password!")

        if not confirmation:
            return apology("You must confirm your password in the \"Confirm Password\" box!")

        if password != confirmation:
            return apology("Your original password and confirmation password did not match!")

        # Generating an incrypted hash of the password.
        passwordHash = generate_password_hash(password)

        # Inserting into the users table, and checking if the username was duplicated.
        # This works because, if the username was duplicated, trying to insert into the
        # table with that username will throw an error.
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, passwordHash)
        except:
            return apology("Sorry, the username you have selected is already taken! Please choose a different username.")

        # Logging the user in and redirecting them if they were added successfully
        # to the database.
        sessionPacked = db.execute(
            "SELECT id FROM users WHERE (username = ?) AND (hash = ?)", username, passwordHash)
        session["user_id"] = sessionPacked[0]["id"]

        # Redirecting the user
        return redirect("/")

    """If the register page was accessed via "get", displaying it to the user."""
    return render_template("register.html")
