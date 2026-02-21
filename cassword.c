#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static uint64_t state[2];

uint64_t xorshift128plus()
{
    uint64_t x = state[0];
    uint64_t const y = state[1];
    state[0] = y;
    x ^= x << 23;
    x ^= x >> 17;
    x ^= y ^ (y >> 26);
    state[1] = x;
    return x + y;
}

void seed_prng()
{
    uint64_t seed = (uint64_t)time(NULL);
    state[0] = seed;
    state[1] = seed ^ 0xdeadbeefcafebabeULL;
}

uint32_t random_int(uint32_t max)
{
    uint64_t r;
    uint64_t limit = UINT64_MAX - (UINT64_MAX % max);

    do
    {
        r = xorshift128plus();
    } while (r >= limit);

    return r % max;
}

void shuffle(char *arr, int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        int j = random_int(i + 1);
        char tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

#define LOWER "abcdefghijklmnopqrstuvwxyz"
#define UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGIT "0123456789"
#define SYMBOL "!@#$%^&*()-_=+[]{}<>?"

int main()
{
    int length;

    printf("Enter password length (>= 4): ");
    scanf("%d", &length);

    if (length < 4)
    {
        printf("Length must be at least 4.\n");
        return 1;
    }

    seed_prng();

    const char *all = LOWER UPPER DIGIT SYMBOL;
    int all_len = strlen(all);

    char *password = malloc(length + 1);
    if (!password)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /*one of each type */
    password[0] = LOWER[random_int(strlen(LOWER))];
    password[1] = UPPER[random_int(strlen(UPPER))];
    password[2] = DIGIT[random_int(strlen(DIGIT))];
    password[3] = SYMBOL[random_int(strlen(SYMBOL))];

    for (int i = 4; i < length; i++)
    {
        password[i] = all[random_int(all_len)];
    }

    shuffle(password, length);

    password[length] = '\0';

    printf("Generated Password: %s\n", password);

    free(password);
    return 0;
}