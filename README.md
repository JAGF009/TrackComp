# Tracking comparison

This project aims to provide a basic framework to calculate metrics used in visual tracking. It also tries to create a
common interface to trackers and data bases.

Provides readers for PascalVOC-like databases and [MOT2017](https://motchallenge.net/) database. Currently working on [VOT2017](http://www.votchallenge.net/vot2017/dataset.html) database.

Includes STRUCK, all OpenCV trackers and Re3 Tracker via ZeroMQ

### Dependecies

[ZeroMQ](http://zeromq.org/) to talk with the python process for Re3.

[TCLAP](http://tclap.sourceforge.net/) for command line argument parsing.

### Building steps

    mkdir build && cd build
    cmake ..
    make -j`nproc`
    ./tcomp

If you are working with [fish shell](https://fishshell.com/):
    
    mkdir build; cd build
    cmake ..
    make -j(nproc)
    ./tcomp
