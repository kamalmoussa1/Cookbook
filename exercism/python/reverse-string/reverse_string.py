# without built-in functions
def reverse(input=''):
    r_input = ''
    size = len(input)
    
    for i in range(0,size):
        r_i = size -1 -i 
        r_input += input[r_i]   

    return r_input

# using built-in reversed()
def reverse1(input=''):
    r_input = ''
    for l in reversed(input):
        r_input += l
    
    return r_input


# using extended slices 
def reverse2(input=''):
    return input[::-1]
