# Tracking comparison

This project aims to provide a basic framework to calculate metrics used in visual tracking. It also tries to create a
common interface to trackers and data bases.

For now it provides readers for PascalVOC-like databases and MOT2017 database, currently working on VOT2017 database.

For tracker compatibility I am currently working on STRUCK and plan to include all OpenCV trackers (which will be easy) and Re3 Tracker.

##### Dependency

There is a dependecy on the [Guideline Support Library (GSL)](https://github.com/Microsoft/GSL), to use it you can either copy the files in your project or install it following [these](https://github.com/Microsoft/GSL#using-the-libraries) instructions.

### Building steps

    $ mkdir build && cd build
    $ cmake ..
    $ make -j`nproc`
    $ ./tcomp
