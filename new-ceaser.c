
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void caesarEncrypt(char *text, char *cipher, int key)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            cipher[i] = (c - base + key) % 26 + base;
        }
        else
        {
            cipher[i] = c;
        }
    }
    cipher[i] = '\0';
    printf("%s\n", cipher);
}
void caesarDecrypt(char *text, char *plain, int key)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            plain[i] = (c - base - key + 26) % 26 + base;
        }
        else
        {
            plain[i] = c;
        }
    }
    plain[i] = '\0';
    printf("%s\n", plain);
}
int main()
{
    FILE *fin, *fout;
    char text[1000], result[1000], filename[200];
    int choice, key;
    printf("Enter key (shift value): ");
    scanf("%d", &key);
    getchar();
    while (1)
    {
        printf("\n1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. End\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1)
        {
            printf("Enter the input file name for encryption: ");
            scanf("%s", filename);
            fin = fopen(filename, "r");
            if (!fin)
            {
                printf("Error: File '%s' not found\n", filename);
                continue;
            }
            fgets(text, sizeof(text), fin);
            fclose(fin);
            caesarEncrypt(text, result, key);
            fout = fopen("encrypt.txt", "w");
            fputs(result, fout);
            fclose(fout);
            printf("Encryption complete. Output saved to encrypt.txt\n");
        }
        else if (choice == 2)
        {
            printf("Enter the encrypted file name (usually encrypt.txt): ");
            scanf("%s", filename);
            fin = fopen(filename, "r");
            if (!fin)
            {
                printf("Error: File '%s' not found\n", filename);
                continue;
            }
            fgets(text, sizeof(text), fin);
            fclose(fin);
            caesarDecrypt(text, result, key);
            fout = fopen("decrypt.txt", "w");
            fputs(result, fout);
            fclose(fout);
            printf("Decryption complete. Output saved to decrypt.txt\n");
        }
        else if (choice == 3)
        {
            printf("Exiting program.\n");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}