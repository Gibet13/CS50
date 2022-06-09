import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/",  methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "POST":

        if not request.form.get("cash_bonus"):
            return apology("must provide value", 400)

        cash_bonus = request.form.get("cash_bonus")

        db.execute("UPDATE users SET cash = cash + ?  WHERE id = ?", cash_bonus, session["user_id"])

        return redirect("/")

    else:
        stocks = db.execute("SELECT * FROM stocks WHERE owner_id = ?", session["user_id"])
        username =  db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        total_share = db.execute("SELECT SUM(stock_value) FROM stocks WHERE owner_id = ?", session["user_id"])[0]["SUM(stock_value)"]

        if not total_share:
            total = int(cash)
            total_share = 0
        else:
            total = int(cash) + int(total_share)

        return render_template("index.html", stocks = stocks, cash = cash, total_share = total_share, username = username, total = total)





@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        if request.form.get("symbol"):
            symbol = request.form.get("symbol")

        elif request.args.get("symbol"):
            symbol = request.args.get("symbol")

        else:
            return apology("must provide symbol", 403)

        if lookup(symbol) is None:
            return apology("Invalid symbol", 403)

        # Ensure password was submitted
        elif not request.form.get("shares"):
            return apology("must provide amount", 403)

        name = lookup(symbol)["name"]
        price = lookup(symbol)["price"]
        
        amount = request.form.get("shares")
        share_value = int(price) * int(amount)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if (int(cash) - int(share_value)) < 0:
            return apology("Not enough cash", 400)

        search = db.execute("SELECT symbol FROM stocks WHERE owner_id = ? AND symbol = ?", session["user_id"], symbol)

        if not search:
            db.execute("UPDATE users SET cash = cash - ?  WHERE id = ?", share_value, session["user_id"])
            db.execute("INSERT INTO stocks (owner_id, symbol, name, amount, stock_value) VALUES (?, ?, ?, ? ,?)", session["user_id"], symbol, name, amount, share_value)
            db.execute("INSERT INTO transactions (author_id, symbol, name, type, amount, price, t_date) VALUES (?, ?, ?, 'Purchase', ? ,?, CURRENT_TIMESTAMP)", session["user_id"], symbol, name, amount, share_value)

        else:
            db.execute("UPDATE users SET cash = cash - ?  WHERE id = ?", share_value, session["user_id"])
            db.execute("UPDATE stocks SET amount = amount + ?, stock_value  = stock_value + ? WHERE owner_id = ? AND symbol = ?", amount, share_value, session["user_id"], symbol)
            db.execute("INSERT INTO transactions (author_id, symbol, name, type, amount, price, t_date) VALUES (?, ?, ?, 'Purchase', ? ,?, CURRENT_TIMESTAMP)", session["user_id"], symbol, name, amount, share_value)


        return redirect("/")

    else:
        return render_template("buy.html")




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM transactions WHERE author_id = ? ORDER BY t_date DESC", session["user_id"])

    return render_template("history.html", history = history)




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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    return redirect("/login")




@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        name = lookup(request.form.get("symbol"))["name"]
        symbol = lookup(request.form.get("symbol"))["symbol"]
        price = lookup(request.form.get("symbol"))["price"]


        return render_template("quoted.html", name = name, symbol = symbol, price = usd(price))

    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

         # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was confirmed
        elif request.form.get("password2") != request.form.get("password"):
            return apology("must confirm password", 403)

        # Insert new user in database
        username =  request.form.get("username")
        password_hash = generate_password_hash(request.form.get("password"))

        search = db.execute("SELECT username FROM users WHERE username = ?", username)

        if not search:
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username, password_hash)

        else:
            return apology("Name already taken", 400)

        # Redirect user to login page
        return redirect("/")

    else:
        return render_template("register.html")





@app.route("/pass_change", methods=["GET", "POST"])
@login_required
def pass_change():
    """change user password"""

    if request.method == "POST":

         # Ensure  old password was submitted
        if not request.form.get("old_password"):
            return apology("must provide old password", 400)

        # Ensure new password was submitted
        elif not request.form.get("password"):
            return apology("must provide new password", 400)

        # Ensure new password was confirmed
        elif request.form.get("password2") != request.form.get("password"):
            return apology("must confirm new password", 400)

        old_password = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        new_password_hash = generate_password_hash(request.form.get("password"))

        # Update new user password in database
        if check_password_hash(old_password[0]["hash"], request.form.get("old_password")):

            db.execute("UPDATE users SET hash = ? WHERE id = ?", new_password_hash, session["user_id"])
            return redirect("/")

        else:

            return apology("old password does not match", 400)

    else:
        return render_template("pass_change.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        if request.form.get("symbol"):
            symbol = request.form.get("symbol")

        elif request.args.get("symbol"):
            symbol = request.args.get("symbol")

        else:
            return apology("must provide symbol", 403)

        if lookup(symbol) is None:
            return apology("Invalid symbol", 403)

        # Ensure password was submitted
        elif not request.form.get("shares"):
            return apology("must provide amount", 403)

        name = lookup(symbol)["name"]
        price = lookup(symbol)["price"]

        amount = request.form.get("shares")
        share_value = int(price) * int(amount)

        search = db.execute("SELECT symbol FROM stocks WHERE owner_id = ? AND symbol = ?", session["user_id"], symbol)
        if not search:
            return apology("No stocks found", 403)

        else:

            owned_share = db.execute("SELECT amount FROM stocks WHERE owner_id = ? AND symbol = ?", session["user_id"], symbol)[0]["amount"]

            if (int(owned_share) - int(amount)) <= 0:

                share_value = int(price) * int(owned_share)

                db.execute("UPDATE users SET cash = cash + ?  WHERE id = ?", share_value, session["user_id"])
                db.execute("DELETE FROM stocks WHERE owner_id = ? AND symbol = ?", session["user_id"], symbol)
                db.execute("INSERT INTO transactions (author_id, symbol, name, type, amount, price, t_date) VALUES (?, ?, ?, 'Sale', ? ,?, CURRENT_TIMESTAMP)", session["user_id"], symbol, name, amount, share_value)

            else:
                db.execute("UPDATE users SET cash = cash + ?  WHERE id = ?", share_value, session["user_id"])
                db.execute("UPDATE stocks SET amount = amount - ?, stock_value  = stock_value - ? WHERE owner_id = ? AND symbol = ?", amount, share_value, session["user_id"], symbol)
                db.execute("INSERT INTO transactions (author_id, symbol, name, type, amount, price, t_date) VALUES (?, ?, ?, 'Sale', ? ,?, CURRENT_TIMESTAMP)", session["user_id"], symbol, name, amount, share_value)

        return redirect("/")

    else:
        return render_template("sell.html")




def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
