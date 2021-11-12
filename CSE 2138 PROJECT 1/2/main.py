import re #For getting split string by 2 not calculation for visual interface

def _controlGiven(given):
    if (len(given) > 8) : #To check if given number bigger than 4 byte 2^2
        print("Please use 4 byte your input bigger than 4 byte")
    else:
        for key in given: # Check if given hex is correct no alpha no integer - integers and small chars not allowed
            if((key.isalpha() and str(key) <= 'F') or (key.isdigit() and int(key) <= 9)):
                continue
            else:
                return 0
        return 1

def _getDecDigit(digit): #Returns decimal number of given hex char
    digits = ['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F']
    for x in range(len(digits)):
        if digit == digits[x]:
            return x
def _getDecimal(hexNum): #Works with getDecDigit to return true decimal
    decNum = 0
    power = 0
    for digit in range(len(hexNum), 0, -1):
        decNum = decNum + 16 ** power * _getDecDigit(hexNum[digit-1])
        power += 1
    return decNum
def _getBinDecimal(binNum):
    sum = 0
    for i in reversed(range(len(binNum))):
        sum += (int(binNum[len(binNum)-i-1]) * int(2**i))
    return sum
def _getMantissa(sign,fraction):
    sum = sign
    g=1
    for i in fraction:
        sum += int(i)*(1/(2**g))
        g += 1
    return sum
def _getRound(fraction):
    fraction = list(fraction)
    sum = list()
    last=0
    if(fraction[12] == '0'):
        if(fraction[13] == '0'):
            last = 0
        else:
            for i in range(13,len(fraction)):
                if(fraction[i] == '1'):
                    last = 1
                    break

    elif(fraction[13] == '0'):
        last = 0
    elif(fraction[13] == '1'):
        for i in range(13,len(fraction)):
            if(fraction[i] == '1'):
                last = 1
                break
    else:
        last = 0
    for i in range (13):
        sum.append(fraction[i])
    sum[12] = last
    return sum

def floatingNum(hexNum):
    floating = []
    print("Floating point number is:")
    floating = re.findall('..',hexNum) # To get every 2 bit to show in interface no effect on calculations
    for x in range(len(floating)):
        print (floating[x], end =" ")
    print (", in binary:", end =" ")

    # Code to convert hex to binary 
    n = _getDecimal(hexNum) #Turns Decimal
    bStr = '' 
    while n > 0: # Until decimal become 0 we divide it to 2
        bStr = str(n % 2) + bStr  # To add found binary to end of others
        n =  n >> 1 # Bitwise Right shifting automatic solution I trying to get rid of libraries but manuel n divide by 2**1 is not worked  
    m = str(bStr)
    m = m.zfill(8) 
    res=list(m)
    print (''.join(map(str, res))) 
    return res

def SType(hexNum):
    binary = floatingNum(hexNum) # Gets Binary Number
    
    if (int(binary[0]) == 1 and (len(binary) == 8 or len(binary) == 16 or len(binary) == 32)):
        sum = -1 * int(binary[0]) * int(2**len(binary))
        for i in reversed(range(len(binary))):
            sum += (int(binary[len(binary)-1-i]) * int(2**i))
        print("Decimal from signed 2's complement: ",sum)
    decNum = _getDecimal(hexNum)
    print("Decimal Result: ",str(decNum))

def UType(hexNum):
    binary = floatingNum(hexNum) # Gets Binary Number
    
    decNum = _getDecimal(hexNum)
    print("Decimal Result: ",str(decNum))

