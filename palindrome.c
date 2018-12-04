#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int palindrome (char string [])		//inputs a string and returns 1 if it is a palindrome. Else returns 0
{
	int length = strlen(string)-1;
	int i = 0, j = length, l = 0, ci, cj; //index i and j, character at i and j
	
	
	for (l=0; l <= length; l++ ) //loop through string
	{
		ci= string[i]; //pointer at beggining
		cj= string[j]; //pointer at end
		
		while (ispunct(ci) || isspace(ci))  //if punctuation or whitespace then skip over it
		{
			i++;
			length--; //Loop 1 less time. 
			ci= string[i]; //get character
		}
		while (ispunct(cj) || isspace(cj))  //if punctuation or whitespace then skip over it
		{
			j--;
			cj= string[j]; //get character
		}
		
		ci = tolower(ci); //turn both characters to lowercase
		cj = tolower(cj);
		
		printf("|%c|  |%c|\n",ci, cj);
		
		if (ci != cj)
			return(0); //if characters are not equal it is not a palindrome
		
		i++; //move indexs
		j--;

	}
	
	
	return(1); //it is a palindrome
}








int main(int argc, char *argv[])      //main
{
	char input[100]; //the input string
	
	
	printf("Please enter a palindrome\n"); //prompt for string
	
	fgets(input, 100, stdin); //read input
	
	if (input[strlen(input)-1] == '\n')//if fgets adds a newline change the newline to end of string
		input[strlen(input)-1] = '\0'; 
	
	if (palindrome(input))
		printf("The string \"%s\" is a palindrome\n",input);
	
	else 
		printf("The string \"%s\" is NOT a palindrome\n",input);
	
}