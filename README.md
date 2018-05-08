# Tracking comparison

This project aims to provide a basic framework to calculate metrics used in visual tracking. It also tries to create a
common interface to trackers and data bases.

Provides readers for PascalVOC-like databases and [MOT2017](https://motchallenge.net/) database. Currently working on [VOT2017](http://www.votchallenge.net/vot2017/dataset.html) database.

I am currently working on STRUCK and plan to include all OpenCV trackers and Re3 Tracker.

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
