import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        # Validating the user's input server-side.
        try:
            month = int(month)
            day = int(day)
        except:
            return redirect("/failure")
        if not name or not (1 <= month <= 12) or not (1 <= day <= 31):
            return redirect("/failure")

        # Adding the user's input to the database.
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays = birthdays)

@app.route("/failure")
def failure():
    return render_template("failure.html")

@app.route("/remove" methods=["POST"])
def remove():
    id = request.form.get("id")
    db.execute("DROP * FROM birthdays WHEN id=?", id)
    return redirect("/")
