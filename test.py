import os
import random
import argparse
import subprocess
import graph_plot

SOURCE_CODE_PATH = "./src"

def generateRandomTest(size, filename):
    f = open(filename, "w")
    f.write(str(size) + "\n")
    for i in range(size):
        f.write(str(random.randint(0, 1_000_000)) + " ")
        # f.write(str(i) + " ")
    f.close()

def compileAndRun(compiler, inputSize, times, timeout):
    output = {}
    for file in os.listdir(SOURCE_CODE_PATH):
        if file.endswith(".c"):
            os.system(f"{compiler} -O3 {SOURCE_CODE_PATH}/{file} -o {file[:-2]}.out")
            output[file[:-2]] = []

    for input in inputSize:
        testFileName = f"test{input}.txt"
        generateRandomTest(input, testFileName)
        print("Generated test file with size " + str(input))
        for file in os.listdir("."):
            if file.endswith(".out"):
                avg = 0
                print("Testing " + file)
                t = times
                for i in range(times):
                    try:
                        tmp = subprocess.check_output(f"./{file} {testFileName}".split(), shell=False, timeout=timeout).decode("utf-8")
                        avg += float(tmp)
                    except subprocess.TimeoutExpired:
                        t = 0
                        break
                if t > 0:
                    avg /= t
                    avg *= 1000
                else:
                    avg = None

                output[file[:-4]].append(str(avg))
        os.remove(testFileName)

    for file in os.listdir("."):
            if file.endswith(".out"):
                os.remove(file)
    return output


def main() :
    parser = argparse.ArgumentParser(description='Generate random test and test all file in the directory')
    parser.add_argument('--compiler', type=str, default="gcc", help='Compiler to use')
    parser.add_argument('--times', type=int, default="10", help='Run the test n times')
    parser.add_argument('--timeout', type=float, default="1", help='Timeout for each test')
    parser.add_argument('--inputSize', type=str, default=",".join([str(1_000_000*i) for i in range(1, 11)]), help='Input size for each test, format: 1,2,3,4,5 (comma separated))')
    args = parser.parse_args()

    inputSize = [int(i) for i in args.inputSize.split(",")]
    output = compileAndRun(args.compiler, inputSize, args.times, args.timeout)
    out = open("output.csv", "w")
    out.write("Input size," + ','.join([str(i) for i in inputSize]) + "\n")
    for key in output:
        out.write(key + "," + ','.join(output[key]) + "\n")
    out.close()

if __name__ == "__main__":
    main()
    graph_plot.graph_plot()