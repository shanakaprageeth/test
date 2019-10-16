
import logging

logging.basicConfig(level=logging.ERROR)

def getfuncval(x , a0 =1, a1 = 1, a2 =0, a3= 0):
    y = a0 + a1 * x + a2 * x * x + a3 * x * x * x
    return y

def checkWithinBoundry(val, margin = 0.01):
    if(val >= 0 and val < margin):
        logging.debug("val is {0}:".format(val))
        return True
    if(val < 0 and val > -margin):
        logging.debug("val is {0}:".format(val))
        return True
    return False

# return root or None
def bisection(a,b):
    if (getfuncval(a) * getfuncval(b) > 0): 
        logging.warning("no boundry crossing\n") 
        return None
    if (getfuncval(a) * getfuncval(b) == 0 ):
        if (getfuncval(a) == 0):
            logging.debug("a is {}:".format(a))
            return a
        if (getfuncval(b) == 0):
            logging.debug("b is {}:".format(b))
            return b
    c = a
    while (not checkWithinBoundry(getfuncval(c))): 
        c = (a+b)/2
        if (checkWithinBoundry(getfuncval(c))):
            logging.debug("c is {}:".format(c))
            return c
        if (getfuncval(c)*getfuncval(a) < 0): 
            b = c
        else: 
            a = c
    return c

def guessBoundries(boundry, delta = 10, initialGuess = 0):
    expectedRoots = 1
    positiveVals = []
    negativeVals = []
    roots = []
    tempGuess = initialGuess
    while (expectedRoots > len(roots) and not checkWithinBoundry(tempGuess,boundry)):
        print (tempGuess)
        if ( getfuncval(tempGuess) > 0 ):
            positiveVals.append(tempGuess)
            temp_root = bisection (tempGuess, tempGuess+ delta)
            if (temp_root !=  None):
                roots.append(temp_root)
                negativeVals.append(tempGuess+ delta)
        elif ( getfuncval(tempGuess) < 0 ):
            negativeVals.append(initialGuess)
            temp_root = bisection (tempGuess, initialGuess+ delta)
            if (temp_root !=  None):
                roots.append(temp_root)
                positiveVals.append(tempGuess+ delta)
        else:
            roots.append(tempGuess)
        tempGuess = tempGuess + delta
    return roots

def main():
    a = 10
    b= -10
    final_value = bisection(a, b)
    print( guessBoundries(100) )
    print('final' , bisection(a, b))

if __name__== "__main__" :
    main()
