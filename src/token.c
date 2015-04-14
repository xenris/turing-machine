#include "token.h"

Token* tokenGetNext(FILE* file) {
    const int maxLineLength = 512;
    char line[maxLineLength];
    char linecpy[maxLineLength];

    if(!fgets(line, maxLineLength, file)) {
        return tokenCreate(T_EOF, NULL);
    }

    line[strlen(line) - 1] = '\0';

    strcpy(linecpy, line);

    char* tok = strtok(linecpy, " ");

    if((tok == NULL) || (strncmp(tok, "//", 2) == 0)) {
        return tokenGetNext(file);
    }

    if(strcmp(tok, "alphabet") == 0) {
        tok = strtok(NULL, " ");

        if((tok == NULL) || (strcmp(tok, "=") != 0)) {
            printf("Error: Expected \"=\" after \"alphabet\" in \"%s\"\n", line);
            return tokenCreate(ERROR, NULL);
        } else {
            tok = strtok(NULL, " ");

            if(tok == NULL) {
                printf("Error: Expected characters after \"alphabet = \" in \"%s\"\n", line);
                return tokenCreate(ERROR, NULL);
            } else {
                return tokenCreate(ALPHABET, tok);
            }
        }
    } else if(strcmp(tok, "blank") == 0) {
        tok = strtok(NULL, " ");

        if((tok == NULL) || (strcmp(tok, "=") != 0)) {
            printf("Error: Expected \"=\" after \"blank\" in \"%s\"\n", line);
            return tokenCreate(ERROR, NULL);
        } else {
            tok = strtok(NULL, " ");

            if((tok == NULL) || (strlen(tok) > 1)) {
                printf("Error: Expected single character after \"blank = \" in \"%s\"\n", line);
                return tokenCreate(ERROR, NULL);
            } else {
                return tokenCreate(BLANK, tok);
            }
        }
    } else if(strcmp(tok, "initial") == 0) {
        tok = strtok(NULL, " ");

        if((tok == NULL) || (strcmp(tok, "=") != 0)) {
            printf("Error: Expected \"=\" after \"initial\" in \"%s\"\n", line);
            return tokenCreate(ERROR, NULL);
        } else {
            tok = strtok(NULL, " ");

            if((tok == NULL) || (!isupper(tok[0]))) {
                printf("Error: Expected state after \"initial = \" in \"%s\"\n", line);
                return tokenCreate(ERROR, NULL);
            } else {
                return tokenCreate(INITIAL, tok);
            }
        }
    } else if(isupper(tok[0])) {
        Token* token = tokenCreate(TRANSITION, tok);

        tok = strtok(NULL, " ");

        if((tok == NULL) || (strlen(tok) > 1)) {
            printf("Error: Expected single input character in \"%s\"\n", line);
            return tokenCreate(ERROR, NULL);
        } else {
            token->input = tok[0];

            tok = strtok(NULL, " ");

            if((tok == NULL) || (strlen(tok) > 1)) {
                printf("Error: Expected single output character in \"%s\"\n", line);
                return tokenCreate(ERROR, NULL);
            } else {
                token->output = tok[0];

                tok = strtok(NULL, " ");

                if((tok == NULL) || (strlen(tok) > 1) || ((tok[0] != 'l') && (tok[0] != 'r'))) {
                    printf("Error: Expected \"l\" or \"r\" in 4th argument of \"%s\"\n", line);
                    return tokenCreate(ERROR, NULL);
                } else {
                    token->direction = tok[0];

                    tok = strtok(NULL, " ");

                    if((tok == NULL) || !isupper(tok[0])) {
                        printf("Error: Expected next state in \"%s\"\n", line);
                        return tokenCreate(ERROR, NULL);
                    } else {
                        token->next = stringCopy(tok);

                        return token;
                    }
                }
            }
        }
    } else {
        printf("Warning: I didn't understand this line \"%s\"\n", line);
        return tokenCreate(ERROR, NULL);
    }
}

Token* tokenCreate(TokenType type, char* value) {
    Token* token = malloc(sizeof(Token));

    token->type = type;

    if(value != NULL) {
        token->value = stringCopy(value);
    } else {
        token->value = NULL;
    }

    token->input = '\0';
    token->output = '\0';
    token->direction = '\0';
    token->next = NULL;

    return token;
}

void tokenDelete(Token* token) {
    if(token == NULL) {
        return;
    }

    if(token->value != NULL) {
        free(token->value);
    }

    if(token->next != NULL) {
        free(token->next);
    }

    free(token);
}
