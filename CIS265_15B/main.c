/*************************************************************************
* Title: (CIS265_15B) Locale Info 
* File: main.c
* Author: James Eli
* Date: 9/19/2017
*
* Instead of the passing the locale (i.e. "fi_FI") as a command line please 
* prompt the user to enter the locale. If it's valid, display the output as 
* described in the exercise. If not, display a message saying that the locale 
* is not valid and then prompt again till user chooses to quit the program
* Write a program that obtains the name of a locale from the command line and 
* then displays the values stored in the corresponding lconv structure. For 
* example, if the locale is “fi_FI” (Finland), the output of the program 
* might look like this:
*   decimal_point = “,”
*   thousands_sep = “ “
*   grouping = 3
*   ...
*   int_n_sep_by_space = 2
*   int_p_sign_posn = 1
*   int_n_sign_posn = 1
* For readability, the characters in the grouping and mon_grouping should be 
* displayed as decimal numbers.
*
* Notes:
*  (1) The MS version seems to accept almost any input, however it does seem
*      to perform validity checks on longer strings.
*  (2) Because of this, I perform almost no validity checks on the input,
*      and allow the setlocale() function to have at it.
*  (3) Due to the odd nature of the MS version (see note 1), I decided to 
*      write 2 versions of the program (MSVC and GNU GCC).
*  (4) Compiled with MS Visual Studio 2017 Community (v141) and Eclipse
*      GCC 5.3.0, using C language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/19/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

#ifdef _MSC_VER
// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#define STRING_LENGTH      85     // Maximum acceptable input string length.
#define MAX_INPUT_ATTEMPTS 3      // Maximum invalid input attempts before aborting. 
#define TERMINATION_STRING "quit" // Input string that terminates program.

// Print character numeric value or "not available".
static void printAvailability(const char *format, const char c) {
	char s[2] = { 0 };

	*s = '0' + c;	// Insert character into a 1-character string.
	fprintf(stdout, format, (c == CHAR_MAX) ? "not available" : s);
}

// Display contents of locale lconv structure.
static void printLocale(const struct lconv *lc) {
	assert(lc != NULL);

	printf(" decimal_point = \"%s\"\n", lc->decimal_point);
	printf(" thousands_sep = \"%s\"\n", lc->thousands_sep);
	printf(" grouping = %c\n", '0' + *lc->grouping);

	printf(" mon_deciaml_point = \"%s\"\n", lc->mon_decimal_point);
	printf(" mon_thousands_sep = \"%s\"\n", lc->mon_thousands_sep);
	printf(" mon_grouping = %c\n", '0' + *lc->mon_grouping);

	printf(" positive_sign = \"%s\"\n", lc->positive_sign);
	printf(" negative_sign = \"%s\"\n", lc->negative_sign);

	printf(" currency_symbol = \"%s\"\n", lc->currency_symbol);

	printAvailability(" frac_digits = %s\n", lc->frac_digits);
	
	printAvailability(" p_cs_precedes = %s\n", lc->p_cs_precedes);
	printAvailability(" n_cs_precedes = %s\n", lc->n_cs_precedes);

	printAvailability(" p_sep_by_space = %s\n", lc->p_sep_by_space);
	printAvailability(" n_sep_by_space = %s\n", lc->n_sep_by_space);

	printAvailability(" p_sign_posn = %s\n", lc->p_sign_posn);
	printAvailability(" n_sign_posn = %s\n", lc->n_sign_posn);

	printf(" int_curr_symbol = \"%s\"\n", lc->int_curr_symbol);
	printAvailability(" int_frac_digits = %s\n\n", lc->int_frac_digits);
}

int main(void) {
	int attempts = MAX_INPUT_ATTEMPTS; // Input attempt counter.

	// Required to make eclipse console output work properly.
	setvbuf(stdout, NULL, _IONBF, 0);
	fflush(stdout);

	assert(attempts > 0); // Assert attempts valid non-zero, positive number.

	// Attempt only so many inputs.
	while (attempts--) {
		char locale[STRING_LENGTH]; // String holds user input.
										   
		// Prompt and grab user input.
		fputs("Enter a locale country (\"quit\" to terminate): ", stdout);
		if (!fgets(locale, STRING_LENGTH, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(locale, '\n')) {
			// input too long, eat remainder.
			while (fgets(locale, STRING_LENGTH, stdin) && !strchr(locale, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			// Remove trailing '\n' character.
			if (*(locale + strlen(locale) - 1) == '\n')
				*(locale + strlen(locale) - 1) = 0;

			// Check (caseless) for termination.
			if (_stricmp(locale, TERMINATION_STRING) == 0)
				break;

			// Attempt to set locale.
			char *temp = NULL;
			temp = setlocale(LC_ALL, locale);

			if (temp == NULL) 
				printf("Locale information for \"%s\" not available.\n", locale);
			else {
				// Attempt to retrieve locale info structure.
				struct lconv *lc = localeconv();

				if (lc == NULL) {
					fputs("Failure attempting to retrieve locale lconv structure.\n", stdout);
					continue;
				}
				printf("Locale \"%s\" lconv structure members:\n", temp);
				printLocale(lc);
				// Reset invalid input counter.
				attempts = MAX_INPUT_ATTEMPTS; 
			}
		}
	}
}

