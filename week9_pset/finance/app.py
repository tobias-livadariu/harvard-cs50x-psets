import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """If the route was requested via post, buy shares of stock."""
    if request.method == "post":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("You did not input a stock symbol! Next time, please input a valid stock symbol.")
        if (not isinstance(shares, int)) or shares < 1:
            return apology("When choosing the number of shares you would like to purchase, please use a positive integer.")
        price = lookup(symbol)
        if not price:
            return apology("The stock symbol you inputted does not exist! Please try a different stock symbol.")
        userBal = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        totalCost = shares * price
        if userBal < totalCost:
            return apology(f"You cannot afford that transaction! Remember, your current balance is ${userBal} USD.")
        db.execute("INSERT INTO stocks (user_id, stock_symbol, stock_count) VALUES (?, ?, ?)", session["user_id"], symbol, shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (userBal - totalCost), session["user_id"])
        return redirect()

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "post":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("The stock symbol you quoted does not exist! Please try a different stock symbol.")
        return render_template("quoted.html", quote=quote)

    """If the page was requested via get, rendering it."""
    return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmPassword = request.form.get("confirmPassword")
        """Checking if the user's input is valid."""
        if not username:
            return apology("You must choose a username!")
        if not password:
            return apology("You must choose a password!")
        if not confirmPassword:
            return apology("You must confirm your password in the \"Confirm Password\" box!")
        if password != confirmPassword:
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
        session["user_id"] = db.execute("SELECT id FROM users WHERE (username = ?) AND (hash = ?)", username, passwordHash)

    """If the register page was accessed via "get", displaying it to the user."""
    return template_render("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
