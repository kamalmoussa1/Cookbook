# Euler Project problem 01
# Sum of multiples of 3 and 5 under N

def sum_of(n):

    sum_    = 0

    for i in range(1,n):
        if i%3==0 or i%5==0:
            sum_ += i

    return sum_

print sum_of(1000)
