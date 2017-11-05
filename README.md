# Pima CC CIS265 Week #15 Project B

Instead of the passing the locale (i.e. "fi_FI") as a command line please prompt the user to enter the locale. If it's valid, display the output as described in the exercise. If not, display a message saying that the locale is not valid and then prompt again till user chooses to quit the program.

Write a program that obtains the name of a locale from the command line and then displays the values stored in the corresponding lconv structure. For example, if the locale is “fi_FI” (Finland), the output of the program might look like this:
```Text
  decimal_point = “,”
  thousands_sep = “ “
  grouping = 3
  ...
  int_n_sep_by_space = 2
  int_p_sign_posn = 1
  int_n_sign_posn = 1
```
For readability, the characters in the `grouping` and `mon_grouping` should be displayed as decimal numbers.

Notes:
1. The MSVC version seems to accept almost any input, however it does seem to perform validity checks on longer strings.
2. Because of this, I perform almost no validity checks on the input, and allow the `setlocale` function to have at it.
3. Due to the odd nature of the MS version (see note 1), I decided to write 2 versions of the program (MSVC and GNU GCC).
4. Compiled with MS Visual Studio 2017 Community (v141) and Eclipse GCC 5.3.0, using C language options.

*Submitted in partial fulfillment of the requirements of PCC CIS-265.*
