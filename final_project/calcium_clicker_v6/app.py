"""Note that the following sqlite3 table creation prompts
were inspired by the tables used in Finance.

CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL,
    skeletonCount INTEGER NOT NULL DEFAULT 0,
    totalSkeletons INTEGER NOT NULL DEFAULT 0
);
CREATE TABLE sqlite_sequence(name,seq);
CREATE UNIQUE INDEX username ON users (username);
CREATE TABLE stats (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    skeletonsPerClick INTEGER NOT NULL DEFAULT 1,
    skeletonsPerSecond INTEGER NOT NULL DEFAULT 0,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);
CREATE TABLE simple_upgrades (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    curShovel INTEGER NOT NULL DEFAULT 0,
    shovelCost INTEGER NOT NULL DEFAULT 100,
    numAutodiggers INTEGER NOT NULL DEFAULT 0,
    autodiggerCost INTEGER NOT NULL DEFAULT 10,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);
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
shovels = ["Wooden", "Stone", "Iron", "Gold", "Diamond", "Mythril", "Adamantite", "Runeite", "Dragon", "Infernal", "Masterwork"]
maxShovel = len(shovels) - 1

# Defining a function to calculate the cost of buying the next tier of shovel
# Note that ChatGPT gave me ideas for how this function should look
def calculateShovelCost(curShovel, baseCost, multiplier):
    return int(baseCost * (multiplier ** (curShovel ** 2)))

# Defining a function to calculate the cost of buying the next autodigger
# Note that, like with the calculateShovelCost function, ChatGPT gave me ideas for this function
def calculateAutodiggerCost(numAutodiggers, baseCost, multiplier, exponent):
    return int(baseCost * (1 + multiplier * numAutodiggers) ** exponent)

# Defining a function to calculate how many skeletons each tier of shovel should provide per click
def shovelSkeletonsPerClick(curShovel, baseValue=10, polyPower=1.5, exponentialKicker=1.02):
    return int(baseValue * (curShovel ** polyPower) * (exponentialKicker ** (curShovel ** 0.5)))

"""Updating the skeleton count asyncronously through AJAX without
visually refreshing the webpage. Note that the code below is my own,
but ChatGPT gave me the idea to use AJAX."""
@app.route("/digUpSkeletons", methods=["POST"])
@login_required
def digUpSkeletons():
    # Updating skeletonCount and totalSkeletons in one go and retrieving all values
    updatedValues = db.execute("""
        UPDATE users
        SET skeletonCount = skeletonCount + (SELECT skeletonsPerClick FROM stats WHERE user_id = ?),
            totalSkeletons = totalSkeletons + (SELECT skeletonsPerClick FROM stats WHERE user_id = ?)
        WHERE id = ?
        RETURNING skeletonCount, totalSkeletons
    """, session["user_id"], session["user_id"], session["user_id"])[0]

    skeletonCount = updatedValues["skeletonCount"]
    totalSkeletons = updatedValues["totalSkeletons"]

    # Returning the updated skeleton count as JSON
    return jsonify({"skeletonCount": skeletonCount, "totalSkeletons": totalSkeletons})

"""Updating the number of autodiggers that the user has
through AJAX."""
@app.route("/buyAutodigger", methods=["POST"])
@login_required
def buyAutodigger():
    # Fetching autodiggerCost and skeletonCount in one go
    user_data = db.execute("""SELECT skeletonCount, autodiggerCost, numAutodiggers FROM users
                           INNER JOIN simple_upgrades ON users.id = simple_upgrades.user_id
                           WHERE users.id = ?""", session["user_id"])[0]
    skeletonCount = user_data["skeletonCount"]
    autodiggerCost = user_data["autodiggerCost"]
    numAutodiggers = user_data["numAutodiggers"]

    if skeletonCount < autodiggerCost:
        return jsonify({"wasSuccessful": False})

    # Calculating the new number of autodiggers and the updated cost
    newNumAutodiggers = numAutodiggers + 1
    newAutodiggerCost = calculateAutodiggerCost(numAutodiggers=newNumAutodiggers, baseCost=10, multiplier=0.05, exponent=2)

    # Updating skeletonCount, numAutodiggers, and autodiggerCost in one go
    updatedValues = db.execute("""
        UPDATE users
        SET skeletonCount = skeletonCount - ?
        WHERE id = ?;

        UPDATE simple_upgrades
        SET numAutodiggers = ?, autodiggerCost = ?
        WHERE user_id = ?
        RETURNING numAutodiggers, autodiggerCost;
    """, autodiggerCost, session["user_id"], newNumAutodiggers, newAutodiggerCost, session["user_id"])[0]

    # Returning the updated values as JSON
    return jsonify({"wasSuccessful": True, "numAutodiggers": updatedValues["numAutodiggers"], "autodiggerCost": updatedValues["autodiggerCost"], "skeletonCount": skeletonCount - autodiggerCost})

"""Updating the user's shovel through AJAX."""
@app.route("/buyShovel", methods=["POST"])
@login_required
def buyShovel():
    # Checking if the user can afford a shovel upgrade
    shovelCost = db.execute("SELECT shovelCost FROM simple_upgrades WHERE user_id = ?", session["user_id"])[0]["shovelCost"]
    skeletonCount = db.execute("SELECT skeletonCount FROM users WHERE id = ?", session["user_id"])[0]["skeletonCount"]
    if skeletonCount < shovelCost:
        # Returning False so that the program knows that the transaction failed
        return jsonify({"wasSuccessful": False})

    # If the transaction was succesful, updating the user's skeletonCount
    db.execute("UPDATE users SET skeletonCount = skeletonCount - ? WHERE id = ?", shovelCost, session["user_id"])
    # Getting the new skeleteonCount
    skeletonCount = db.execute("SELECT skeletonCount FROM users WHERE id = ?", session["user_id"])[0]["skeletonCount"]

    # Updating the user's shovel level
    db.execute("UPDATE simple_upgrades SET curShovel = curShovel + 1 WHERE user_id = ?", session["user_id"])
    # Fetching the updated shovel level
    curShovelRow = db.execute("SELECT curShovel FROM simple_upgrades WHERE user_id = ?", session["user_id"])
    curShovel = curShovelRow[0]["curShovel"]
    # Determining the updated cost for a new shovel
    shovelCost = calculateShovelCost(curShovel=curShovel, baseCost=100, multiplier=1.5)
    db.execute("UPDATE simple_upgrades SET shovelCost = ? WHERE user_id = ?", shovelCost, session["user_id"])
    # Returning the updated shovel values as JSON
    return jsonify({"wasSuccessful": True, "curShovel": curShovel, "shovelCost": shovelCost, "shovels": shovels, "maxShovel": maxShovel, "skeletonCount": skeletonCount})

