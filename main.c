#include "main.h"

// Add digit, e.g. 8+5 = 13, singleDigit will be 3, and nextDigit will be 1
void digitAddition(int a, int b, int c, int* result) {
	int nextDigit = (a + b + c) / 10;
	int singleDigit = (a + b + c) - nextDigit * 10;
	result[0] = singleDigit;
	result[1] = nextDigit;
}

// Add two big numbers
void add(const char* a, const char* b, char* dst) {
	int length_a = strlen(a);
	int length_b = strlen(b);
	char result[MAX_PLACE];
	initNumber(result, MAX_PLACE);
	int extra = 0;
	for (int index = MAX_PLACE - 2, counter = 0; index >= 0; index--, counter++) {
		int tempnum = -1;
		if (length_a - 1 - counter >= 0)
			tempnum = a[length_a - 1 - counter] - '0';
		int digit_A = tempnum >= 0 ? a[length_a - 1 - counter] - '0' : 0;
		tempnum = -1;
		if (length_b - 1 - counter >= 0)
			tempnum = b[length_b - 1 - counter] - '0';
		int digit_B = tempnum >= 0 ? b[length_b - 1 - counter] - '0' : 0;
		int temp[2];
		digitAddition(digit_A, digit_B, extra, temp);
		extra = temp[1];
		result[index] = '0' + temp[0];
	}
	removeZero(result);
	strcpy(dst, result);
}

// Perform checking before addition, handles negative numbers
void addition(char* a, const char* b) {
	char result[MAX_PLACE];
	initNumber(result, MAX_PLACE);

	char intA[MAX_PLACE];
	initNumber(intA, MAX_PLACE);
	strcpy(intA, a);

	char intB[MAX_PLACE];
	initNumber(intB, MAX_PLACE);
	strcpy(intB, b);

	int decimalA = decimal2int(intA);
	int decimalB = decimal2int(intB);
	int decimalPlace = 0;

	if (decimalA > decimalB) {
		addZero(intB, decimalA - decimalB, intB);
		decimalPlace = decimalA;
	}
	else if (decimalB > decimalA) {
		addZero(intA, decimalB - decimalA, intA);
		decimalPlace = decimalB;
	}
	else
		decimalPlace = decimalA;

	add(intA, intB, result);
	addDecimal(result, decimalPlace);
	strcpy(a, result);
}

// Subtract digit, e.g. 17-9=8. which 7-9=-2, extra 10 is needed, therefore add 10 to singleDigit, and the nextDigit is 1 to subtract an extra 1
void digitSubtraction(int a, int b, int c, int* result) {
	int singleDigit = a - b - c;
	int nextDigit = 0;
	if (singleDigit < 0) {
		nextDigit = 1;
		singleDigit += 10;
	}
	result[0] = singleDigit;
	result[1] = nextDigit;
}

// Subtract b from a
void subtract(const char* a, const char* b, char* dst) {
	int length_a = strlen(a);
	int length_b = strlen(b);
	char result[MAX_PLACE];
	initNumber(result, MAX_PLACE);
	int extra = 0;
	for (int index = MAX_PLACE - 2, counter = 0; index >= 0; index--, counter++) {
		int tempnum = -1;
		if (length_a - 1 - counter >= 0)
			tempnum = a[length_a - 1 - counter] - '0';
		int digit_A = tempnum >= 0 ? a[length_a - 1 - counter] - '0' : 0;
		tempnum = -1;
		if (length_b - 1 - counter >= 0)
			tempnum = a[length_b - 1 - counter] - '0';
		int digit_B = tempnum >= 0 ? b[length_b - 1 - counter] - '0' : 0;
		int temp[2];
		digitSubtraction(digit_A, digit_B, extra, temp);
		extra = temp[1];
		result[index] = '0' + temp[0];
	}
	removeZero(result);
	strcpy(dst, result);
}

// Perform checking before subtraction, handles negative numbers
void subtraction(char* a, const char* b) {
	char result[MAX_PLACE];
	initNumber(result, MAX_PLACE);

	char intA[MAX_PLACE];
	initNumber(intA, MAX_PLACE);
	strcpy(intA, a);

	char intB[MAX_PLACE];
	initNumber(intB, MAX_PLACE);
	strcpy(intB, b);


	int decimalA = decimal2int(intA);
	int decimalB = decimal2int(intB);
	int decimalPlace = 0;

	if (decimalA > decimalB) {
		addZero(intB, decimalA - decimalB, intB);
		decimalPlace = decimalA;
	}
	else if (decimalB > decimalA) {
		addZero(intA, decimalB - decimalA, intA);
		decimalPlace = decimalB;
	}
	else
		decimalPlace = decimalA;
	if(bigNumMax(intA, intB) == 0)
		subtract(intA, intB, result);
	else {
		subtract(intB, intA, result);
		addNegativeSign(result);
	}
	addDecimal(result, decimalPlace);
	strcpy(a, result);
}

