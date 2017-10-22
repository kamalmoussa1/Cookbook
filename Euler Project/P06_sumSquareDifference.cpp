/*
    Problem 6: 
    Find the difference between the sum of the squares of the first
     one hundred natural numbers and the square of the sum.

    skills:
        - loops
        - <math> lib
        - functions
*/

#include <iostream>
#include <cmath>

int calc_sqd(int n); // function declaration

int main()
{
    int diff = calc_sqd(100);
    std::cout << diff << std::endl;
}

// function definition 
int calc_sqd(int n)
{
    int square_of_sum;
    int sum_of_square = 0;
    int sumofN        = 0;

    // sum of squares of first N natural numbers
    for(int i = 1; i <= n; i++)
    {
        sum_of_square += i*i;
        sumofN += i;
    }

    // square of sum of first N natural numbers
    square_of_sum = pow(sumofN,2);   // make use of <cmath> lib 

    return square_of_sum -  sum_of_square;  // return the difference 

}