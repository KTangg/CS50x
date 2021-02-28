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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    balance = balance[0]["cash"]
    total_st = 0
    for row in stocks:
        total_st += row["accum_price"]
    total = total_st + balance

    return render_template("index.html", stocks=stocks, balance=balance, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Check for valid input
        if not request.form.get('symbol') or not request.form.get('shares'):
            return apology("fill the form", 400)
        elif not lookup(request.form.get("symbol")):
            return apology("invalid ticker", 400)

        # Check for digit quantity
        elif not request.form.get('shares').isdigit():
            return apology("quantity must be integer", 400)

        elif float(request.form.get('shares')) % 1 > 0:
            return apology("quantity must be integer", 400)

        elif float(request.form.get('shares')) < 1:
            return apology("quantity must be integer", 400)

        stock = lookup(request.form.get('symbol'))

        # get user cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
        cash = cash[0]['cash']

        stock_qty = int(request.form.get('shares'))
        stock_price = float(stock['price'])
        b_price = stock_qty * stock_price

        # Check for payment
        if b_price > cash:
            return apology("you are too poor", 403)

        else:

            # Deduct user cash
            balance = cash - b_price
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])
            db.execute("INSERT INTO stocks (symbol, qty, price, user_id, accum_price) VALUES (?, ?, ?, ?, ?)", stock['symbol'], stock_qty, stock_price, session["user_id"], b_price)

            db.execute("INSERT INTO transactions (symbol, qty, price, user_id) VALUES (?, ?, ?, ?)",  stock['symbol'], stock_qty, stock_price, session["user_id"])
            flash("Bought")
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("transactions.html", transactions=transactions)



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
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        stock = lookup(request.form.get("symbol"))

        # No stock found
        if not stock:
            return apology("no stock found", 400)

        # Show Quoted Stock
        return render_template("quoted.html", stock=stock)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("password and comfirm must be the same", 400)

        user_id = db.execute("SELECT username FROM users WHERE username=?", request.form.get("username"))

        if not user_id:

            # Hash password
            h_pw = generate_password_hash(request.form.get("password"))

            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), h_pw)

            # Redirect user to home page
            return redirect("/login")

        else:
            return apology("already used username", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Check for valid input
        if not request.form.get('symbol') or not request.form.get('shares'):
            return apology("fill the form", 400)

        # Check for digit quantity
        elif not request.form.get('shares').isdigit():
            return apology("quantity must be integer", 400)

        elif int(request.form.get('shares')) < 1:
            return apology("quantity must be integer", 400)

        symbol = request.form.get("symbol")
        qty = int(request.form.get("shares"))

        stock = db.execute("SELECT * FROM stocks WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])
        if stock[0]["qty"] < qty:
            return apology("too high sell volume", 400)

        stock_now = lookup(symbol)
        now_price = float(stock_now['price'])

        sell_price = now_price * qty

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        balance = user_cash[0]['cash'] + sell_price

        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

        new_qty = stock[0]["qty"] - qty

        db.execute("UPDATE stocks SET qty = ?, accum_price = ? WHERE user_id = ? AND symbol = ?", new_qty, new_qty*stock[0]['price'], session["user_id"], symbol)

        db.execute("INSERT INTO transactions (symbol, qty, price, user_id) VALUES (?, ?, ?, ?)",  symbol, -qty, now_price, session["user_id"])
        flash("Sold")

        db.execute("DELETE FROM stocks WHERE qty = 0")

        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        stocks = db.execute("SELECT * FROM stocks WHERE (user_id = ?) ORDER BY symbol", session["user_id"])
        return render_template("sell.html", stocks=stocks)

@app.route("/forgot", methods=["GET", "POST"])
def forgot():
    """Password Change"""
     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("password and comfirm must be the same", 400)

        user_id = db.execute("SELECT username FROM users WHERE username=?", request.form.get("username"))

        if user_id:

            # Hash password
            h_pw = generate_password_hash(request.form.get("password"))

            db.execute("UPDATE users SET hash = ? WHERE username = ? ", h_pw, request.form.get("username"))

            # Redirect user to home page
            return redirect("/login")

        else:
            return apology("Invalid", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("forgot.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