// Digit multiplication, e.g. 7*9=63, singleDigit = 3, nextDigit = 6
void digitMultiplication(int a, int b, int c, int* result) {
	int nextDigit = (a * b + c) / 10;
	int singleDigit = (a * b + c) - nextDigit * 10;
	result[0] = singleDigit;
	result[1] = nextDigit;
}

// Multiply 2 numbers
void multiply(const char* a, const char* b, char* dst) {
	int length_a = strlen(a);
	char result[MAX_PLACE];
	initNumber(result, MAX_PLACE);
	int extra = 0;
	int location = 0;
	for (location = 1; location < strlen(b); location++)
		result[MAX_PLACE - 2 - location] = '0';
	for (int index = MAX_PLACE - 2 - location, counter = 0; index >= 0; index--, counter++) {
		int tempnum = -1;
		if (length_a - 1 - counter >= 0)
			tempnum = a[length_a - 1 - counter] - '0';
		int digit_A = tempnum >= 0 ? a[length_a - 1 - counter] - '0' : 0;
		tempnum = -1;
		int digit_B = b[0] - '0';
		int temp[2];
		digitMultiplication(digit_A, digit_B, extra, temp);
		extra = temp[1];
		result[index] = '0' + temp[0];
	}
	removeZero(result);
	strcpy(dst, result);
}

// Perform checking before multiplication, handles negative numbers
void multiplication(char* a, const char* b) {
	char result[MAX_PLACE];
	initNumber(result, MAX_PLACE);
	result[0] = '0';

	int isNegA = 0;
	int isNegB = 0;

	if (a[0] == '-')
		isNegA = 1;
	if (b[0] == '-')
		isNegB = 1;

	char intA[MAX_PLACE];
	initNumber(intA, MAX_PLACE);
	strcpy(intA, a);
	if(isNegA)
		removeNegativeSign(intA);

	char intB[MAX_PLACE];
	initNumber(intB, MAX_PLACE);
	strcpy(intB, b);
	if(isNegB)
		removeNegativeSign(intB);

	int decimalA = decimal2int(intA);
	int decimalB = decimal2int(intB);
	int decimalPlace = 0;

	decimalPlace = decimalA + decimalB;

	int length_b = strlen(intB);
	for (int i = 0; i < length_b; i++) {
		char resulttemp[MAX_PLACE];
		initNumber(resulttemp, MAX_PLACE);
		char tempNumber[MAX_PLACE];
		initNumber(tempNumber, MAX_PLACE);
		char testb[] = { intB[i], '\0' };
		addZero(testb, length_b - 1 - i, tempNumber);
		multiply(intA, tempNumber, resulttemp);
 		add(result, resulttemp, result);
	}
	addDecimal(result, decimalPlace);
	if (isNegA ^ isNegB)
		addNegativeSign(result);

	strcpy(a, result);
}

