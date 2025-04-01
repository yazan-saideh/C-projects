#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cipher.h"
#include "tests.h"
#define TEST_ARG_NUMBER_ERR "The program receives 1 or 4 arguments only.\n"
#define TEST_ARG_TEST_ERR "Usage: cipher test\n"
#define TEST_ARG_COMMAND_ERR "The given command is invalid.\n"
#define TEST_K_ERR "The given shift value is invalid.\n"
#define TEST_FILE_ERR "The given file is invalid.\n"


int test_func(void);

_Bool check_k(char k[]);

int files(int i,const char * command,
    const char * input_path,const char * output_path);

int main (int argc, char *argv[])
{   //check the amount of args
    if (argc != 5  && argc != 2) {
        fprintf(stderr, TEST_ARG_NUMBER_ERR);
        return EXIT_FAILURE;}
    if (argc == 5) {//check when the user enters 5 args
        char *command = argv[1];
        char *input_path = argv[3];
        char *output_path = argv[4];
        if (strcmp(command, "cipher") != 0
            && strcmp(command, "decipher") != 0) {
            fprintf(stderr, TEST_ARG_COMMAND_ERR);
            return EXIT_FAILURE;}
        int k;
        if (check_k(argv[2])) {
            k = strtol(argv[2], NULL, 10);}
        else {
            fprintf(stderr, TEST_K_ERR);
            return EXIT_FAILURE;
        }
        if (files(k, command, input_path, output_path)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    if (argc == 2) {
        char *command = argv[1];
        if (strcmp(command, "test") == 0) {
            if(test_func() == EXIT_SUCCESS) {
                return EXIT_SUCCESS;}
        }
        fprintf(stderr, TEST_ARG_TEST_ERR);
        return EXIT_FAILURE;
    }
}

int test_func() {
    if (test_cipher_non_cyclic_lower_case_positive_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_cipher_cyclic_lower_case_special_char_positive_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_cipher_non_cyclic_lower_case_special_char_negative_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_cipher_cyclic_lower_case_negative_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_cipher_cyclic_upper_case_positive_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_decipher_non_cyclic_lower_case_positive_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_decipher_cyclic_lower_case_special_char_positive_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_decipher_non_cyclic_lower_case_special_char_negative_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_decipher_cyclic_lower_case_negative_k() != 0) {
        return EXIT_FAILURE;
    }

    if (test_decipher_cyclic_upper_case_positive_k() != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

_Bool check_k(char k[]) {
    //check if k is negative or positive
    int start = 0;
    if (k[0] == '-')
    {
    start = 1;
    }
    for(int i = start; k[i] != '\0' ; i++) {
        if (k[i] < '0' || k[i] > '9') {
            return false;
        }
    }
    return true;
}

int files(int k ,const char *command,
    const char *input_path, const char *output_path) {

    // open an input and an output files
    FILE *input_file = fopen(input_path, "r");
    FILE *output_file = fopen(output_path, "w");
    if (!input_file || !output_file) {
        fprintf(stderr, TEST_FILE_ERR);
        return EXIT_FAILURE;
    }
    char line[1024];
    while (fgets(line, sizeof(line), input_file)) {
        if (strcmp(command, "cipher") == 0) {
            cipher(line, k);  // cipher the line
        }
        else if (strcmp(command, "decipher") == 0) {
            decipher(line, k);// decipher the line
        }
        fputs(line, output_file);
    }
    // Close the files
    fclose(input_file);
    fclose(output_file);
    return EXIT_SUCCESS;
}