# BrickStudios' guidelines
## Naming things
- Use `snake_case` for variables.
- Use `CaptialCase` for Types.
- Use `camelCase` for functions.

## Spaces, Spacing and Bracing
- Every comma is followed by a space, so for example
`myFunction(int a, int b, int c)`

- Spaces after every operator
`13 + 37` instead of `13+37`

- Use tabs to indent your code, the tabs must be the same as 4 spaces.

- Curly braces on a seperate line, except if the code inside the block is only one line.
So both

```c++
if (condition)
    return true;
```

and

```c++
if (condition)
{
    int i = 1;
    return i;
}
```
are good to use.

## Other
- Comment code where you think it is necessary.
- Everything must be `const` correct.
- Use smart pointers.
- Write the constructor and destructor at the same time so you do not forget to properly `delete`.

## Git
- Commit in English.
- Write short but descriptive commit messages.
- If you want to be cool, add a GPG key to your Github account to be "Verified".

