#include <stdio.h>
#include <string.h>

/*
    Classic String/Char Array Interview DSA Questions
    1. Reverse a string in place (no new array)
    2. Check if a string is palindrome
    3. Count frequency of each character
    4. Find the first non-repeating character
    5. Remove duplicate characters from a string
    6. Implement strstr (substring search)
*/

// Calculate the length of a C string
int charArrLength(const char arr[]) {
    int length = 0;
    while (arr[length] != '\0') {
        length++;
    }
    return length;
}

// 1. Reverse a string in place
void reverseString(char str[]) {
    int n = charArrLength(str);
    int i = 0, j = n - 1;
    while (i < j) {
        char t = str[i];
        str[i] = str[j];
        str[j] = t;
        i++; j--;
    }
}

// 2. Check if a string is palindrome
int isPalindrome(const char str[]) {
    int n = charArrLength(str);
    int i = 0, j = n - 1;
    while (i < j) {
        if (str[i] != str[j])
            return 0;
        i++; j--;
    }
    return 1;
}

// 3. Count frequency of each character (lowercase only, for illustration)
void countFrequency(const char str[]) {
    int freq[256] = {0};
    int i = 0;
    while (str[i] != '\0') {
        freq[(unsigned char)str[i]]++;
        i++;
    }
    printf("Character frequencies:\n");
    for (int c = 0; c < 256; c++) {
        if (freq[c] > 0)
            printf("'%c': %d\n", c, freq[c]);
    }
}

// 4. Find the first non-repeating character
char firstNonRepeating(const char str[]) {
    int freq[256] = {0};
    for (int i = 0; str[i] != '\0'; i++)
        freq[(unsigned char)str[i]]++;
    for (int i = 0; str[i] != '\0'; i++)
        if (freq[(unsigned char)str[i]] == 1)
            return str[i];
    return '\0'; // Not found
}

// 5. Remove duplicate characters from a string (in place, preserves order)
void removeDuplicates(char str[]) {
    int seen[256] = {0};
    int i = 0, j = 0;
    while (str[i]) {
        if (!seen[(unsigned char)str[i]]) {
            seen[(unsigned char)str[i]] = 1;
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

// 6. Substring search (implement strstr)
int stringStr(const char hay[], const char needle[]) {
    int n = charArrLength(hay), m = charArrLength(needle);
    if (m == 0) return 0;
    for (int i = 0; i <= n - m; i++) {
        int found = 1;
        for (int j = 0; j < m; j++) {
            if (hay[i + j] != needle[j]) {
                found = 0; break;
            }
        }
        if (found) return i;
    }
    return -1;
}

// Demo main for all above string/char-array ("cooom") DSA interview functions
int main() {
    char str1[100] = "racecar";
    char str2[100] = "hello";
    char str3[200] = "abcabcdef";
    char str4[100] = "banana";
    char substr[20] = "ana";

    // 1. Reverse
    printf("Original: %s\n", str2);
    reverseString(str2);
    printf("Reversed: %s\n", str2);
    reverseString(str2); // restore

    // 2. Palindrome
    printf("Is '%s' palindrome? %s\n", str1, isPalindrome(str1) ? "Yes" : "No");
    printf("Is '%s' palindrome? %s\n", str2, isPalindrome(str2) ? "Yes" : "No");

    // 3. Frequency count
    countFrequency(str4);

    // 4. First non-repeating
    char fnrc = firstNonRepeating(str4);
    if (fnrc)
        printf("First non-repeating character in '%s': '%c'\n", str4, fnrc);
    else
        printf("No non-repeating character in '%s'\n", str4);

    // 5. Remove duplicates
    printf("String before duplicates removal: %s\n", str3);
    removeDuplicates(str3);
    printf("String after duplicates removal: %s\n", str3);

    // 6. Substring search (strstr)
    int pos = stringStr(str4, substr);
    if (pos != -1)
        printf("Substring \"%s\" found at index %d in \"%s\"\n", substr, pos, str4);
    else
        printf("Substring \"%s\" not found in \"%s\"\n", substr, str4);

    return 0;
}
