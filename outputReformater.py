import sys


#print(sys.argv)






def __main__():
    inputFile = sys.argv[1];
    with open(inputFile, 'r') as f:
        lines = f.readlines();
        print(lines);

    benchmarks = [x.split('x')[0] for x in lines[0].split(',')[:-2]];
    print (benchmarks)
    lines = [x for x in lines[1:] if x[0] != "#"];
    print(lines);

    times = [];
    counts = [];
    for line in lines:
        x = line.split(":");
        time = x[0];
        count = x[1];





    print("Ending the file")

__main__()