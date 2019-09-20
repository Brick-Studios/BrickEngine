# BrickStudios' guidelines
## Naming things
- Use `snake_case` for variables and file names.
- Use `CaptialCase` for Types.
- Use `camelCase` for functions.

## Include all the things!
- Always use include guards.

```c++
#ifndef FILE_*FILENAME*_HPP
#define FILE_*FILENAME*_HPP

// Your code here

#endif /* FILE_*FILENAME*_HPP */
```

# Filing your taxes
- Put header files in the include/ folder and use the .hpp extention.
- Put source files in the lib/ folder and use the .cpp extention.
- Structure your code in sensible and modular folders and files.

## Spaces, Spacing and Bracing
- Every comma is followed by a space, so for example
`myFunction(int a, int b, int c)`

- Spaces after every operator
`13 + 37` instead of `13+37`

- Indent your code with 4 spaces.

- Curly braces on the same line as the statement or function except if there is only one line in the code block.

```c++
if (condition)
    return true;
```

and

```c++
if (condition) {
    int i = 1;
    return i;
}
```
are good to use.

## Other
- Comment code where you think it is necessary.
- Everything must be `const` correct.
- Use smart pointers whenever possible. If smartpointers can not be used, use RAII and the Rule of Five.
- Write the constructor and destructor at the same time so you do not forget to properly `delete`.

## Git
- Commit in English.
- Write short but descriptive commit messages.
- If you want to be cool, add a GPG key to your Github account to be "Verified".

