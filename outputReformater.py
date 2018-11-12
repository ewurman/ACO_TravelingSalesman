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

    this = input("helo")
    for j in range(4):
        filename = "/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/OutputFiles/" + allfiles[j]
        title = allfiles[j][3:-4]
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
                this = input("hello")
                ind = np.arange(len(plotcount))
                width = 0.35
            if j % 2 == 0 :
                fig, ax = plt.subplots()
                print(ind)
                print(counts)
                rects1 = ax.bar(ind, plotcount, width, color='r')
                for i in range(len(rects1)):
                    height = rects1[i].get_height()
                    ax.text(rects1[i].get_x() + rects1[i].get_width()/2., 1.05*height,
                            '%d' % timelabel[i],
                            ha='center', va='bottom')
            else:
                rects2 = ax.bar(ind+width, plotcount, width, color='b')
                
                for i in range(len(rects2)):
                    height = rects2[i].get_height()
                    ax.text(rects2[i].get_x() + rects2[i].get_width()/2., 1.05*height,
                            '%d' % timelabel[i],
                            ha='center', va='bottom')
                
                
                ax.set_ylabel('Scores')
                ax.set_title('Distribution of Tour Termination, and Time Taken to Achieve Optimality of ' + title + ' Cities')
                ax.set_xticks(ind + width / 2)
                ax.set_xticklabels(('1.4' ,'1.35' ,'1.325' ,'1.30' ,'1.275' ,'1.25' ,'1.225' ,'1.20' ,'1.175' ,'1.15' ,'1.125' ,'1.10' ,'1.075' ,'1.05' ,'1.025', '1.0' ))
                ax.legend((rects1[0], rects2[0]), ('ACS','EAS'))
                plt.show()
            i+=1
        
            



                



    
    
    
    
    
    print("Ending the file")

__main__()
