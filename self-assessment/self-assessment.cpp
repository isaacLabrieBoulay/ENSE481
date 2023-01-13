#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/*
Q1. What do you hope to gain from this class?

   I have not done embedded development in a while and I hope to refresh on those competences. The experience I have in this kind of work often involved
   using libraries built by other developpers and I hoped that I could get experience building an application on a target absolutely from scratch. Also, I am
   currently in a DSP class which has no project and I would like to be able to port the knowledge from that class into this project. Coming from a musical
   background, I have a lot of interest in sound processing software. There's a super cool company called Neural DSP which I would love to work for.
   
Q2. What environments have you experience developing in: eg. Unix, Mac, Windows. 
What targets have you worked with: eg. ARM, Microchip, Intel, Freescale? What languages? 
Briefly describe the experience and the tools used.

   I've developped on Unix and Windows systems using Keil uVision, Vim, and Cod::Blocks. I've used a lot of git and I still completely suck at it...
   I've developped for the Cortex M3, CAEN nuclear instrumentation modules, the Texas Instrument MSP430FR5994IPNR, and a tiny bit of Arduino. I programmed in
   C/C++/Python/VHDL. Most of my recent programming has been in the space of data science (machine learning using TensorFlow).


Q3. Describe the largest software system that you have personally built. Any
software/hardware.

   I spent 8 months working at the Canadian Nuclear Laboratories on a Data Acquisition System for a Neutron Interrogation System. I used the MIDAS framework (C & C++)
   to implement a system for controlling pulse discriminating modules, ADCs, and TDCs, using an FPGA I built a pretty basic logic system for the devices, I interacted
   with an event packager, I built an event analyzer, and even (using templates) created a web interface for this system.
*/

//
// Q4
//
// arguments: N/A
// 
// description:
//    Initializes and prints the variable type for Q4.
//
void Q4(void);

//
// Q4f 
//
// arguments:
//    1. arg (float)
//
// description:
//    Dummy function for Q4f
//
bool Q4f(float);

//
// Q5 (whatsit) 
//
// arguments:
//    1. arg (unsigned int): input register value
//
// description:
//    Q5b. I have no idea what this is supposed to do. It seems pretty random
//
unsigned int whatsit(unsigned int); //whatsit()

//
// Q6 (bitSet)
//
// arguments:
//    1. address (unsigned int*): the address of the memory-mapped register
//    2. short unsigned int (bit): bit number in the range [0,31]
//
// description:
//     The function sets the designated bit to 1, without modifying any other bits in
//     the register. For example to set bit 14 of the register at 0x1100FEEC to
//     1 you would call:
//       bitSet(0x1100FEEC, 14);
//
void bitSet(unsigned int *, short unsigned int);

//
// Q7 (search)
//
// arguments:
//    1. a (uint232_t []): an array
//    2. size (uint32_t): number of elements in the array (0, max)
//    3. value (uint32_t): test value
//
// description:
//    Function that searches for a test value in an array. It returns -1 if the value is not 
//    present or returns the array index. This search algorithm needs to have complexity O(logn).
//    Binary Search seems to be the only one.
//
int search(uint32_t [], uint32_t, uint32_t);

// program to compute Q4 to Q7
int main() {

   // Q4
   printf("Question 4\n");
   Q4();
   printf("\n");

   // Q5
   printf("Question 5\n");
   unsigned int test_vals[] = {2, 5, 15, 504};

   for (int i = 0; i < 4; i++){
      unsigned int arg = test_vals[i];
      unsigned int result = whatsit(arg);
      printf("input: %X\n", arg);
      printf("output: %X\n", result);
   }
   printf("\n");

   // Q6
   printf("Question 6\n");
   unsigned int a = 0;
   unsigned int* ptr = &a; //originally a is 0
   printf("value before bitSet = %X\n", a);
   bitSet(ptr, 14);
   printf("\n");

   // Q7
   printf("Question 7\n");
   int val = 1;
   uint32_t arr[] = {1,3,4,5,9,10,34,35};
   int length = sizeof(arr)/sizeof(arr[0]); // compute size
   int index = search(arr, length, val);
   printf("val is at index %d\n", index);


   return 0;
}

void Q4(void) {
   
   // (a) an unsigned integer
   unsigned int a;
   cout << "(a): " << typeid(a).name() << endl;
   // (b) a pointer to a signed character
   char* ab;
   cout << "(b): " << typeid(ab).name() << endl;
   // (c) an array of 10 unsigned integers
   unsigned int abc[10];
   cout  << "(c): " << typeid(abc).name() << endl;
   // (d) an array of 10 pointers to unsigned characters
   unsigned char* abcd[10];
   cout  << "(d): " << typeid(abcd).name() << endl;
   // (e) a pointer to an array of 10 unsigned integers
   unsigned int array[10];
   unsigned int* abcde;
   cout  << "(e): " << typeid(abcde).name() << endl;
   // (f) a pointer to a function that takes a float as an argument, and returns
   // a boolean.
   bool (*abcdef)(float) = Q4f;
   cout  << "(f): " << typeid(abcdef).name() << endl;
   // (g) a pointer to a volatile unsigned integer
   volatile unsigned int* abcdefg;
   cout  << "(g): " << typeid(abcdefg).name() << endl;
}

bool Q4f(float arg){
   return 1;
}

unsigned int whatsit(unsigned int arg){

   unsigned int result = 0;
   unsigned int i;
   unsigned int x = 0;

   for (i = 0; i < 32; i++){
      //cout << "loop " << i << endl;
      x = result + result;
      result = arg & 1;
      result = result | x;
      //printf("result: %X\n", result);
      arg = arg/2;
   }

   return result;
}

void bitSet(unsigned int *address, short unsigned int bit){

   // value at the address
   unsigned int value = *address;
   // create the mask by shifting by 'bit'
   unsigned int mask = 0x00000001 << bit;
   // OR this bit to the value at address
   *address = value | mask;
   printf("value after bitSet = %X\n",*address);
}

int search(uint32_t a[], uint32_t size, uint32_t value) {
   
   // start the lower bound at 0, and the upper bound at max-1
   int low = 0;
   int high = size-1;
   int mid;
   while (low <= high){
      // find mid point
      int mid = low + (high - low) / 2;
      // mid converges to solution
      if (a[mid] == value)
         return mid;
      // update high and low otherwise
      if (a[mid] < value)
         low = mid + 1;

      else
         high = mid - 1;
   }
   // if loop cant find it, return -1
   return -1;
}
