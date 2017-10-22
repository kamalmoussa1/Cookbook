'''
Euler Project 
P02     : Even Fibonacci numbers
        By considering the terms in the Fibonacci sequence whose values
        do not exceed four million, find the sum of the even-valued terms.
Data    : 29 - 9 - 2017
'''
	
def calcFib(max): # max sum

    a = 0; b =1; tot = 0; even_sum = 0

    while tot < max:
        tot = a + b
        if tot < max and tot%2 ==0: # even or not 
            even_sum += tot
        a = b; b = tot

    return even_sum
    
print calcFib(4000000)

