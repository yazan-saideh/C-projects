#include "sort_bus_lines.h"

#define MAX_NUMBERS 10
#include <stdlib.h>
#include <stdbool.h>
//TODO add implementation here
void swap(BusLine *a, BusLine *b) {
    const BusLine temp = *a;
    *a = *b;
    *b = temp;
}

// Check if the character is a digit
int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

// Function to check if the string is only digits
int is_all_digits(const char *str) {
    while (*str) {
        if (!is_digit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

// Check if the character is an alphabet letter
int is_alphabet(char c) {
    return (c >= 'a' && c <= 'z');
}

// Function to check if the string contains is alphabetic characters
int is_all_alpha(const char *str) {
    while (*str) {
        if (!is_alphabet(*str)) {
            return false;
        }
        str++;
    }
    return true;
}


int compare_busline(const BusLine *a, const BusLine *b) {
    // Check if both names contain only digits
    if (is_all_digits(a->name) && is_all_digits(b->name)) {
        // Compare numbers (numeric strings)
        int num1 = strtol(a->name, NULL, 10);
        int num2 = strtol(b->name, NULL, 10);
        return num1 - num2;
    }

    // Check if both names contain only alphabetic characters
    if (is_all_alpha(a->name) && is_all_alpha(b->name)) {
        return strcmp(a->name, b->name);
    }
    if (is_all_digits(a->name) && !is_all_digits(b->name)) {
        return -1;
    }
    if (!is_all_digits(a->name) && is_all_digits(b->name)) {
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

    // If one string is shorter, the shorter one is considered "less"
    return *str_a - *str_b;
}

// Bubble sort function for BusLines
void bubble_sort(BusLine *start, BusLine *end) {
    for (BusLine *p = start; p < end; p++) {
        for (BusLine *q = start; q < end - 1 - (p - start); q++) {
            if (compare_busline(q, q + 1) > 0) {
                swap(q, q + 1);
            }
        }
    }
}
/**
 * TODO add documentation
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type) {
    if (end - start <= 1) {
        return;
    }
    BusLine *pivot = partition(start, end, sort_type);
    quick_sort(start, pivot, sort_type);
    quick_sort(pivot + 1, end, sort_type);
}




BusLine *partition (BusLine *start, BusLine *end, SortType sort_type) {
    BusLine *start_i = start - 1;
    BusLine *pivot = end - 1;
    if (sort_type == DURATION) {
        for (BusLine *q = start; q < end - 1; q++) {
            if (pivot->duration >= q->duration) {
                start_i++;
                swap(q, start_i);
            }
        }
    }
    else if(sort_type == DISTANCE) {
        for (BusLine *q = start; q < end - 1; q++) {
            if (pivot->distance >= q->distance) {
                start_i++;
                swap(q, start_i);
            }
        }
    }
    swap(pivot, start_i+1);
    return start_i + 1;
}