// Perform division
void division(char* dividend, const char* divisor) {
	char tempDividend[MAX_PLACE];
	initNumber(tempDividend, MAX_PLACE);

	char intDividend[MAX_PLACE];
	initNumber(intDividend, MAX_PLACE);
	strcpy(intDividend, dividend);

	char intDivisor[MAX_PLACE];
	initNumber(intDivisor, MAX_PLACE);
	strcpy(intDivisor, divisor);

	int decimalDividend = decimal2int(intDividend);
	int decimalDivisor = decimal2int(intDivisor);
	int decimalPlace = 0;

	if (decimalDividend > decimalDivisor) {
		addZero(intDivisor, decimalDividend - decimalDivisor, intDivisor);
		decimalPlace = decimalDividend;
	}
	else if (decimalDivisor > decimalDividend) {
		addZero(intDividend, decimalDivisor - decimalDividend, intDividend);
		decimalPlace = decimalDivisor;
	}
	else
		decimalPlace = decimalDividend;

	strcpy(tempDividend, intDividend);

	int length_dividend = strlen(intDividend);
	int decimal = 0;


	char quotient[MAX_PLACE];
	initNumber(quotient, MAX_PLACE);

	for (int i = 0; i < MAX_PLACE; i++) {
		if (decimal == 50 || tempDividend[0] == '0' || tempDividend[0] == '\0')
			break;

		char tempNumber[MAX_PLACE];
		initNumber(tempNumber, MAX_PLACE);

		char multiple[MAX_PLACE];

		int maxMultiple = 1;
		short isSmaller = 0;

		for (maxMultiple; maxMultiple < 10; maxMultiple++) {
			initNumber(multiple, MAX_PLACE);
			char charMultiple[] = { maxMultiple + '0', '\0' };
			addZero(charMultiple, length_dividend - 1 - i, multiple);
			multiply(intDivisor, multiple, tempNumber);
			if (bigNumMax(tempDividend, tempNumber) == 1 || bigNumMax(tempDividend, tempNumber) == 2 || (bigNumMax(tempDividend, tempNumber) == 0 && maxMultiple == 9)) {
				if (bigNumMax(tempDividend, tempNumber) == 0 && maxMultiple == 9 || bigNumMax(tempDividend, tempNumber) == 2) {
					multiply(intDivisor, multiple, tempNumber);
					if (quotient[0] == '\0')
						quotient[0] = '0';
					add(quotient, multiple, quotient);
				}
				else {
					char charMultiple[] = { maxMultiple - 1 + '0', '\0' };
					addZero(charMultiple, length_dividend - 1 - i, multiple);
					multiply(intDivisor, multiple, tempNumber);
					if (quotient[0] == '\0')
						quotient[0] = '0';
					add(quotient, multiple, quotient);
				}
				subtract(tempDividend, tempNumber, tempDividend);
				isSmaller = 1;
				if (bigNumMax(tempDividend, intDivisor) == 1)
					isSmaller = 2;
				break;
			}
		}
		if (isSmaller == 1)
			continue;
		else if (isSmaller == 2) {
			decimal++;
			multiply(tempDividend, "10", tempDividend);
			multiply(quotient, "10", quotient);			
		}
	}
	if (decimal > 0) {
		addDecimal(quotient, decimal);
	}
	if (quotient[0] == '\0') {
		initNumber(quotient, MAX_PLACE);
		quotient[0] = '0';
	}
	strcpy(dividend, quotient);
}

// Init character array to '\0'
void initNumber(char* number, int max) {
	for (int i = 0; i < max; i++)
		number[i] = '\0';
}

// Find the bigger big num from a and b, if a is greater, return 0, if b is greater, return 1, if they are the same, return 2
int bigNumMax(const char* a, const char* b) {
	if (strlen(a) > strlen(b))
		return 0;
	else if(strlen(a) < strlen(b))
		return 1;
	else {
		for (int i = 0; i < strlen(a); i++) {
			if (a[i] > b[i])
				return 0;
			else if (a[i] < b[i])
				return 1;
		}
		return 2;
	}
}

// Remove the beginning zeros
void removeZero(char* number) {
	char tempNumber[MAX_PLACE];
	initNumber(tempNumber, MAX_PLACE);
	int index = 0;
	short shouldSkip = 1;
	int tempIndex = 0;
	while (number[index] != '\0') {
		if (number[index] != '0' && shouldSkip) {
			shouldSkip = 0;
			tempNumber[tempIndex] = number[index];
			tempIndex++;
		}
		else if (!shouldSkip) {
			tempNumber[tempIndex] = number[index];
			tempIndex++;
		}
		index++;
	}

	strcpy(number, tempNumber);
}

// Add zeros after the digit for multiplication
// e.g 438 -> 4 -> 400
void addZero(char* number, int numberofzero, char* dst) {
	char result[MAX_PLACE];
	initNumber(result, MAX_PLACE);
	strcpy(result, number);
	for (int i = strlen(number); i < numberofzero + strlen(number); i++)
		result[i] = '0';
	strcpy(dst, result);
}

