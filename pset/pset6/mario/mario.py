from cs50 import get_int


def main():

    # promp asking
    h = get_pos_int("Height: ")
    
    # bricking
    for i in range(h):
        # left side
        print(" " * (h - (i + 1)), end='')
        print("#" * (i + 1), end='')
        # middle
        print("  ", end='')
        # right side
        print("#" * (i + 1), end='')
        print("")
        

def get_pos_int(word):
    
    x = 0
    
    # working if value not between 1-8 
    while x not in range(1, 9):
        
        x = get_int(word)
        
    return x
    
    
if __name__ == '__main__':
    main()
