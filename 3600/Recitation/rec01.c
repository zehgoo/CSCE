#include <stdio.h>

int main()
{
    unsigned char asciiVal;
    printf("Enter an ASCII character: ");
    scanf("%c", &asciiVal);
    
    printf("The ASCII value of %c is: \n", asciiVal);
    unsigned int hexVal = asciiVal;

    printf("    Dec: %d\n    Hex: %x\n    Bin: ", asciiVal, hexVal);

    unsigned int decVal = hexVal;
    unsigned int tempVal = 0;

    for (int i = 7; i >= 0; --i)
    {
        tempVal = decVal >> i;
        if (tempVal & 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    } 

    return 0; 

}