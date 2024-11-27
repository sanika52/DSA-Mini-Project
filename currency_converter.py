import tkinter as tk
from tkinter import messagebox

# Function to convert currency
def convert_currency():
    amount = amount_entry.get()
    if not amount.isdigit():
        messagebox.showerror("Invalid Input", "Please enter a valid number!")
        return

    amount = float(amount)
    convert_from = convert_from_var.get()
    convert_to = convert_to_var.get()
    converted_amount = 0  # Replace with actual conversion logic

    # Example conversion logic (add real exchange rates)
    if convert_from == "USD" and convert_to == "INR":
        converted_amount = amount * 74.85
    elif convert_from == "INR" and convert_to == "USD":
        converted_amount = amount * 0.013
    # Add other conversion logic here

    ans.set(f"Converted Amount: {converted_amount:.2f}")

# Function to clear inputs
def clear():
    amount_entry.delete(0, tk.END)
    ans.set("")

# Function to exit the application
def exit_app():
    c.destroy()

# Create main window
c = tk.Tk()
c.title("Currency Converter")
c.geometry("500x500")
c.configure(background="lightblue")

# Labels and Input Fields
amount_label = tk.Label(c, text="Enter Amount:", font=("Arial", 12))
amount_label.place(x=50, y=150)

amount_entry = tk.Entry(c, font=("Arial", 12), bd=2, relief=tk.SOLID)
amount_entry.place(x=200, y=150)

convert_from_label = tk.Label(c, text="From Currency:", font=("Arial", 12))
convert_from_label.place(x=50, y=200)

currency_options = ["USD", "INR", "EUR"]  # Add more currencies
convert_from_var = tk.StringVar(c)
convert_from_var.set(currency_options[0])
convert_from_dropdown = tk.OptionMenu(c, convert_from_var, *currency_options)
convert_from_dropdown.place(x=200, y=200)

convert_to_label = tk.Label(c, text="To Currency:", font=("Arial", 12))
convert_to_label.place(x=50, y=250)

convert_to_var = tk.StringVar(c)
convert_to_var.set(currency_options[1])
convert_to_dropdown = tk.OptionMenu(c, convert_to_var, *currency_options)
convert_to_dropdown.place(x=200, y=250)

# Buttons
convert_button = tk.Button(c, text="Convert", font=("Arial", 12), command=convert_currency, bg="green", fg="white")
convert_button.place(x=150, y=300)

clear_button = tk.Button(c, text="Clear", font=("Arial", 12), command=clear, bg="yellow")
clear_button.place(x=250, y=300)

exit_button = tk.Button(c, text="Exit", font=("Arial", 12), command=exit_app, bg="red", fg="white")
exit_button.place(x=350, y=300)

# Result Display
ans = tk.StringVar(c)
result_label = tk.Label(c, textvariable=ans, font=("Arial", 12), bg="lightblue", fg="black")
result_label.place(x=150, y=350)

# Run the main loop
c.mainloop()