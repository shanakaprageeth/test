
import logging

logging.basicConfig(level=logging.ERROR)

#please define polynomial here
def getfuncval(x , a0 =-1, a1 = 0, a2 =1, a3= 0):
    y = a0 + a1 * x + a2 * x * x + a3 * x * x * x
    return y

# check whether a number within the a margin
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

def guessUpdate(posCycle, val1, val2):
    if (posCycle):
        return val1+val2
    return val1-val2

# create guessues within the boundary
def guessBoundries(boundry, delta = 10, initialGuess = 0):
    expectedRoots = 2
    positiveVals = []
    negativeVals = []
    roots = []
    tempGuess = initialGuess
    posCycle = 1
    while (expectedRoots > len(roots)):
        if(not checkWithinBoundry(tempGuess,boundry) and posCycle == 0):
            break
        elif(not checkWithinBoundry(tempGuess,boundry) and posCycle == 1):
            posCycle = 0
        if ( getfuncval(tempGuess) > 0 ):
            positiveVals.append(tempGuess)
            temp_root = bisection (tempGuess, guessUpdate(posCycle, tempGuess, delta))
            if (temp_root !=  None):
                roots.append(temp_root)
                negativeVals.append(guessUpdate(posCycle, tempGuess, delta))
        elif ( getfuncval(tempGuess) < 0 ):
            negativeVals.append(tempGuess)
            temp_root = bisection (tempGuess, guessUpdate(posCycle, tempGuess, delta))
            if (temp_root !=  None):
                roots.append(temp_root)
                positiveVals.append(guessUpdate(posCycle, tempGuess, delta))
        else:
            roots.append(tempGuess)
        tempGuess = guessUpdate(posCycle, tempGuess, delta)
    return roots

def main():
    
    print('guessed roots are ',guessBoundries(100) )
    print('roots for your guesses using bisection method are' , bisection(-10, 0))

if __name__== "__main__" :
    main()
