#include<stdio.h>
#include<stdlib.h>
#include "charFunction.h"
char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
//int numOfLetters=0;
int numOfOccur[25];
//Ashish Datta and Skye Croke

void charOccur(char letter)
{
	switch(letter)
	{ //Checks letter against case and increments numOfOccur at that index. numOfOccur[0] = a ...numOfOccur[25]=z
		case 'a':
			numOfOccur[0]++;
			break;
		case 'b':
			numOfOccur[1]++;
			break;
		case 'c':
			numOfOccur[2]++;
			break;
		case 'd':
			numOfOccur[3]++;
			break;
		case 'e':
			numOfOccur[4]++;
			break;
		case 'f':
			numOfOccur[5]++;
			break;
		case 'g':
			numOfOccur[6]++;
			break;
		case 'h':
			numOfOccur[7]++;
			break;
		case 'i':
			numOfOccur[8]++;
			break;
		case 'j':
			numOfOccur[9]++;
			break;
		case 'k':
			numOfOccur[10]++;
			break;
		case 'l':
			numOfOccur[11]++;
			break;
		case 'm':
			numOfOccur[12]++;
			break;
		case 'n':
			numOfOccur[13]++;
			break;
		case 'o':
			numOfOccur[14]++;
			break;
		case 'p':
			numOfOccur[15]++;
			break;
		case 'q':
			numOfOccur[16]++;
			break;
		case 'r':
			numOfOccur[17]++;
			break;
		case 's':
			numOfOccur[18]++;
			break;
		case 't':
			numOfOccur[19]++;
			break;
		case 'u':
			numOfOccur[20]++;
			break;
		case 'v':
			numOfOccur[21]++;
			break;
		case 'w':
			numOfOccur[22]++;
			break;
		case 'x':
			numOfOccur[23]++;
			break;
		case 'y':
			numOfOccur[24]++;
			break;
		case 'z':
			numOfOccur[25]++;
			break;
	}
		
}//end function
		

void printCharOccur(int numOfLetters)
{
		int k;
		for(k =0; k < 26; k++)
		{
			 printf("%c %9d  %.5f\n",alphabet[k], numOfOccur[k],((double)numOfOccur[k]/(double)numOfLetters)) ;  
		}

}//end function

void countPairs(char *fileName)
{
	FILE *f=fopen(fileName, "rb");
	int i,j,ii,jj;
	int numOfPairs=0;
	long charPair[26][26];
	memset(charPair, 0, 26*26*sizeof(long));
	
	fseek(f, 0, SEEK_END);
	int  len = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* yourInput = malloc(len+1); 
	fread(yourInput, 1, len, f); 
	yourInput[len] = '\0';
	char* reader = yourInput;
	char current = tolower(*reader);
	++reader;
	char next = tolower(*reader);
	while(next!=0) { // assumes \0-terminated
   		charPair[current-97][next-97] += 1;
    		current = next;
		++reader;
		next = *reader;
		//++reader;
	}	
	/*End pair search algorithm*/
	

	for(i=0;i<26;++i)
	{
		for(j=0;j<26;++j)
		{
			numOfPairs += charPair[i][j];
			printf("Pair: %c%c times %ld\n",alphabet[i],alphabet[j],charPair[i][j]);	
		}
	}
	printf("%d pairs\n", numOfPairs);

}//end function



