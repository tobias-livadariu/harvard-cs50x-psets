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

from helpers import apology, login_required, formatNumberSuffix, calculateShovelCost, calculateAutodiggerCost, shovelSkeletonsPerClick

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

# Registering Jinja2 filters
app.jinja_env.filters['formatNumberSuffix'] = formatNumberSuffix
app.jinja_env.filters['shovelSkeletonsPerClick'] = shovelSkeletonsPerClick

# Defining the list of shovels that the user can buy
shovels = ["Wooden", "Stone", "Iron", "Gold", "Diamond", "Mythril", "Adamantite", "Runeite", "Dragon", "Infernal", "Masterwork"]
maxShovel = len(shovels) - 1

"""Updating the skeleton count asyncronously through AJAX without
visually refreshing the webpage. Note that the code below is my own,
but ChatGPT gave me the idea to use AJAX."""
@app.route("/digUpSkeletons", methods=["POST"])
@login_required
def digUpSkeletons():
    # Update skeletonCount and totalSkeletons in the users table using a subquery to fetch skeletonsPerClick
    db.execute("""
        UPDATE users
        SET skeletonCount = skeletonCount + (SELECT skeletonsPerClick FROM stats WHERE user_id = ?),
            totalSkeletons = totalSkeletons + (SELECT skeletonsPerClick FROM stats WHERE user_id = ?)
        WHERE id = ?
    """, session["user_id"], session["user_id"], session["user_id"])

    # Fetch the updated skeletonCount and totalSkeletons values
    updatedValues = db.execute("SELECT skeletonCount, totalSkeletons FROM users WHERE id = ?", session["user_id"])[0]

    # Unpack the updatedValues dictionary
    skeletonCount = updatedValues["skeletonCount"]
    totalSkeletons = updatedValues["totalSkeletons"]

    # Returning the updated skeleton count as JSON
    return jsonify({"skeletonCount": skeletonCount, "totalSkeletons": totalSkeletons})

"""Updating the number of autodiggers that the user has
through AJAX."""
@app.route("/buyAutodigger", methods=["POST"])
@login_required
def buyAutodigger():
    # Getting the values of num and cost from the route's request args
    numBuying = request.args.get("numBuying", type=int)
    numAutodiggers = request.args.get("numAutodiggers", type=int)
    cost = request.args.get("cost", type=int)
    skeletonCount = request.args.get("skeletonCount", type=int)

    # If all required parameters are provided, use them to process the bulk purchase
    if (numBuying is not None) and (numAutodiggers is not None) and (cost is not None) and (skeletonCount is not None):
        # Ensure the user has enough skeletons
        if skeletonCount < cost:
            return jsonify({"wasSuccessful": False, "message": "Not enough skeletons"})

        # Updating values in all pertinent variables
        skeletonCount -= cost
        numAutodiggers += numBuying
        autodiggerCost = calculateAutodiggerCost(numAutodiggers=numAutodiggers, baseCost=10, growthRate=1.15)

        # Updating the database
        db.execute("UPDATE users SET skeletonCount = ? WHERE id = ?", skeletonCount, session["user_id"])
        db.execute("UPDATE simple_upgrades SET numAutodiggers = ?, autodiggerCost = ? WHERE user_id = ?", numAutodiggers, autodiggerCost, session["user_id"])

    # Running an alternate route if not all request argument variables exist
    else:
        # Fetching autodiggerCost, numAutodiggers, and skeletonCount in one go
        userData = db.execute("""SELECT skeletonCount, autodiggerCost, numAutodiggers FROM users
                            INNER JOIN simple_upgrades ON users.id = simple_upgrades.user_id
                            WHERE users.id = ?""", session["user_id"])[0]
        skeletonCount = userData["skeletonCount"]
        autodiggerCost = userData["autodiggerCost"]
        numAutodiggers = userData["numAutodiggers"]

        if skeletonCount < autodiggerCost:
            return jsonify({"wasSuccessful": False})

        # Updating the user's skeletonCount value
        skeletonCount -= autodiggerCost

        # Calculating the new number of autodiggers and the updated cost
        numAutodiggers = numAutodiggers + 1
        autodiggerCost = calculateAutodiggerCost(numAutodiggers=numAutodiggers, baseCost=10, growthRate=1.15)

        # Updating skeletonCount
        db.execute("UPDATE users SET skeletonCount = ? WHERE id = ?", skeletonCount, session["user_id"])

        # Updating numAutodiggers and autodiggerCost in one go
        db.execute("UPDATE simple_upgrades SET numAutodiggers = ?, autodiggerCost = ? WHERE user_id = ?", numAutodiggers, autodiggerCost, session["user_id"])
    # Returning the updated values as JSON
    return jsonify({"wasSuccessful": True, "numAutodiggers": numAutodiggers, "autodiggerCost": autodiggerCost, "skeletonCount": skeletonCount})

