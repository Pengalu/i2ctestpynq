## IIC Test for Pynq Board TU/e

This repository contains code for a master and slave device to demonstrate reading and writing to registers from the master board. It is to be run using two connected PYNQ boards using the PMOD pins. This is a demonstration for the Communications Submodule of the TU/e 5EWC0 Communication Challenge

Please compile this on a PYNQ board! It will not compile on a laptop / other machine without LibPynq installed!

The LibPynq library is included but must be installed on target PYNQ board using cmake install inside the libpynq-5EWC0-# directory. 

Initialize the slave and master code on different PYNQ boards!