// Add back decimal point, e.g addDecimal("12345", 2) will convert "12345" to "123.45"
void addDecimal(char* number, int place)
{
	char temp[MAX_PLACE];
	initNumber(temp, MAX_PLACE);
	int pos = strlen(number);
	int dec = pos - place;
	short placed = 0;
	for (pos; pos >= 0; pos--) {
		if (pos == dec) {
			temp[pos] = '.';
			placed = 1;
		}
		else {
			if (placed)
				temp[pos] = number[pos];
			else
				temp[pos] = number[pos - 1];
		}
	}

	// Remove zeros after decimal
	pos = strlen(temp);
	for (int index = pos - 1; index >= 0; index--) {
		if (temp[index] == '0')
			temp[index] = '\0';
		else
			break;
	}

	// If the last character is a single dot, remove it
	pos = strlen(temp);
	if (temp[pos - 1] == '.')
		temp[pos - 1] = '\0';

	// Add zero at the beginning if something is wrong
	if (temp[0] == '.') {
		char temp2[MAX_PLACE];
		initNumber(temp2, MAX_PLACE);
		temp2[0] = '0';
		for (int i = 0; i < strlen(temp); i++)
			temp2[i + 1] = temp[i];

		pos = strlen(temp2);
		if (temp2[pos - 1] == '.')
			temp2[pos - 1] = '\0';
		strcpy(number, temp2);
		return;
	}

	strcpy(number, temp);
}

// Convert floating point to integer, and return the decimal place position. e.g. 123.45 will convert to 12345 and return 2
int decimal2int(char* decimalNumber) {
	char intnumber[MAX_PLACE];
	initNumber(intnumber, MAX_PLACE);
	int decimalPlace = 0;
	int found = 0;
	for (int index = 0; index < strlen(decimalNumber); index++) {
		if (decimalNumber[index] == '.') {
			found = 1;
			decimalPlace = strlen(decimalNumber) - 1 - index;
		}
		else {
			if (found) 
				intnumber[index - 1] = decimalNumber[index];
			else
				intnumber[index] = decimalNumber[index];
		}

	}
	strcpy(decimalNumber, intnumber);
	return decimalPlace;
}

// Add negative sign before the number
void addNegativeSign(char* number)
{
	char negNum[MAX_PLACE];
	initNumber(negNum, MAX_PLACE);
	negNum[0] = '-';
	for (int i = 0; i < strlen(number); i++)
		negNum[i + 1] = number[i];
	strcpy(number, negNum);
}

// Remove negative sign before the number
void removeNegativeSign(char* number)
{
	char posNum[MAX_PLACE];
	initNumber(posNum, MAX_PLACE);
	for (int i = 0; i < strlen(number); i++) 
		posNum[i] = number[i + 1];
	strcpy(number, posNum);
}

// Check whether the formula contains multiply or divide operations
int hasMultiplyOrDivide(const char* op)
{
	for (int i = 0; i < strlen(op); i++) {
		if (op[i] == '*' || op[i] == '/')
			return 1;
	}
	return 0;
}

// Remove a number from number array, e.g. removeNumber(["123", "456", "789"], 1, 3) -> ["123", "789"]
void removeNumber(char number[][MAX_PLACE], int index, int numLength) {
	for (int i = index; i < numLength - 1; i++)
		strcpy(number[i], number[i + 1]);
	initNumber(number[numLength - 1], MAX_PLACE);
}

// Remove an operator from opreator array, e.g. removeOp("+-*/", 1, 4) -> "+*/"
void removeOp(char* op, int index, int opLength) {
	for (int i = index; i < opLength - 1; i++)
		op[i] = op[i + 1];
	op[opLength - 1] = '\0';
}

