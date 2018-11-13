import sys
import os
import statistics
import matplotlib.pyplot as plt
import numpy as np

#print(sys.argv)

def __main__():
    directory = "/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/OutputFiles"
    print(os.listdir(directory))

    allfiles = []
    for thing in os.listdir(directory):
        if thing.endswith('.csv'):
            allfiles.append(thing)
    allfiles.sort()
    print(allfiles)

    for j in range(8):
        filename = "/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/OutputFiles/" + allfiles[j]
        title = allfiles[j][:4]
        if filename.endswith('.csv'):
            print(filename)
            
            with open(filename, 'r') as f:
                lines = f.readlines()
                timelabel = []
                plotcount = []
                times = [[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
                counts = [[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
                for line in lines[3:]:
                    line = line.split(",")
                    print("line = ", line)
                    
                    for i in range(len(line)-2):
                        cell = line[i]
                        x = cell.split(":")
                        time = float(x[0])
                        count = float(x[1])
                        times[i].append(time)
                        counts[i].append(count)
            
                print("counts = ", counts)
                for i in range(len(line)-2):
                    plotcount.append(statistics.mean(counts[i]))
                    timelabel.append(max(times[i]))
                
                print("plotcount = ", plotcount)
                print(timelabel)
                # this = input("hello")
                ind = np.arange(len(plotcount))
                width = 0.35
            if j % 2 == 0 :
                fig, ax = plt.subplots()
                print(ind)
                print(counts)
                rects1 = ax.bar(ind, plotcount, width, color='r')
                for i in range(len(rects1)):
                    height = rects1[i].get_height()
                    if timelabel[i] != 0 and timelabel[i] != -1:
                        ax.text(rects1[i].get_x() + rects1[i].get_width()/2., 1.001*height,
                            '%d' % timelabel[i],
                            ha='center', va='bottom')
            else:
                rects2 = ax.bar(ind+width, plotcount, width, color='b')
                
                for i in range(len(rects2)):
                    height = rects2[i].get_height()
                    if timelabel[i] != 0 and timelabel[i] != -1:
                        ax.text(rects2[i].get_x() + rects2[i].get_width()/2., 1.001*height,
                            '%d' % timelabel[i],
                            ha='center', va='bottom')
                
                
                ax.set_ylabel('Count of Tours Terminating at Optimality')
                ax.set_title('Distribution of Tour Termination, and Time Taken to Achieve Optimality of ' + title + ' Cities')
                ax.set_xticks(ind + width / 2)
                ax.set_xticklabels(('1.4' ,'1.35' ,'1.325' ,'1.30' ,'1.275' ,'1.25' ,'1.225' ,'1.20' ,'1.175' ,'1.15' ,'1.125' ,'1.10' ,'1.075' ,'1.05' ,'1.025', '1.0' ))
                ax.legend((rects1[0], rects2[0]), ('ACS','EAS'))

#                t = ("This is a really long string that I'd rather have wrapped so that it doesn't go outside of the figure, but if it's long enough it will go off the top or bottom!")
#                plt.text(0.5, -.25, t, horizontalalignment='center', verticalalignment='center', transform=ax.transAxes, wrap=True)
                plt.show()
                this = input("jhbjn")
            j+=1
    this = input("jhbjn")
    print("Ending the file")

__main__()
