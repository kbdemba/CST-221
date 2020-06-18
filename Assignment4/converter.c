//Kebba Demba
//CST-221
//Decimal Number conversion

// In this program, the program takes in a number between 0 and 4095. It thens
// displays the number as a 32-bit binary number and 32-bit hexadecimal, 
// It then	transform the input by shifting the number 16 bits to the left, then mask out (AND) 
// the bottom 16 bits then display the final result in binary, hexadecimal, and
// decimal to the console.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


void convertToBinary(int decimal)
{
	//CONVERT TO BINARY
	//get the decimal number
	unsigned int bi = decimal;

	//holds the 32 bit binary number
	int binary[32];
	int i = 32;

	//set the binary number to 0
	for (int j = 0; j <= 32; j++)
	{
		binary[j] = 0;
	}

	//converts the intpart into a binary number
	while (bi != 0)
	{
		int r = bi % 2;
		binary[i] = r;
		bi = bi / 2;
		i--;
	}

	printf("Binary Conversion: ");
	//prints binary number
	for (int j = 0; j <= 32; j++)
	{
		printf("%d", binary[j]);
	}
	printf("\n");

	return;
}

void convertToHexadecimal(int decimal)
{
	//CONVERT TO HEXADECIMAL
	//converts the intpart into hexadecimal
	printf("Hexadecimal Conversion: ");
	unsigned int hi = decimal;
	printf("%X", hi);
	printf("\n");
	return;
}

int main()
{

	//create variable to hold user input
	unsigned int decimal;

START: //start of the program
	//get the user input
	printf("Enter an int number 0 to 4095: ");
	scanf("%d", &decimal);

	//if number is between 0 - 4095
	if (decimal > 0 && decimal < 4095)
	{
		printf("Decimal: %d\n", decimal); 
	}
	else
	{
		printf("You have to enter an int number 0 to 4095.\n");
		goto START; //propmpt user again
	}

	convertToBinary(decimal);
	convertToHexadecimal(decimal);

	//TRANSFORM INPUT
	//shift the number 16 bits to the left
	unsigned int shift = decimal << 16;
	//printf("\nLEFT SHIFT: %d", shift);  //used to check

	//mask out (AND) the bottom 16 bits
	shift &= ~0xFFFF;
	//printf("\nMASK OUT BOTTOM: %d", shift);  //used to check

	//hex number 0x07FF to produce the final resultant number
	shift |= 0x07FF;
	//printf("\nHEX OUTPUT: %d", shift);  //used to check

	//output final resultant
	printf("\nFINAL OUTPUTS: ");
	printf("\nDecimal Conversion: %d\n", shift);
	convertToBinary(shift);
	convertToHexadecimal(shift);

	return 0;
}