#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int header_check(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //Invalid input
    if (argc != 2)
    {
        printf("Usage: ./recover *file\n");

        return 1;
    }

    //take the pointer number
    char *input = argv[1];

    //open the memory
    FILE *memory = fopen(input, "r");

    //Checking file is open
    if (memory == NULL)
    {
        printf("File Cannot be Open %s\n", input);

        return 1;
    }

    //reading the file for 1-4 byte in each FAT
    int jpg_count = 0;
    FILE *img;
    char filename[100];
    BYTE buffer[512];
    int found = 0;
    
    while (fread(buffer, sizeof(BYTE), 512, memory) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0)) 
        {
            if (jpg_count == 0)
            {
                found = 1;
                //Create a filename
                sprintf(filename, "%03i.jpg", jpg_count);
                
                //Create new jpg file
                img = fopen(filename, "w");
                
                //Writing the content
                fwrite(buffer, sizeof(BYTE), 512, img);
                
                jpg_count += 1;
            }
            
            else
            {
                //Close old file
                fclose(img);
                
                //Create a new filename
                sprintf(filename, "%03i.jpg", jpg_count);
                
                //Create new jpg file
                img = fopen(filename, "w");
                
                //Writing the content
                fwrite(buffer, sizeof(BYTE), 512, img);
                
                jpg_count += 1;
            }
        }
        
        else
        {
            if (found != 0)
            {
                //Writing the content
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }
   
    return 0;
}