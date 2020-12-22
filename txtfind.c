#include <stdio.h>

/* The method counts the number of characters until
it reaches the end of the line and returns the amount */
int getLine(char *s) {
    int count = 0;
    while (*s != EOF && *s != '\n' &&
     *s != '\0' && *s != '\r') {
        count++;
        s=s+1;
    }
    return count;
}

/* The method counts the number of characters until
it reaches the end of the word and returns the amount */
int getWord(char *w) {
    int count = 0;
    while (*w != EOF && *w != '\n' && *w != '\r' &&
     *w != '\t' && *w != '\0' && *w != ' ') {
        count++;
        w=w+1;
    }
    return count;
}

/* compare str2 to st1 */
/* (str1 = text, str1len = current-line-length, str2 = target-word) */
/* The method runs on the entire line and checks if the word is in
sequence in this line by counting the characters and checking the equality */
int substring(char *str1, char *str2 ,int str1len) {
    int str2len = getWord(str2);
    int similarCount = 0;
    for (int i = 0; i<str1len&&*str2!='\0'; i++) {
            if (*str2 == *str1) {
                similarCount++;
                str2++;
                if (str2len==similarCount) return 1;
            } else {
                str2-=similarCount;
                similarCount = 0;
            }
            str1++;
        }
    return 0;
}

/* compare str2 to st1 */
/* (str1 = target-word, str2 = temp-word) */
/* The method checks if the difference of the
2 strings does not exceed 1 and also checks if
there is at most one different letter between them */
int similar(char *str1, char *str2, int str2len) {
    int dif = 0;
    int str1len = getWord(str1);
    if (str2len-str1len>1||str1len-str2len>1) {return 0;}
    int similarCount = 0;
    for (int i = 0; i<str2len&&*str1!='\0';) {
            if (*str2 == *str1) {
                similarCount++;
                str1++;
                str2++;
                i++;
            } else {
                if (*str2!=*(str1+1)) {
                    str2++;
                    i++;
                }
                else str1++;
                dif++;
            }
        }
    if (dif<=1) return 1;
    return 0;
}

/* The method iterates the lines and prints
the line if it contains the given word */
void print_lines(char *s, char *str) {
    int counter = 0;
    int nextLineLength = 0;
    int bool = 1;
    while (bool) {
        nextLineLength = getLine(s);
        if (substring(s, str, nextLineLength)==1) {
            printf("%.*s\n", nextLineLength, s);
        }
        counter = nextLineLength+1;
        s+=counter;
        if (*s == '\0') bool = 0;
    }
}

/* The method iterates the words and prints
the word if it similar to the given word */
void print_similar_words(char *str1, char *str2) {
    int wordlen;
    char *wordpointer = str1;
    while (*wordpointer!='\0'&&*wordpointer!=EOF) {
        wordlen = getWord(wordpointer);
        if (wordlen==0) {
            wordpointer++;
        } else {
            if (similar (str2, wordpointer, wordlen)==1) {
                printf("%.*s\n", wordlen, wordpointer);
            }
            wordpointer+=(wordlen+1);
        }
    }
}

int main() {
    /* get proper array length according to the input in the buffer */
    fseek (stdin, 0, SEEK_END);
    int length = ftell (stdin);
    fseek (stdin, 0, SEEK_SET);
    /* declare the fileinput array */
    char fileinput[length];
    fread(fileinput, 1, length, stdin);
    /* pointer1 = target-word */
    char *pointer1 = fileinput;
    fileinput[getWord(pointer1)] = '\0';
    /* pointer2 = option */
    char *pointer2 = pointer1+getWord(pointer1)+1;
    fileinput[getWord(pointer1)+1+getWord(pointer2)] = '\0';
    /* pointer3 = text */
    char *pointer3 = pointer2+getWord(pointer2)+3;
    /* call method that implement the selected option */
    if (*pointer2=='a') print_lines(pointer3,pointer1);
    else if (*pointer2=='b') print_similar_words(pointer3, pointer1);
    return 0;
}