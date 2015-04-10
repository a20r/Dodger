Dodger
======

Generating safe trajectories in stochastic dynamic environment by leveraging
information about obstacle motion.

# Install

To make use of the ROS enable features of Dodger, please install ROS Indigo.
Instructions can be found
[here](http://wiki.ros.org/indigo/Installation/Ubuntu). Note that this project
has been tested using Ubuntu 14.04. To build Dodger, see the command line
instructions below.

    $ git clone https://github.com/wallarelvo/Dodger.git && cd Dodger
    $ ./install.sh

# Examples

Scripts are provided to showcase Dodger. To visualize a particular scenario
using Matplotlib, run

    $ scripts/easy_run.sh [name of example]

A number of examples are given in the `examples/` directory. Also, the command
line argument provided to `scripts/easy_run.sh` excludes the `.cpp` extension.
To visualize a particular scenario using RViz run

    $ roslaunch config/tf.launch &
    $ rosrun rviz rviz -d config/config.rviz &
    $ scripts/easy_ros.sh [name of example]

This script has the same constraints for example names as for the Matplotlib
example.
