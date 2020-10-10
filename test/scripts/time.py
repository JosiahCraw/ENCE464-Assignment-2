import os
import sys
import argparse
import time
import csv

import numpy as np
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as mp
from matplotlib import cm

SIZES = [101, 201, 301, 401, 501, 601, 701, 801]
NUM_ITER = 10
DEFAULT_THREAD = 4

def plot_size_time(rep, thread, iter_num):
    for size in SIZES:
        output = run_code('{} {} {}'.format(str(size), iter_num, thread), rep)
        with open('st.csv', 'a+', newline='') as csvfile:
            spamwriter = csv.writer(csvfile, delimiter=' ',
                                quotechar='|', quoting=csv.QUOTE_MINIMAL)
            spamwriter.writerow([size, thread, output])
        


def plot_size_threads_time(rep, iter_num):
    threads = [1, 2, 4, 8, 16, 32, 64]
    for size in SIZES:
        for thread in threads:
            output = run_code('{} {} {}'.format(str(size), iter_num, thread), rep)
            with open('stt.csv', 'a+', newline='') as csvfile:
                spamwriter = csv.writer(csvfile, delimiter=' ',
                        quotechar='|', quoting=csv.QUOTE_MINIMAL)
                spamwriter.writerow([size, thread, output])


def plot_threads_time(size, rep, iter_num):
    threads = [1, 2, 4, 8, 16, 32, 64]
    for thread in threads:
        output = run_code('{} {} {}'.format(str(size), iter_num, thread), rep)
        with open('tt.csv', 'a+', newline='') as csvfile:
            spamwriter = csv.writer(csvfile, delimiter=' ',
                            quotechar='|', quoting=csv.QUOTE_MINIMAL)
            spamwriter.writerow([size, thread, output])


def run_code(args, rep):
    start_time = time.time()
    for _ in range(rep):
        os.system("./timed_test "+args)
    outtime = (time.time() - start_time) / float(rep)
    return outtime

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Time testing Utility for ENCE464')
    parser.add_argument("--size", action="store", help="Size of array (for threads to time)")
    parser.add_argument("--reps", action="store", help="Number of repetitions for each run, defult 10")
    parser.add_argument("--thread", action="store", help="Number of threads (for size to time), default 4")

    parser.add_argument("--iter", action="store", help="Number of iters, default 10")

    parser.add_argument("--tt", action="store_true", help="Runs the threads to time run")
    parser.add_argument("--st", action="store_true", help="Runs the size to time run")
    parser.add_argument("--stt", action="store_true", help="Runs the threads to size to time run")

    args = parser.parse_args()

    if (args.reps == None):
        rep = 10 
    else:
        rep = int(args.reps)

    if (args.thread == None):
        thread = 4 
    else:
        thread = int(args.thread)

    if (args.iter == None):
        iter_num = 10 
    else:
        iter_num = int(args.iter)

    if (args.tt == True):
        if (args.size == None):
            parser.print_help()
            exit(1)

    if args.tt == True:
        with open('tt.csv', 'w+', newline='') as csvfile:
            pass
        plot_threads_time(args.size, rep, iter_num)
    
    if args.st == True:
        with open('st.csv', 'w+', newline='') as csvfile:
            pass
        plot_size_time(rep, thread, iter_num)
    
    if args.stt == True:
        with open('stt.csv', 'w+', newline='') as csvfile:
            pass
        plot_size_threads_time(rep, iter_num)