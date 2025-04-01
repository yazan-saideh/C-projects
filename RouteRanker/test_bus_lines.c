#include "test_bus_lines.h"

#include <stdlib.h>

#include <stdbool.h>
//TODO add implementation here
int is_sorted_by_distance(const BusLine *start, const BusLine *end) {
    size_t size = end - start;
    BusLine *copy = malloc(size * sizeof(BusLine));
    if (copy == NULL) {
        return EXIT_FAILURE;
    }
    memcpy(copy, start, size * sizeof(BusLine));
    quick_sort(copy, copy + size, DISTANCE);

    for (BusLine *current = copy; current < copy + size - 1; current++) {
        if (current->distance > (current + 1)->distance) {
            free(copy);
            return EXIT_FAILURE;
        }
    }
    free(copy); // Free memory after use
    return EXIT_SUCCESS;
}

int is_sorted_by_duration (const BusLine *start, const BusLine *end) {
    size_t size = end - start;
    BusLine *copy = malloc(size * sizeof(BusLine));
    if (copy == NULL) {
        return EXIT_FAILURE;
    }
    memcpy(copy, start, size * sizeof(BusLine));
    quick_sort(copy, copy + size,DURATION);
    for(const BusLine *current = copy; current < copy + size - 1; current++)
    {
        if(current->duration > (current+ 1)->duration) {
            free(copy);
            return EXIT_FAILURE;
        }
    }
    free(copy);
    return EXIT_SUCCESS;
}
int is_digit2(char c) {
    return (c >= '0' && c <= '9');
}

// Function to check if the string contains only digits
int is_all_digits2(const char *str) {
    while (*str) {
        if (!is_digit2(*str)) {
            return false;
        }
        str++;
    }
    return true;
}


int is_alphabet2(char c) {
    return (c >= 'a' && c <= 'z');
}


int is_all_alpha2(const char *str) {
    while (*str) {
        if (!is_alphabet2(*str)) {
            return false;
        }
        str++;
    }
    return true;
}


int compare_busline2(const BusLine *a, const BusLine *b) {

    if (is_all_digits2(a->name) && is_all_digits2(b->name)) {
        int num1 = strtol(a->name, NULL, 10);
        int num2 = strtol(b->name, NULL, 10);
        return num1 - num2;
    }


    if (is_all_alpha2(a->name) && is_all_alpha2(b->name)) {
        return strcmp(a->name, b->name);
    }

    if (is_all_digits2(a->name) && !is_all_digits2(b->name)) {
        return -1;
    }
    if (!is_all_digits2(a->name) && is_all_digits2(b->name)) {
        return 1;
    }
    const char *str_a = a->name;
    const char *str_b = b->name;

    while (*str_a && *str_b) {
        if (*str_a != *str_b) {
            return *str_a - *str_b;
        }
        str_a++;
        str_b++;
    }

    return *str_a - *str_b;
}


int is_sorted_by_name(const BusLine *start, const BusLine *end) {
    size_t size = end - start;
    BusLine *copy = malloc(size * sizeof(BusLine));
    if (copy == NULL) {
        return EXIT_FAILURE;
    }
    memcpy(copy, start, size * sizeof(BusLine));
    bubble_sort(copy, copy + size);

    for (BusLine *current = copy;
        current < copy + size - 1; current++) {
        if (compare_busline2(current, (current + 1)) > 0) {
            free(copy);
            return EXIT_FAILURE;
        }
    }
    free(copy); // Free memory after use
    return EXIT_SUCCESS;
}

int is_equal(const BusLine *start_sorted,
             const BusLine *end_sorted,
             const BusLine *start_original,
             const BusLine *end_original) {
    if((end_sorted - start_sorted) != (end_original - start_original)){
        return false;
    }
    int counter = 0;
    for(const BusLine *curr_sorted = start_sorted; curr_sorted
        <end_sorted; curr_sorted++){
        for(const BusLine *curr_original = start_original;
            curr_original<end_original; curr_original++) {
            if(strcmp(curr_sorted->name,curr_original->name)==0){
                counter++;
            }
        }
    }
    if (counter != (end_sorted - start_sorted)){
        return false;
    }
    return true;
}


