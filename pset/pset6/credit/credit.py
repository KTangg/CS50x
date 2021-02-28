import math as m


def main():
    # Asking Card Number
    card = get_card()

    # Branching to 4 Conditions (Visa(1), Amex, Visa(2), Master)

    # Master Card Checking 15,16 digith is (51,52,53,54,55)
    if (card // power(10, 14) >= 51 and (card // power(10, 14)) <= 55):
    
        digith = 16

        x = checking(card, digith)

        if (x == 1):
            
            print("MASTERCARD\n")

        else:
            
            print("INVALID\n")

    # Visa(Cond. 1) 16 digith is 4
    elif ((card // power(10, 15)) == 4):
        
        digith = 16

        x = checking(card, digith)

        if (x == 1):
            
            print("VISA\n")

        else:
            
            print("INVALID\n")

    # Amex 15,14 digith is (34,37)
    elif (card // power(10, 13) == 34 or card // power(10, 13) == 37):
    
        digith = 15
        
        x = checking(card, digith)

        if (x == 1):
            
            print("AMEX\n")

        else:
            
            print("INVALID\n")

    # Visa(Cond. 2) 13 digith is 4
    elif (card // power(10, 12) == 4):
    
        digith = 13

        x = checking(card, digith)

        if (x == 1):
        
            print("VISA\n")

        else:
            
            print("INVALID\n")

    # Not on Any Condition is Invalid
    else:
        
        print("INVALID\n")


def get_card():
    # Asking for Card Number(Positive Number only)
    n = 0
    
    while (n <= 0):
        
        n = int(input("Number: "))
        
    return n


# Checking Validate Funtion
def checking(card, digith):

    # This for Other Number that *2
    other_sum = 0

    for i in range(2, digith + 1, 2):
    
        # Finding Other Number
        other = (card % m.pow(10, i) // m.pow(10, i - 1))

        # Multiply its by 2
        other_2 = other * 2

        # Sum its digit product
        digit_p = (other_2 // 10) + (other_2 % 10)

        # Sum  of Other digit product
        other_sum += digit_p

    # This for the rest that not *2
    rest_sum = 0

    for j in range(1, digith + 1, 2):
        
        # Finding the rest
        rest_n = (card % power(10, j) // power(10, j - 1))

        # Summing it
        rest_sum += rest_n

    # Sum all product
    tot = other_sum + rest_sum

    # Checking last digit
    if (tot % 10 == 0):
    
        x = 1
        
    else:
    
        x = 0
    
    return x
    
    
def power(x, y):
    
    z = m.pow(x, y)
    
    return z


if __name__ == '__main__':
    main()