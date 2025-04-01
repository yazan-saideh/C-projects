#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#define MAX_LINE_LENGTH 60
#define MAX_info_LENGTH 21
#define EXIT_CHECK 3
#define TEST_NUM 6
#define SORT_BY_NAME 7
#define TEST_NUM2 8
#define BY_DURATION "by_duration"
#define BY_DISTANCE "by_distance"
#define BY_NAME "by_name"
#define TEST "test"
#define USAGE_ERR "Usage: Enter (by_duration, by_distance, by_name,test)\n"
#define DISTANCE_ERROR "Error: distance should be an integer "\
"between 0 and 1000 (includes)\n"
#define DURATION_ERROR "Error: duration should be an integer "\
"between 10 and 100 (includes)\n"
#define ENTER_LINE_INFO "Enter line info. Then enter\n"
#define ENTER_NUMBER_OF_LINES "Enter number of lines. Then enter\n"
#define FORMAT_ERR "Error: Use name,duration,distance format.\n"
#define INVALID_INPUT "Error: input must be a valid number.\n"
#define NUM_ERR "Error: Number of lines should be a positive integer\n"
#define NAME_ERORR "Error: bus name should contains"\
 " only digits and small chars\n"
#define TEST1_PASSED "TEST 1 PASSED: The array is sorted by distance\n"
#define TEST2_PASSED "TEST 2 PASSED: The array has "\
"the same items after sorting\n"
#define TEST3_PASSED "TEST 3 PASSED: The array is sorted by duration\n"
#define TEST4_PASSED "TEST 4 PASSED: The array has "\
 "the same items after sorting\n"
#define TEST5_PASSED "TEST 5 PASSED: The array is sorted by name\n"
#define TEST6_PASSED "TEST 6 PASSED: The array has "\
"the same items after sorting\n"
#define TEST1_FAILED "TEST 1 FAILED: The array is not sorted by distance\n"
#define TEST2_FAILED "TEST 2 FAILED: The array is"\
 " not the same items after sorting\n"
#define TEST3_FAILED "TEST 3 FAILED: The array is not sorted by duration\n"
#define TEST4_FAILED "TEST 4 FAILED: The array is not "\
 "the same items after sorting\n"
#define TEST5_FAILED "TEST 5 FAILED: The array is not sorted by name\n"
#define TEST6_FAILED "TEST 6 FAILED: the array is not "\
 " the same items after sorting\n"

/**
 * TODO add documentation
 */
//check the line info
_Bool check_line_info(const char* line_name1
 ,const char *distance,const int duration1) {
 long distance1 = 0;
 for(size_t i = 0; i < strlen(distance); i++) {
  if (distance[i] < '0' || distance[i] > '9') {
   fprintf(stdout,DISTANCE_ERROR);
   return false;
  }
 }
 distance1 = strtol(distance, NULL, 10);
 if (distance1 < 0 || distance1 > 1000) {
  fprintf(stdout,DISTANCE_ERROR);
  return false;
 }
 if (duration1 < 10 || duration1 > 100) {
  fprintf(stdout,DURATION_ERROR);
  return false;
 }
 // Validate line name
 unsigned long line_name_len = strlen(line_name1);
 for (unsigned long i = 0; i < line_name_len; i++) {
  // Ensure each character is alphanumeric (0-9, a-z)
  if (!((line_name1[i] >= '0' && line_name1[i] <= '9') ||
        (line_name1[i] >= 'a' && line_name1[i] <= 'z'))) {
   fprintf(stdout,NAME_ERORR);
   return false;}
 }
 return true;
}

//check the filter info and assigne a value for it
SortType check_filter_info(const char* filter, SortType sort_type) {
 if (strcmp(filter, BY_DISTANCE) == 0) {
  sort_type = DISTANCE;
 } else if (strcmp(filter, BY_DURATION) == 0) {
  sort_type = DURATION;}
 else if (strcmp(filter, BY_NAME) == 0) {
  return SORT_BY_NAME;
 }
 else if(strcmp(filter, TEST) == 0) {
   return TEST_NUM2;
 }
 else {
  return EXIT_CHECK;
 }
 return sort_type;
}

