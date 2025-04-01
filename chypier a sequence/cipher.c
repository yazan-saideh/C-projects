#include "cipher.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.


// See full documentation in header file
void cipher (char s[], int k)
{
  k = k % 26;
  // your code goes here
  for(int i = 0; s[i] != '\0'; i++)
  {
    if (s[i] >= 'a' && s[i] <= 'z')
    {
      // Shift for lowercase letters
      if (s[i] + k > 'z')
      {
        s[i] = (s[i] + k) - 26; // go to 'a' if it goes beyond 'z'
      }
      else if (s[i] + k < 'a')
      {
        s[i] = s[i] + k + 26; //go to 'z' if it goes below 'a'
      }
      else
      {
        s[i] = s[i] + k; // Normal shift within the 'a' to 'z' range
      }
    }
    else if (s[i] >= 'A' && s[i] <= 'Z') {
      // Shift  for uppercase letters
      if (s[i] + k > 'Z')
      {
        s[i] = s[i] + k - 26;
      }
      else if (s[i] + k < 'A')
      {
        s[i] = s[i] + k + 26;
      }
      else
      {
        s[i] = s[i] + k;
      }
    }
  }
}


// See full documentation in header file
void decipher (char s[], int k)
{
  // your code goes here
  // make sure that k handles big numbers
   k = (-k % 26 + 26) % 26;
  for(int i = 0; s[i] != '\0'; i++)
  {
    if (s[i] >= 'a' && s[i] <= 'z')
    {
      //make sure not to go over the z
      if (s[i] + k > 'z')
      {
        s[i] = s[i] + k - 26; // go to 'a' if it goes beyond 'z'
      }
      else if (s[i] + k < 'a')
      {
        s[i] = s[i] + k + 26; // go to 'z' if it goes below 'a'
      }
      else
      {
        s[i] = s[i] + k; // Normal shift within the 'a' and 'z'
      }
    }
    else if (s[i] >= 'A' && s[i] <= 'Z') {
      // Shift for uppercase letters
      if (s[i] + k > 'Z')
      {
        s[i] = s[i] + k - 26;
      }
      else if (s[i] + k < 'A')
      {
        s[i] = s[i] + k + 26;
      }
      else
      {
        s[i] = s[i] + k;
      }
    }
  }
}
