# SortCmp

```usage: test.py [-h] [--compiler COMPILER] [--times TIMES] [--timeout TIMEOUT]
               [--inputSize INPUTSIZE]

Generate random test and test all c file in the ./src directory

options:
  -h, --help            show this help message and exit
  --compiler COMPILER   Compiler to use (default: gcc)
  --times TIMES         Run the test n times for each file and take the
                        average (default: 10)
  --timeout TIMEOUT     Timeout for each test (default: 1)
  --inputSize INPUTSIZE
                        Input size for each test, format: 1,2,3,4,5 (comma
                        separated) (default: 1000000,2000000,3000000,4000000,5
                        000000,6000000,7000000,8000000,9000000,10000000)
```