//create an array of buslines in the memory based on the user
//inputs
BusLine *create_bus_lines(long number_lines , int distance
 , int duration , char line_name[]) {
 BusLine *bus_lines = malloc(sizeof(BusLine) * number_lines);
 if (bus_lines == NULL) {
  return NULL;
 }
 char line_info[MAX_LINE_LENGTH] = {0};
 int i = 0;
 while (i < number_lines) {//retry if there is an invalid input
  fprintf(stdout, ENTER_LINE_INFO);
  if (!fgets(line_info, MAX_LINE_LENGTH, stdin)) {
   continue;
  }
  line_info[strcspn(line_info, "\n")] = '\0';  // Remove newline character
  char distance_char[MAX_info_LENGTH] = {0};
  if (sscanf(line_info, "%20[^,],%20[^,],%d",
   line_name, distance_char, &duration) != 3) {
   fprintf(stdout, FORMAT_ERR);
   continue;
  }
  if (!check_line_info(line_name, distance_char, duration)) {
   continue;
  }
  distance = strtol(distance_char, NULL, 10);
  bus_lines[i].distance = distance;
  bus_lines[i].duration = duration;
  strncpy(bus_lines[i].name, line_name, MAX_info_LENGTH - 1);
  bus_lines[i].name[MAX_info_LENGTH - 1] = '\0';
  i++;
 }
 return bus_lines;
}
//check is equal test
_Bool is_equal_test(const BusLine *start_orignal
 , const BusLine *end_orignal, const BusLine *start_sorted
 , char failed[],char passed[]) {
 if(is_equal(start_orignal,end_orignal , start_sorted,
   start_sorted + (end_orignal - start_orignal))) {
  fprintf(stdout,"%s", passed);
  return true;
   }
 fprintf(stdout,"%s", failed);
 return false;

}
//check tests
int test_bus_lines(BusLine *start_orignal, BusLine *end_orignal) {
 int counter = TEST_NUM;
 BusLine *current_bus = malloc(sizeof(BusLine)
  * (end_orignal - start_orignal));
 if (current_bus == NULL) {
  return EXIT_FAILURE;
 }
 memcpy(current_bus, start_orignal, sizeof(BusLine)
  * (end_orignal - start_orignal));
 if(is_sorted_by_distance(start_orignal, end_orignal)){
  counter--;
  fprintf(stdout, TEST1_FAILED);
 }
 else {
  fprintf(stdout, TEST1_PASSED);
 }
 quick_sort(start_orignal,end_orignal,DISTANCE);
 if(!is_equal_test(start_orignal,end_orignal,
  current_bus,TEST2_FAILED,TEST2_PASSED)) {
  counter--;
 }
 if(is_sorted_by_duration(start_orignal, end_orignal)) {
  counter--;
  fprintf(stdout, TEST3_FAILED);
 }
 else {
  fprintf(stdout, TEST3_PASSED);
 }
 quick_sort(start_orignal,end_orignal,DURATION);
 if(!is_equal_test(start_orignal,end_orignal,
  current_bus,TEST4_FAILED,TEST4_PASSED)) {
  counter--;
 }
 if(is_sorted_by_name(start_orignal, end_orignal)) {
  counter--;
  fprintf(stdout, TEST5_FAILED);
 }
 else {
  fprintf(stdout, TEST5_PASSED);
 }
 bubble_sort(start_orignal, end_orignal);
 if(!is_equal_test(start_orignal,end_orignal,
  current_bus,TEST6_FAILED,TEST6_PASSED)) {
  counter--;
 }
 if (counter == TEST_NUM) {
  free(current_bus);
  return EXIT_SUCCESS;
 }
 free(current_bus);
 return EXIT_FAILURE;
}
//take the number of the lines from the input
int num_line(char number_of_lines[]) {
 long number_lines = 0;
 char *ptr;
 while(true) {
  fprintf(stdout, ENTER_NUMBER_OF_LINES);
  if(!fgets(number_of_lines, MAX_LINE_LENGTH, stdin)) {
  }
  number_of_lines[strcspn(number_of_lines, "\n")] = '\0';
  if (strspn(number_of_lines, "0123456789")
   != strlen(number_of_lines)) {
   fprintf(stdout, NUM_ERR);
   continue;
  }
  number_lines = strtol(number_of_lines, &ptr, 10);
  if(number_lines <= 0) {
   fprintf(stdout,NUM_ERR );}
  else {
   return number_lines;
   }
 }
}

int main (int argc, char *argv[]) {
 if (argc != 2) {
  return EXIT_FAILURE;
 }
 char *filter = argv[1];
 SortType sort_type = DISTANCE;
 char number_of_lines[MAX_LINE_LENGTH] = {0};
 char line_name[MAX_info_LENGTH] = {0};
 int distance = 0,duration = 0;
 _Bool is_bubble_sort = false,is_test = false;
 if(check_filter_info(filter, sort_type) == TEST_NUM2) {
  is_test = true;//check if the user chose test as arg
 }
 else if(check_filter_info(filter, sort_type) == EXIT_CHECK) {
  fprintf(stdout, USAGE_ERR);//if the user typed anything else
   return EXIT_FAILURE;
 }
 else if(check_filter_info(filter, sort_type) == SORT_BY_NAME) {
  is_bubble_sort = true;//check the sort type (bubble,quick)
 }
 int number_lines = num_line(number_of_lines);
 BusLine *bus_lines = create_bus_lines(number_lines
  , distance, duration, line_name);
 if (!bus_lines) {
  return EXIT_FAILURE;
 }
 if(!is_test)
 {sort_type = check_filter_info(filter, sort_type);
  if(is_bubble_sort) {
   bubble_sort(bus_lines,bus_lines + number_lines);
  }
  else {
   quick_sort(bus_lines, bus_lines + number_lines, sort_type);
  }
  for (BusLine *current_bus = bus_lines; current_bus
   < bus_lines + number_lines; current_bus++) {
   fprintf(stdout,"%s,%d,%d\n", current_bus->name,
    current_bus->distance, current_bus->duration);
  }
  free(bus_lines);
  return EXIT_SUCCESS;
 }
  if(test_bus_lines(bus_lines, bus_lines + number_lines)) {
   free(bus_lines);
   return EXIT_FAILURE;
  }
  free(bus_lines);
  return EXIT_SUCCESS;
 }




