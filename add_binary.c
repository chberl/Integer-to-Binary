/* adds binary numbers and checks overflow
    *
    * Time spent: 2hrs
    *
    * author: Ariel Urim Chung, Charlotte Berl
*/
#include <stdio.h>
#include <stdlib.h>

//Helper functions implemented for you.
#include "binary_helpers.h"

//Functions you need to implement.
int add_binary(int x[], int y[], int sum[], int carry_in, int size);
void flip_bits(int bits[], int num_bits);
int signed_overflow(int x[], int y[], int sum[]);
int unsigned_overflow(int carry_in, int carry_out);


//You should not modify main.
int main(int argc, char* argv[]){

    //Read and validate input.
    int x[MAX_BITS], y[MAX_BITS], sum[MAX_BITS];
    int carry_out, num_bits;

    if(argc != 4){
        printf("usage: num_bits ./add_binary binary_x binary_y\n");
        return 1;
    }
    num_bits = atoi(argv[1]);
    if(num_bits > MAX_BITS || num_bits < 0){
        printf("num_bits must be between 0 and %d\n", MAX_BITS);
        return 1;
    }
    read_binary(argv[2], x, num_bits);
    read_binary(argv[3], y, num_bits);
    if(!validate_binary(x, num_bits) || !validate_binary(y, num_bits)){
        printf("Invalid %d-bid binary input.\n", num_bits);
        return 1;
    }

    //add and print result
    print_binary(x, num_bits);
    printf(" + ");
    print_binary(y, num_bits);
    printf(" = ");
    carry_out = add_binary(x, y, sum, 0, num_bits);
    print_binary(sum, num_bits);
    printf("\n");
    if(signed_overflow(x, y, sum)){
        printf("Signed Overflow!\n");
    }
    if(unsigned_overflow(0, carry_out)){
        printf("Unsigned Overflow!\n");
    }

    //subtract and print result
    printf("\n");
    print_binary(x, num_bits);
    printf(" - ");
    print_binary(y, num_bits);
    printf(" = ");
    flip_bits(y, num_bits);
    carry_out = add_binary(x, y, sum, 1, num_bits);
    print_binary(sum, num_bits);
    printf("\n");
    if(signed_overflow(x, y, sum)){
        printf("Signed Overflow!\n");
    }
    if(unsigned_overflow(1, carry_out)){
        printf("Unsigned Overflow!\n");
    }

    return 0;
}

/* Adds two binary integers.
 *
 * The two addends and the sum are represented as arrays of integers with size
 * num_tallybits. Because the number reads from left to right, the most significant
 * bit is at index 0 in the array, and the 1s digit is at index num_bits - 1.
 *
 * ARGUMENTS:
 *     x:    The first addend. Integer array with size num_bits. Every
 *         entry in the array is a 1 or a 0.
 *     y:    The second addend. Integer array with size num_bits. Every
 *         entry in the array is a 1 or a 0.
 *     sum:  This array initially contains garbage values. Its entries
 *         should be set to 1s and 0s to represent the binary value x+y.
 *     num_bits: The size of the arrays.
 *
 * RETURNS: The carry out from the most-significant bit.
 *
 * NOTE: As we've seen in the stack diagram exercises, C doesn't play nice with
 * returning arrays from a function, but functions can modify arrays that are
 * passed in. When implementing this function, you should think of the
 * sum array as the return value. Make sure that by the end of the
 * function this array holds a correct binary representation of the sum x+y.
 */
int add_binary(int x[], int y[], int sum[], int carry_in, int num_bits){
  //if carry_in is 1, then subtract;
  //if carry_in is 0, then add;
  int tally = carry_in;
  //tally counts carry in for each number
  for(int n=num_bits-1;n>=0;n--) {
    int tot = x[n] + y[n] + tally;
    if (tot==0) {
      sum[n] = 0;
      tally = 0;
    } else if (tot==1) {
      sum[n] = 1;
      tally = 0;
    } else if (tot==2) {
      sum[n] =0;
      tally = 1;
    } else if (tot==3) {
      sum[n] = 1;
      tally = 1;
    }
  }

  return tally;
}

/* Flips the bits of a binary number.
 *
 * ARGUMENTS:
 * bits: An array of ones and zeros.
 * num_bits: t else {he size of the array.
 *
 * Returns: No return value, but the elements of bits[] are modified:
 *     1-->0 and 0-->1.
 */
void flip_bits(int bits[], int num_bits){
  for(int n=num_bits-1;n>=0;n--) {
    if (bits[n]==1) {
      bits[n] = 0;
    } else if (bits[n]==0){
      bits[n] =1;
    }

  }

}

/* Checks whether signed overflow has occurred in an addition/subtraction.
 * ARGUMENTS: x, y, sum from add_binary.
 * RETURNS: 1 if there was signed overflow; 0 otherwise.
 * NOTE: You are not given the carries, so you'll have to inspect the
 *       most-significa  if(carry_in==1){nt bit.
 */
int signed_overflow(int x[], int y[], int sum[]){
  if (x[0]==y[0]) {
    if (x[0]==sum[0]) {
      return 0;
    } else {
      return 1;
    }
  } else {
    return 0;
  }
}

/* Checks whether unsigned overflow has occurred in an addition/subtraction.
 * ARGUMENTS: carry_in and carry_out add_binary.
 * RETURNS: 1 if there was unsigned overflow; 0 otherwise.
 * NOTE: You are not given the operands, so you'll have to use the carries.
 */
int unsigned_overflow(int carry_in, int carry_out){
  if (carry_in==carry_out) {
    return 0;
  } else {
    return 1;
  }
}
