# Tracking comparison

This project aims to provide a basic framework to calculate metrics used in visual tracking. It also tries to create a
common interface to trackers and data bases.

Provides readers for PascalVOC-like databases and [MOT2017](https://motchallenge.net/) database. Currently working on [VOT2017](http://www.votchallenge.net/vot2017/dataset.html) database.

Includes STRUCK, all OpenCV trackers and Re3 Tracker via ZeroMQ

### USAGE

      ./build/tcomp  {-t <STRUCK|Re3|MIL|KCF|TLD|BOOSTING>|-a} [-d <VOC|MOT
                     |VOT>] --id <string> [-f <int>] [--] [--version] [-h]
                     <path>

   Where: 

      -t <STRUCK|Re3|MIL|KCF|TLD|BOOSTING>
        (OR required)  Tracker to use
            -- OR --
      -a,  --all # Not working yet
        (OR required)  Set this if you want to run the secuence in all the trackers


      -d <VOC|MOT|VOT>,  --DB <VOC|MOT|VOT>
        Data base type to use

      --id <string>
        (required)  Identificator of the track

      -f <int>,  --frameskip <int>
        Number of frames to skip

      --,  --ignore_rest
        Ignores the rest of the labeled arguments following this flag.

      --version
        Displays version information and exits.

      -h,  --help
        Displays usage information and exits.

      <path>
        (required)  Path of the data base to be used


      Tracking comparator


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


