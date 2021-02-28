def main():
    # Getting text input
    text = str(input("Text: "))

    # Count letter and show
    letters = count_letter(text)

    # Count word and show
    words = count_word(text)

    # Count sentence and show
    sentences = count_sentence(text)

    # Index calculation
    factor = word100(words)

    L = letters * factor
    S = sentences * factor

    index = (0.0588 * L) - (0.296 * S) - 15.8

    # Condition before rounding number
    if (index < 1):
        
        print("Before Grade 1\n")

    elif (round(index) >= 16):
        
        print("Grade 16+\n")

    else:
        
        print(f"Grade {round(index)}\n")


def count_letter(text):

    letter = 0
    
    for i in text:
    
        # Checking is it alphabet or not if yes count
        if (i.isalpha()):
            
            letter += 1
            
    return letter


def count_word(text):

    word = 0

    # Checking for spacebar
    for i in text:
        
        # Checking is it whitespace or not if yes count
        if (i == ' '):
            
            word += 1
            
    # Plus one for ending
    return word + 1


def count_sentence(text):
    
    sentence = 0

    # Checking for . ? !
    for i in text:
        
        # Checking for . ? !
        if (i == '.' or i == '!' or i == '?'):
        
            sentence += 1
           
    return sentence


def word100(word):
    
    # factor to find average for 100 words
    factor = 100.0 / word
    
    return factor
    
    
if __name__ == '__main__':
    main()