"""Determining the max number of autodiggers that
the user is able to buy."""
@app.route("/numAutodiggersBuyable", methods=["POST"])
@login_required
def numAutodiggersBuyable():
    # Fetching numAutodiggers and skeletonCount in one search
    userData = db.execute("""SELECT skeletonCount, numAutodiggers FROM users
                           INNER JOIN simple_upgrades ON users.id = simple_upgrades.user_id
                           WHERE users.id = ?""", session["user_id"])[0]
    skeletonCount = userData["skeletonCount"]
    numAutodiggers = userData["numAutodiggers"]

    # Defining a variable to hold the number of autodiggers the user can buy
    # And the amount that the max number of autodiggers would cost
    numAutodiggersBuyable = 0
    costAutodiggersBuyable = {
        "costForTen": 0,
        "costForMax": 0
    }

    # Using a while True loop to determine the max number of autodiggers the user can buy
    while True:
        nextCost = calculateAutodiggerCost(numAutodiggers=(numAutodiggers + numAutodiggersBuyable), baseCost=10, growthRate=1.15)

        # Break if the accumulated cost considering the next autodigger's cost exceeds the user's skeleton count
        if costAutodiggersBuyable["costForMax"] + nextCost > skeletonCount:
            break

        # Accumulate costs
        costAutodiggersBuyable["costForMax"] += nextCost
        if numAutodiggersBuyable < 10:
            costAutodiggersBuyable["costForTen"] += nextCost

        numAutodiggersBuyable += 1


    # Returning the maximum number of autodiggers that the user can buy
    return jsonify({
        "numAutodiggersBuyable": numAutodiggersBuyable,
        "costForTen": costAutodiggersBuyable["costForTen"],
        "costForMax": costAutodiggersBuyable["costForMax"],
        "numAutodiggers": numAutodiggers,
        "skeletonCount": skeletonCount
    })

"""Updating the user's shovel through AJAX."""
@app.route("/buyShovel", methods=["POST"])
@login_required
def buyShovel():
    # Fetching shovelCost, skeletonCount, and curShovel in one query
    userShovelData = db.execute("""
        SELECT users.skeletonCount, simple_upgrades.shovelCost, simple_upgrades.curShovel
        FROM users
        JOIN simple_upgrades ON users.id = simple_upgrades.user_id
        WHERE users.id = ?
    """, session["user_id"])[0]

    skeletonCount = userShovelData["skeletonCount"]
    shovelCost = userShovelData["shovelCost"]
    curShovel = userShovelData["curShovel"]

    if skeletonCount < shovelCost:
        return jsonify({"wasSuccessful": False})

    # Updating skeletonCount and curShovel, calculating new shovelCost
    skeletonCount -= shovelCost
    curShovel += 1
    shovelCost = calculateShovelCost(curShovel=curShovel, baseCost=100, multiplier=1.5)

    # Updating the user's skeletonCount value
    db.execute("UPDATE users SET skeletonCount = ? WHERE id = ?", skeletonCount, session["user_id"])

    # Updating the user's curShovel and shovelCost values
    db.execute("UPDATE simple_upgrades SET curShovel = ?, shovelCost = ? WHERE user_id = ?", curShovel, shovelCost, session["user_id"])

    # Returning the updated shovel values as JSON
    return jsonify({"wasSuccessful": True, "curShovel": curShovel, "shovelCost": shovelCost, "shovels": shovels, "maxShovel": maxShovel, "skeletonCount": skeletonCount})

