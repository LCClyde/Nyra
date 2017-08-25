
variable = 9

def multiply(a,b):
    c = 0
    for i in range(0, a):
        c = c + b
    return c
    
class SampleClass:
    def __init__(self):
        self.value = 10;
        
    def multiply_value(self, val):
        self.value = multiply(val, self.value)
        return self.value