@app.route("/updateStats", methods=["POST"])
@login_required
def updateStats():
    # Getting the user's current shovel level and current autodigger count
    simpleUpgrades = db.execute("SELECT numAutodiggers, curShovel FROM simple_upgrades WHERE user_id = ?", session["user_id"])
    numAutodiggers = simpleUpgrades["numAutodiggers"]
    curShovel = simpleUpgrades["curShovel"]

    # Determining the user's skeletonsPerClick and skeletonsPerSecond
    skeletonsPerClick = shovelSkeletonsPerClick(curShovel, baseValue=10, polyPower=1.5, exponentialKicker=1.02)
    skeletonsPerSecond = numAutodiggers

    # Refreshing the value in skeletonsPerClick and skeletonsPerSecond
    db.execute("UPDATE stats SET skeletonsPerClick = ?, skeletonsPerSecond = ? WHERE user_id = ?", skeletonsPerClick, skeletonsPerSecond, session["user_id"])
    # Returning the updated values as JSON
    return jsonify({"skeletonsPerClick": skeletonsPerClick, "skeletonsPerSecond": skeletonsPerSecond})

@app.route("/perSecondOperations", methods=["POST"])
@login_required
def perSecondOperations():
    # Fetching the current skeletons per second
    skeletonsPerSecond = db.execute("SELECT skeletonsPerSecond FROM stats WHERE user_id = ?", session["user_id"])[0]["skeletonsPerSecond"]

    # Updating the skeletonCount and totalSkeletons variables
    db.execute("UPDATE users SET skeletonCount = skeletonCount + ?, totalSkeletons = totalSkeletons + ? WHERE id = ?", skeletonsPerSecond, skeletonsPerSecond, session["user_id"])

    # Returning the skeletonsPerSecond value as JSON
    return jsonify({"skeletonsPerSecond": skeletonsPerSecond})

@app.route("/", methods=["GET"])
@login_required #NOTE: the @login_required decorator was taken from Finance
def index():
    # Rendering the webpage
    # Getting the current and total skeleton counts
    usersRow = db.execute("SELECT skeletonCount, totalSkeletons FROM users WHERE id = ?", session["user_id"])
    users = usersRow[0]
    skeletonCount = users["skeletonCount"]
    totalSkeletons = users["totalSkeletons"]

    # Getting the current autodigger count, shovel level, and price for the next simple upgrades
    simpleUpgradesRow = db.execute("SELECT curShovel, shovelCost, numAutodiggers, autodiggerCost FROM simple_upgrades WHERE user_id = ?", session["user_id"])
    simpleUpgrades = simpleUpgradesRow[0]
    curShovel = simpleUpgrades["curShovel"]
    shovelCost = simpleUpgrades["shovelCost"]
    numAutodiggers = simpleUpgrades["numAutodiggers"]
    autodiggerCost = simpleUpgrades["autodiggerCost"]

    # Getting the current skeletons per click and skeletons per second
    statsRow = db.execute("SELECT skeletonsPerClick, skeletonsPerSecond FROM stats WHERE user_id = ?", session["user_id"])
    stats = statsRow[0]
    skeletonsPerClick = stats["skeletonsPerClick"]
    skeletonsPerSecond = stats["skeletonsPerSecond"]

    return render_template("index.html", skeletonCount=skeletonCount, totalSkeletons=totalSkeletons, curShovel=curShovel, shovelCost=shovelCost, numAutodiggers=numAutodiggers,
                           autodiggerCost=autodiggerCost, skeletonsPerClick=skeletonsPerClick, skeletonsPerSecond=skeletonsPerSecond, shovels=shovels, maxShovel=maxShovel)

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

        # Inserting a row into every table in the database for the new user
        db.execute("INSERT INTO stats (user_id) VALUES (?)", session["user_id"])
        db.execute("INSERT INTO simple_upgrades (user_id) VALUES (?)", session["user_id"])

        # Redirecting the user
        return redirect("/")

    """If the register page was accessed via "get", displaying it to the user."""
    return render_template("register.html")