@app.route("/updateStats", methods=["POST"])
@login_required
def updateStats():
    # Getting the user's current shovel level and current autodigger count
    simpleUpgrades = db.execute("SELECT numAutodiggers, curShovel FROM simple_upgrades WHERE user_id = ?", session["user_id"])[0]
    numAutodiggers = simpleUpgrades["numAutodiggers"]
    curShovel = simpleUpgrades["curShovel"]

    # Determining the user's skeletonsPerClick and skeletonsPerSecond
    skeletonsPerClick = shovelSkeletonsPerClick(curShovel, baseValue=1, polyPower=1.75, exponentialKicker=1.08)
    skeletonsPerSecond = numAutodiggers

    # Refreshing the value in skeletonsPerClick and skeletonsPerSecond
    db.execute("UPDATE stats SET skeletonsPerClick = ?, skeletonsPerSecond = ? WHERE user_id = ?", skeletonsPerClick, skeletonsPerSecond, session["user_id"])
    # Returning the updated values as JSON
    return jsonify({"skeletonsPerClick": skeletonsPerClick, "skeletonsPerSecond": skeletonsPerSecond})

@app.route("/perSecondOperations", methods=["POST"])
@login_required
def perSecondOperations():
    # Fetching the current skeletonsPerSecond, skeletonCount, and totalSkeletons variables
    perSecondValues = db.execute("""
        SELECT stats.skeletonsPerSecond, users.skeletonCount, users.totalSkeletons
        FROM users
        JOIN stats ON users.id = stats.user_id
        WHERE users.id = ?
    """, session["user_id"])[0]
    skeletonsPerSecond = perSecondValues["skeletonsPerSecond"]
    skeletonCount = perSecondValues["skeletonCount"]
    totalSkeletons = perSecondValues["totalSkeletons"]

    # Updating the skeletonCount and totalSkeletons variables
    db.execute("UPDATE users SET skeletonCount = skeletonCount + ?, totalSkeletons = totalSkeletons + ? WHERE id = ?", skeletonsPerSecond, skeletonsPerSecond, session["user_id"])

    # Fetching the updated values
    updatedValues = db.execute("SELECT skeletonCount, totalSkeletons FROM users WHERE id = ?", session["user_id"])[0]

    # Returning the skeletonsPerSecond value as JSON
    return jsonify({"skeletonsPerSecond": skeletonsPerSecond, "skeletonCount": updatedValues["skeletonCount"], "totalSkeletons": updatedValues["totalSkeletons"]})

@app.route("/", methods=["GET"])
@login_required
def index():
    # Fetching all necessary data in a single query
    userData = db.execute("""
        SELECT users.skeletonCount, users.totalSkeletons,
               simple_upgrades.curShovel, simple_upgrades.shovelCost, simple_upgrades.numAutodiggers, simple_upgrades.autodiggerCost,
               stats.skeletonsPerClick, stats.skeletonsPerSecond
        FROM users
        JOIN simple_upgrades ON users.id = simple_upgrades.user_id
        JOIN stats ON users.id = stats.user_id
        WHERE users.id = ?
    """, session["user_id"])[0]

    skeletonCount = userData["skeletonCount"]
    totalSkeletons = userData["totalSkeletons"]
    curShovel = userData["curShovel"]
    shovelCost = userData["shovelCost"]
    numAutodiggers = userData["numAutodiggers"]
    autodiggerCost = userData["autodiggerCost"]
    skeletonsPerClick = userData["skeletonsPerClick"]
    skeletonsPerSecond = userData["skeletonsPerSecond"]

    # Rendering the webpage with the fetched data
    return render_template("index.html",
        skeletonCount=skeletonCount,
        totalSkeletons=totalSkeletons,
        curShovel=curShovel,
        shovelCost=shovelCost,
        numAutodiggers=numAutodiggers,
        autodiggerCost=autodiggerCost,
        skeletonsPerClick=skeletonsPerClick,
        skeletonsPerSecond=skeletonsPerSecond,
        shovels=shovels,
        maxShovel=maxShovel
    )

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