// Parse the formula in variable input, set numLength to the number of numbers retrieved, opLength to the number of operators retrieved,
// and assign dstnum and dstop to the numbers and operators found
void parse(char* input, int* numLength, int* opLength, char* dstnum, char* dstop) {
	int index = 0;

	char number[50][MAX_PLACE];
	for (int i = 0; i < 50; i++)
		initNumber(number[i], MAX_PLACE);
	int numplace = 0;
	int numpos = 0;

	int decimal;

	char op[99];
	initNumber(op, 99);
	int opplace = 0;

	char exp[10];
	initNumber(exp, 10);
	int expind = 0;

	char tempNum[99];
	initNumber(tempNum, 99);

	char bracketParsing[999];
	initNumber(bracketParsing, 999);

	int parseBracket = 0;
	int parseBracketind = 0;

	while (input[index] != '\0') {
		switch (input[index]) {
		case '+':
		case '-':
		case '*':
		case '/':
			if (parseBracket)
				bracketParsing[parseBracketind] = input[index];
			else {
				if (input[index] == '-' && numpos == 0) {
					number[numplace][numpos] = input[index];
					numpos++;
					index++;
					continue;
				}
				numpos = 0;
				numplace++;
				op[opplace] = input[index];
				opplace++;
			}
			break;
		case 'E':
			if (parseBracket)
				bracketParsing[parseBracketind] = input[index];
			else {
				index++;
				do {
					exp[expind] = input[index++];
					expind++;
				} while (input[index] != '+' && input[index] != '-' && input[index] != '*' && input[index] != '/' && input[index] != '\0');
				for (int i = 0; i < expind; i++) {
					tempNum[i] = exp[i];
				}
				if (tempNum[0] == '-') {
					removeNegativeSign(tempNum);
					if (strlen(tempNum) == 1)
						addDecimal(number[numplace], tempNum[0] - '0');
					else {
						int exp = (tempNum[0] - '0') * 10 + (tempNum[1] - '0');
						addDecimal(number[numplace], exp);
					}
				}
				else {
					if (strlen(tempNum) == 1) {
						decimal = decimal2int(number[numplace]);
						addZero(number[numplace], tempNum[0] - '0', number[numplace]);
						addDecimal(number[numplace], decimal);
					}
					else {
						int exp = (tempNum[0] - '0') * 10 + (tempNum[1] - '0');
						addZero(number[numplace], exp, number[numplace]);
					}

				}
				expind = 0;
				numpos = 0;
				index--;
			}
			break;
		case '(':
			parseBracket = 1;
			index++;
			continue;
			break;
		case ')':
			parseBracket = 0;
			int numLengthBracket = 0;
			int opLengthBracket = 0;
			
			char numberBracket[50][MAX_PLACE];
			for (int i = 0; i < 50; i++)
				initNumber(numberBracket[i], MAX_PLACE);

			char opBracket[99];
			initNumber(opBracket, 99);

			parse(bracketParsing, &numLengthBracket, &opLengthBracket, numberBracket, opBracket);
			calculate(numberBracket, opBracket, &numLengthBracket, &opLengthBracket);

			strcpy(number[numplace], numberBracket);
			break;
		default:
			if (parseBracket)
				bracketParsing[parseBracketind] = input[index];
			else {
				number[numplace][numpos] = input[index];
				numpos++;
			}
			break;
		}
		if(parseBracket)
			parseBracketind++;
		index++;
	}
	
	// Copy the 2D array
	memcpy(dstnum, number, sizeof(char) * 50 * MAX_PLACE);
	strcpy(dstop, op);
	*numLength = numplace + 1;
	*opLength = opplace;
}

// Calculate the result of the parsed formula
void calculate(char number[][MAX_PLACE], char* op, int* numLength, int* opLength) {
	int done = 0;

	while (!done) {
		if (strlen(op) == 0)
			break;
		for (int opCalculate = 0; opCalculate < strlen(op); opCalculate++) {
			int skip = 0;
			if (hasMultiplyOrDivide(op)) {
				switch (op[opCalculate]) {
				case '*':
					multiplication(number[opCalculate], number[opCalculate + 1]);
					break;
				case '/':
					division(number[opCalculate], number[opCalculate + 1]);
					break;
				default:
					skip = 1;
					break;
				}
			}
			else {
				switch (op[opCalculate]) {
				case '+':
					if (number[opCalculate][0] == '-' && number[opCalculate + 1][0] != '-')
						subtraction(number[opCalculate + 1], number[opCalculate]);
					else if (number[opCalculate][0] != '-' && number[opCalculate + 1][0] == '-')
						subtraction(number[opCalculate], number[opCalculate + 1]);
					else if (number[opCalculate][0] == '-' && number[opCalculate + 1][0] == '-') {
						removeNegativeSign(number[opCalculate]);
						removeNegativeSign(number[opCalculate + 1]);
						addition(number[opCalculate], number[opCalculate + 1]);
						addNegativeSign(number[opCalculate]);
					}
					else
						addition(number[opCalculate], number[opCalculate + 1]);
					break;
				case '-':
					subtraction(number[opCalculate], number[opCalculate + 1]);
					break;
					skip = 1;
				default:
					break;
				}
			}
			if (skip)
				continue;
			removeNumber(number, opCalculate + 1, *numLength);
			(*numLength)--;
			removeOp(op, opCalculate, *opLength);
			(*opLength)--;
			opCalculate = -1;
		}
	}
}

int main() {
	char input[999];
	gets(input);

	char result[50][MAX_PLACE];
	int numLength = 0;
	int opLength = 0;
	char op[99];
	initNumber(op, 99);

	parse(input, &numLength, &opLength, result, op);
	calculate(result, op, &numLength, &opLength);
	
	printf("%s", result[0]);
	return 0;
}