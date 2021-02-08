/* changes integer to binary
    *
    * Time spent: 3hrs
    *
    * author: Charlotte Berl
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Helper functions implemented for you.
#include "binary_helpers.h"

//Functions you need to implement.
void int_to_unsigned(long int_input, int unsigned_output[], int num_bits);
void int_to_twos(long int_input, int twos_output[], int num_bits);

//You should not modify main.
int main(int argc, char* argv[]){
    int converted_to_unsigned[MAX_BITS], converted_to_twos[MAX_BITS], num_bits;
    long int_input;

    //Read and validate input.
    if(argc != 3){
        printf("usage: ./to_binary num_bits int_input\n");
        return 1;
    }
    num_bits = atoi(argv[1]);
    if(num_bits > MAX_BITS || num_bits < 0){
        printf("num_bits must be between 0 and %d\n", MAX_BITS);
        return 1;
    }
    int_input = atol(argv[2]);

    //Convert int_input to unsigned.
    if( validate_unisigned(int_input, num_bits) ){
        int_to_unsigned(int_input, converted_to_unsigned, num_bits);
        printf("converted to unsigned: ");
        print_binary(converted_to_unsigned, num_bits);
        printf("\n");
    }else{
        printf("not a valid %d-bit unsigned integer\n", num_bits);
    }

    //Convert int_input to twos complement.
    if( validate_twos(int_input, num_bits) ){
        int_to_twos(int_input, converted_to_twos, num_bits);
        printf("converted to twos complement: ");
        print_binary(converted_to_twos, num_bits);
        printf("\n");
    }else{
        printf("not a valid %d-bit twos complement integer\n", num_bits);
    }

    return 0;
}


/* int_to_unsigned() converts an integer into unsigned binary.
 *
 * The binary value is represented an array of integers with size num_bits.
 * Because the number reads from left to right, the most significant bit is at
 * index 0 in the array, and the 1s digit is at index num_bits - 1.
 *
 * ARGUMENTS:
 *   int_input: This is the integer to be converted to binary. You may assume
 *           that int_input is always between 0 and 2^num_bits - 1,
 *           inclusive.
 *   unsigned_output: This is the array of size num_bits that will hold the
 *           1s and 0s of the number's unsigned binary representation. This
 *           array initially contains garbage values, so every entry should
 *           be replaced by a 1 or a 0.
 *   num_bits: The size of the array.
 *
 * NOTE: As we've seen in the stack diagram exercises, C doesn't play nice with
 * returning arrays from a function, but functions can modify arrays that are
 * passed in. When implementing this function, you should think of the
 * unsigned_output array as the return value. Make sure that by the end of the
 * function this array holds the correct unsigned binary representation
 * of the input integer.
 */
void int_to_unsigned(long int_input, int unsigned_output[], int num_bits){
  long number = int_input;
  int count = 0;
  //tot is total
  for (int n=num_bits;n>0;n--){
    long tot = 1;
    for(int j=n-1;j>0;j--){
      tot = tot*2;
    }
    if(number>=tot) {
      unsigned_output[count] = 1;
      number = number - tot;
    } else {
      unsigned_output[count] = 0;
    }
    count++;
  }

}


/* int_to_twos() converts an integer into two's complement binary.
 *
 * The binary value is represented an array of integers with size num_bits.
 * Because the number reads from left to right, the sign bit is at index 0 in
 * the array, and the 1s digit is at index num_bits - 1.
 *
 * ARGUMENTS:
 *   int_input: this is the integer to be converted to binary. You may assume
 *           that int_input is always between -(2^(num_bits-1)) and
 *           (2^(num_bits-1) - 1), inclusive.
 *   twos_output: this is the array of size num_bits that will hold the
 *           1s and 0s of the number's two's complement binary
 *           representation. This array initially contains garbage values,
 *           so every entry should be replaced by a 1 or a 0.
 *   num_bits: The size of the array.
 *
 * NOTE: As we've seen in the stack diagram exercises, C doesn't play nice with
 * returning arrays from a function, but functions can modify arrays that are
 * passed in. When implementing this function, you should think of the
 * twos_output array as the return value. Make sure that by the end of the
 * function this array holds the correct twos complement binary representation
 * of the input integer.
 */
void int_to_twos(long int_input, int twos_output[], int num_bits){
  long number = int_input;
  if (number<0) {
    twos_output[0] = 1;
    number -= -pow(2,num_bits-1);
  } else {
    twos_output[0] = 0;
  }
  int count = 1;
    for (int n=num_bits-1;n>=1;n--){
        if(number>=pow(2,n-1)) {
          twos_output[count] = 1;
          number -= pow(2,n-1);
        } else {
          twos_output[count] = 0;
        }
        count++;
      }
  }
