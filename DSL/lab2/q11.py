n = int(input("Enter the number:"))
while(n > 0):
    if n%2 == 0:
        print(n," divisible")
    else:
        print(n," not divisible")
    n -= 1
else:
    print("END")