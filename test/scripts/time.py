import os
import sys
import argparse
import time
import csv
import matplotlib

import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as mp
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

SIZES = [801]
NUM_ITER = 10
DEFAULT_THREAD = 4

def run_size_time(rep, thread, iter_num):
    for size in SIZES:
        output = run_code('{} {} {}'.format(str(size), iter_num, thread), rep)
        with open('st.csv', 'a+', newline='') as csvfile:
            spamwriter = csv.writer(csvfile, delimiter=' ',
                                quotechar='|', quoting=csv.QUOTE_MINIMAL)
            spamwriter.writerow([size, thread, output])
        
def plot_size_time(save, src):
    if src is not None:
        if save[-1] != '/':
            data_file = '{}/st.csv'.format(src)
        else:
            data_file = '{}st.csv'.format(src)
        size_time = genfromtxt(data_file, delimiter=' ')
    else:
        size_time = genfromtxt('st.csv', delimiter=' ')
    size_time = np.transpose(size_time)
    mp.figure(3)
    mp.plot(size_time[0], size_time[2])
    mp.xlabel("Dimension Size")
    mp.ylabel("Time (s)")
    mp.title("Computation Time to dimension size")
    if save != None:
        matplotlib.use("pgf")
        matplotlib.rcParams.update({
            "pgf.texsystem": "pdflatex",
            'font.family': 'serif',
            'text.usetex': True,
            'pgf.rcfonts': False,
        })
        if save[-1] != '/':
            mp.savefig('{}/st.pgf'.format(save))
        else:
            mp.savefig('{}st.pgf'.format(save))
    else:
        mp.show()


def run_size_threads_time(rep, iter_num):
    threads = [4, 8, 16, 32, 64, 128, 256]
    for size in SIZES:
        for thread in threads:
            output = run_code('{} {} {}'.format(str(size), iter_num, thread), rep)
            with open('stt.csv', 'a+', newline='') as csvfile:
                spamwriter = csv.writer(csvfile, delimiter=' ',
                        quotechar='|', quoting=csv.QUOTE_MINIMAL)
                spamwriter.writerow([size, thread, output])

def plot_size_threads_time(save, src):
    if src is not None:
        if save[-1] != '/':
            data_file = '{}/stt.csv'.format(src)
        else:
            data_file = '{}stt.csv'.format(src)
        data = genfromtxt(data_file, delimiter=' ')
    else:
        data = genfromtxt('stt.csv', delimiter=' ')
    data = np.transpose(data)

    fig = mp.figure()
    ax = fig.gca(projection='3d')
    ax.view_init(30, 130)
    ax.set_xlabel("Dimension Size")
    ax.set_ylabel("Threads")
    ax.set_zlabel("Time (s)")
    ax.set_title("Overall Speed Analysis")
    surf = ax.plot_trisurf(data[0], data[1], data[2], cmap=cm.jet, linewidth=0.1)
    # fig.colorbar(surf, shrink=0.5, aspect=5)
    if save != None:
        matplotlib.use("pgf")
        matplotlib.rcParams.update({
            "pgf.texsystem": "pdflatex",
            'font.family': 'serif',
            'text.usetex': True,
            'pgf.rcfonts': False,
        })
        if save[-1] != '/':
            mp.savefig('{}/stt.pgf'.format(save))
        else:
            mp.savefig('{}stt.pgf'.format(save))
    else:
        mp.show()

def run_threads_time(size, rep, iter_num):
    threads = [1, 2, 4, 8, 16, 32, 64, 128, 256]
    for thread in threads:
        output = run_code('{} {} {}'.format(str(size), iter_num, thread), rep)
        with open('tt.csv', 'a+', newline='') as csvfile:
            spamwriter = csv.writer(csvfile, delimiter=' ',
                            quotechar='|', quoting=csv.QUOTE_MINIMAL)
            spamwriter.writerow([size, thread, output])

def plot_threads_time(save, src):
    if src is not None:
        if save[-1] != '/':
            data_file = '{}/tt.csv'.format(src)
        else:
            data_file = '{}tt.csv'.format(src)
        threads_time = genfromtxt(data_file, delimiter=' ')
    else:
        threads_time = genfromtxt('tt.csv', delimiter=' ')
    threads_time = np.transpose(threads_time)

    if save != None:
        matplotlib.use("pgf")
        matplotlib.rcParams.update({
            "pgf.texsystem": "pdflatex",
            'font.family': 'serif',
            'text.usetex': True,
            'pgf.rcfonts': False,
        })
    mp.figure(2)
    mp.plot(threads_time[1], threads_time[2])
    mp.xlabel("Thread Number")
    mp.ylabel("Time (s)")
    mp.title("Computation Time to Thread Number N=501, 100 iterations")
    if save != None:
        if save[-1] != '/':
            mp.savefig('{}/tt.pgf'.format(save))
        else:
            mp.savefig('{}tt.pgf'.format(save))
    else:
        mp.show()

def run_code(args, rep):
    start_time = time.time()
    for _ in range(rep):
        os.system("./timed_test "+args)
    outtime = (time.time() - start_time) / float(rep)
    return outtime


def main():
    parser = argparse.ArgumentParser(description='Time testing Utility for ENCE464')
    parser.add_argument("--size", action="store", help="Size of array (for threads to time)")
    parser.add_argument("--reps", action="store", help="Number of repetitions for each run, defult 10")
    parser.add_argument("--thread", action="store", help="Number of threads (for size to time), default 4")

    parser.add_argument("--iter", action="store", help="Number of iters, default 10")

    parser.add_argument("--data", action="store", help="Folder containing simulated data")
    parser.add_argument("--save", action="store", help="Save the Plot as a PGF, give the save location")

    parser.add_argument("--plot", action="store_true", help="Run the appropriate plotting function")
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

    if (args.tt == True and not args.plot):
        if (args.size == None):
            parser.print_help()
            exit(1)

    if args.tt == True:
        if (args.plot == True):
            plot_threads_time(args.save, args.data)
        else:
            run_threads_time(args.size, rep, iter_num)
    
    if args.st == True:
        if (args.plot == True):
            plot_size_time(args.save, args.data)
        else:
            run_size_time(rep, thread, iter_num)
    
    if args.stt == True:
        if (args.plot == True):
            plot_size_threads_time(args.save, args.data)
        else:
            run_size_threads_time(rep, iter_num)

if __name__ == "__main__":
    main()