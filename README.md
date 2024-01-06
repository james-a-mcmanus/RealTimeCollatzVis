# Real Time Collatz Graph Display


- Receives data from clientSender_fn.
- Plots it on a graph, rescales as data comes in.
- Runs continuously


# Dependencies
- To build, needs boost and qtmake
- on Ubuntu
	- `sudo apt-get install libboost-all-dev`
	- `sudo apt install -y qtbase5-dev qt5-qmake`


- To build, navigate to the install directory:
	- `mkdir build`
	- `cd build`
 	- `qmake RealTimeCollatzVis.pro`
	- `make`

