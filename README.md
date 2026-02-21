# Cassword

A simple password generator written in C.

## What it does

Generates random, secure passwords that always contain:

- At least one lowercase letter (a-z)
- At least one uppercase letter (A-Z)
- At least one digit (0-9)
- At least one symbol (!@#$%^&\*()-\_=+[]{}<>?)

## How to use

1. Run the program
2. Enter your desired password length (minimum 4)
3. Get your randomly generated password

```
Enter password length (>= 4): 16
Generated Password: k7#Xm@pL2nR!sYq4
```

## How it works

1. **Random Number Generator**: Uses the xorshift128plus algorithm to generate random numbers
2. **Guaranteed Variety**: Places one character from each category (lowercase, uppercase, digit, symbol) into the password
3. **Fill Remaining**: Fills the rest of the password with random characters from all categories
4. **Shuffle**: Randomizes the order so the guaranteed characters aren't always in the same positions

## Strengths

- **Unbiased random selection**: The `random_int()` function rejects values that would cause modulo bias, ensuring fair distribution
- **Guaranteed character diversity**: Every password includes at least one character from each category
- **Fisher-Yates shuffle**: Uses a proper shuffling algorithm to randomize character positions
- **Memory safety**: Properly allocates and frees memory
- **Fast PRNG**: xorshift128plus is efficient and has good statistical properties

## Weaknesses

- **Weak seeding**: Uses `time(NULL)` which is predictable (only ~1 second resolution). An attacker who knows roughly when the password was generated could brute-force the seed
- **Not cryptographically secure**: xorshift128plus is fast but not suitable for cryptographic purposes—its internal state can be recovered from outputs
- **No input validation**: Using `scanf("%d")` without checking return value could cause issues with non-numeric input
- **Fixed character sets**: Users cannot customize which characters to include or exclude

## Future Improvements

- [ ] Use OS-provided entropy for seeding (`/dev/urandom` on Linux, `BCryptGenRandom` on Windows)
- [ ] Replace xorshift128plus with a CSPRNG (Cryptographically Secure PRNG) for security-critical use
- [ ] Add command-line arguments for password length and character set options
- [ ] Allow users to exclude ambiguous characters (like `0`, `O`, `l`, `1`)
- [ ] Add option to generate multiple passwords at once
- [ ] Add password strength estimation
- [ ] Improve input validation and error handling

## Building

Compile with GCC:

```
gcc cassword.c -o cassword.exe
```

Then run:

```
./cassword.exe
```