def FType(hexNum):
    binary = floatingNum(hexNum) # Gets Binary Number
    sign = 0
    bits = 0
    exponent = ""
    fraction = ""
    roundfraction = ""
    decexpo = 0
    bias = 0
    decimal = 0
    totalBitSize = ((len(hexNum) / 2) * 8)
    if(len(binary) < totalBitSize):
        size = int(totalBitSize) - len(binary)
        for i in range(size):
            binary.insert(0,'0')

    if(binary[0] == '0'): # That steps checks for odd bit size if not even adds positive 0 in the beggining
        sign = 0
    else:
        sign = 1
    if(len(binary) == 8): # Checks the bit size if size equals given then devides it exp and fra
        bits = 4
        for i in range(1,5):
            exponent += str(binary[i])
        for i in range(5,len(binary)):
            fraction += str(binary[i])
    elif(len(binary) == 16):
        bits = 6
        for i in range(1,7):
            exponent += str(binary[i])
        for i in range(7,len(binary)):
            fraction += str(binary[i])
    elif(len(binary) == 24):
        bits = 8
        for i in range(1,9):
            exponent += str(binary[i])
        for i in range(9,len(binary)):
            fraction += str(binary[i])
    elif(len(binary) == 32):
        bits = 10
        for i in range(1,11):
            exponent += str(binary[i])
        for i in range(11,len(binary)):
            fraction += str(binary[i])
    
    if(len(fraction) > 13):
        roundfraction = ''.join(map(str, _getRound(fraction)))
    else:
        roundfraction = fraction
    decexpo = _getBinDecimal(exponent)
    print("Sign bit =",sign)
    if(exponent.find('1') != -1):
        print("Exponent =(",exponent,")2 =",decexpo)
        mantissa=_getMantissa(1,roundfraction)
    else:
        print("Exponent =",exponent," -> denormalized number")
        mantissa=_getMantissa(0,roundfraction)
    print("Fraction =",fraction,"-> rounded fraction =",roundfraction)
    bias = (2**(bits-1))-1
    if(exponent.find('1') != -1):
        e = decexpo - bias
    else:
        e = 1 - bias
    if(exponent.find('0') == -1):
        if(roundfraction.find('1') == -1):
            if(sign == 0):
                value = "+infinity"
                print(value)
                return 0
            else:
                value = "-infinity"
                print(value)
                return 0
        else:
            value = "NaN"
            print(value)
            return 0
    elif(exponent.find('1') == -1):
        if(roundfraction.find('1') == -1):
            if(sign == 0):
                value = "+0"
                print(value)
                return 0
            else:
                value = "-0"
                print(value)
                return 0
        else:
            value = ((-1)**sign)*mantissa*(2**e)
    else:
        value = ((-1)**sign)*mantissa*(2**e)
    divide = str(value)
    divide = divide.split('.')
    x = divide[0]
    if(divide[1].find('e') != -1):
        divide = divide[1].split('e')
        y = divide[1]
        z = divide[0]
        if(len(z) > 5):
            z = [z[i:i+5] for i in range(0, len(z), 5)]
        value = x+"."+z[0]+"e"+y
    else:
        z = divide[1]
        if(len(z) > 5):
            z = [z[i:i+5] for i in range(0, len(z), 5)]
        value = x+"."+z[0]
    print(value)


def switch(hexNum):
    while True:
        try:
            value = int(input("Please enter a Data Type 1(F floating integer) | 2(U Unsigned Integer) | 3(S Signed Integer) 0 For re-enter hex:")) #To get integer input for menu
            while True:
                try:
                    if(value == 0):#If 0 return back to begining
                        main()
                    elif(value == 1): #If 1 return to Floting numbers
                        FType(hexNum)
                        break
                    elif(value == 2): #If 2 return to UnSigned numbers
                        UType(hexNum)
                        break
                    elif(value == 3): #If 3 return to Signed numbers
                        SType(hexNum)
                        break
                    else:
                        print('Please enter one of signs above') #If not above catch error
                        break
                except KeyError:
                    print('Please enter one of signs above') #If not above catch key errors
                    break
        except ValueError:
            print("You entered non integer character") #If input not integer except Value errors
            continue
        
def hexToDec(hexNum):
    storage = ""
    success = _controlGiven(hexNum)
    if (success == 1):        
        if(len(hexNum) % 2 > 0): #To store if given number odd check is last value is digit and if it's digit then is it odd or even
            storage = "0"+hexNum
        else:
            storage = hexNum
        switch(storage)
    else:
        print("Only digits and characters from A to F will be accepted as an input")

def main():
    while True:
        hex = input("Please enter a Hex value without 0x sign :")
        hexToDec(hex)

main()