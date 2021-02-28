import csv
import sys


def main():
    
    # Check for valid command-line
    if len(sys.argv) != 3:
        
        print("Usage: python dna.py CSVFILE TEXTFILE")
        sys.exit(1)
        
    # Read CSV and store sample data lise[{dict1},{dict2}]
    sample = []
    
    CSV_file = sys.argv[1]
    with open(CSV_file, 'r') as csv_data:
    
        reader = csv.DictReader(csv_data)
        
        for row in reader:
            
            # Change all value to integer
            for key in row:
                # Except for name
                if key != 'name':
                    
                    row[key] = int(row[key])
                    
            # Add dict to list
            sample.append(row)
        
    SEQ_file = sys.argv[2]
    with open(SEQ_file, 'r') as seq_data:
        # Store sequence data
        seq = seq_data.read()
        
    # Count for each key    
    seq_count = dna_read(sample, seq)
    
    # Finding the name
    identify(sample, seq_count)
        
        
def dna_read(sample, seq):
    
    seq_count = {}    
    
    for key in sample[0]:
        
        if key != 'name':
            
            highest = 0
            
            for i in range(len(seq)):
                
                text = seq[i: i + (len(key))]
                a = len(key)
                b = len(seq[i:i+(len(key))])
                if seq[i:i + (len(key))] == key:
                    
                    # Found 1
                    repeat = 1
                    
                    # Check for next 
                    for j in range(i + len(key), len(seq) + 1, len(key)):
                        c = len(seq[j: j + (len(key))])
                        d = seq[j: j + (len(key))]
                        if seq[j: j + (len(key))] == key:
                            
                            # Keep Counting
                            repeat += 1
                        
                        else:
                            # If not repeat reset it 
                            if repeat > highest:
                                
                                # Record the highest
                                highest = repeat
                                repeat = 0
                                
                            break
            
            # Append to dict
            seq_count[key] = highest
    
    return seq_count


def identify(sample, seq_count):
    
    # Iterate over every name & each key
    
    for dna_data in sample:
        
        keys = 0
        correct = 0
        
        for key in dna_data:
            
            if key != 'name':
                
                keys += 1
                
                if dna_data[key] == seq_count[key]:
                    
                    correct += 1
                    
        if keys == correct:
            
            print(dna_data['name'])
            
            return True
    
    print("No Match")
    return False


if __name__ == '__main__':
    main()