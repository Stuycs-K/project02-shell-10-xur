[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

## Team Name - The ONE
## Member(s) - Ray Xu

## Shell Implementations:
- This shell can handle basic commands including but not limited to ls, wc, grep, echo, cat. The shell also handles cd.
- This shell can handle redirect stdin and stdout using respective operators < and >
    - Example for stdin: cat < intput.txt
    - Example for stdout: echo hello > output.txt
- This shell can handle a maximum of one pipe using operator |. This pipe can be combined with redirect stdin/stdout only if the operators are utilized in the following order: < | >.
    - Example: cat < input.txt | grep hello > output.txt

## Possible Bugs:
- If keyboard keys are pressed unintentionally and followed by CTRL+D, it's necessary to hit CTRL+D twice to successfully exit.
- If keyboard keys are pressed unintentionally and followed by 'exit', it's necessary to type exit and hit enter three times to successfully exit. There was an effort made to debug/remedy this but it has not been successful thus far.
- The echo command, when utilized in the following manner, will replicate the entire phrase (including quotation marks) in output.txt as opposed to formatting the phrase with new lines and no quotation marks:
    - echo "apple\nbanana" > output.txt
- The echo command, when utilized in the following manner, will include the backslash in output.txt as opposed to eliminating it:
    - echo apple\nbanana > output.txt

## Function Headers:
- PRINTERROR
    - No arguments, returns 0 representing successful execution
    - Prints error number and message based on errno set by other functions
- EXECUTE
    - Takes char * (string) and char ** (array of strings)
    - Executes command in string and utilizes args for command from array of strings
    - Command 'cd' is specially handled, otherwise commands passed into execvp
    - Forks into child and parent processes
    - No return value
- PARSE ARGS
    - Takes a char * (string) and empty char ** (array of strings)
    - Function separates the string by spaces and puts each substring into the array of strings
    - No return value but array of strings is modified/filled
- PRINT ASCII
    - Debug function, takes a char * (string)
    - Prints ascii values corresponding to each character of the string
    - No return value
- MAIN
    - No arguments
    - While true loop ensures terminal continues running/prompting until exit or CTRL+D used
    - Returns 0 if executed successfully
- GOPIPE
  - Takes char * (string)
  - Separates string into two pieces around the | pipe operator
  - Executes first string command and pipes output into the input of the second string command
  - Executes second string command
  - No return value
- REDIRIN
    - Takes char ** (array of strings) and int counter
    - Locates file from which stdin should be taken using counter and array of strings
    - Sets stdin as the file, then executes, then reverts stdin
    - No return value
- REDIROUT
    - Takes char ** (array of strings) and int counter
    - Locates file to which stdout should be redirected using counter and array of strings
    - Sets stdout as the file, then executes, then reverts stdout
    - No return value

