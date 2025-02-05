# Welcome to WCSim

WCSim is a very flexible GEANT4 based program for developing and
simulating large water Cherenkov detectors.

As of August 2014 WCSim has been moved to GitHub.  It can be found at:

https://github.com/WCSim/WCSim

Tutorials and information about the branches and WCSim development model can be
found on the wiki:

https://github.com/WCSim/WCSim/wiki

WCSim has very few external dependencies.  It relies on only ROOT and Geant4.

There is a mailing list which will send you GitHub push/checkin
notifications here:

https://lists.phy.duke.edu/mailman/listinfo/wcsim-git

You can follow issues/requests etc by watching the GitHub respository.

## Validation Webpage

WCSim uses Travis CI to perform build and physics tests for each pull request and commit.
The scripts it runs can be found at https://github.com/WCSim/Validation

The output can be found at: https://wcsim.github.io/Validation/

## Documentation

More detailed information about the simulation is available in
`doc/DetectorDocumentation.pdf`

Additionally, doxygen documentation is available at https://wcsim.github.io/WCSim/inherits.html

## Current notes and how to build

You should have a recent and working version of ROOT and GEANT4.
(Known to work with GEANT 4.10.1p03 and ROOT v5.28.00)  You also need all of the G4
data files including hadron xsecs etc.  Those are the only
requirements.  The code should work with gcc 4.4.7. For v1.6.0 and earlier, use GEANT 4.9.4.p01.

### Build Instructions using make:

To compile: 
* `make clean`
* `make rootcint`
* `make`

If you want to use these libraries with an external program then also do:
* `make shared`      [ For root programs]
* `make libWCSim.a`  [ Also necessary for the event display?]

### Build Instructions using CMake:

CMake is cross-platform software for managing the build process in 
a compiler-independent way (cmake.org).
**Cmake 3.1+ is required.**
It is recommended to build ROOT and GEANT4 also through CMake. The 
latter is very CMake friendly since GEANT 4.9.6, while it started introducing
builds through CMake from 4.9.4 onwards (http://geant4.web.cern.ch/geant4/support/ReleaseNotes4.9.4.html#10.).
Using cmake, builds and source code need to well separated and make
it easier to build many versions of the same software.

A recommended way to set up the directory structure in your own
preferred `WCSIM_HOME`:
- `${WCSIM_HOME}/WCSim` : contains the src dir, typically the cloned or 
  unzipped code from GitHub
- `${WCSIM_HOME}/WCSim_build` : contains directories for each build, eg.
   for each branch you want to test or for different releases, comparing
  debugged versions, etc.
  Each subdirectory like `WCSim_dev` or `WCSim_v1.2` would contain the intermediate files produced
  during compilation and not the finale ones
- `${WCSIM_HOME}/WCSim_install` : contains directories for each build, eg.
  for each branch you want to test or for different releases, comparing
  debugged versions, etc.
  Each subdirectory like `WCSim_dev` or `WCSim_v1.2` will contain the final executable and libraries, 
  the example macros and library for ROOT.

To compile you need to have `CMakeLists.txt` in the WCSim source dir.
* `mkdir -p ${WCSIM_HOME}/WCSim_build/WCSim_dev ; cd ${WCSIM_HOME}/WCSim_build/WCSim_dev`
* Set up the Geant4_Dir: `export Geant4_DIR=${HOME}/Geant4/install/geant4.9.6.p04`
  (from the make install phase of Geant4). Alternatively, source the `geant4.sh` setup script 
located under e.g. `${HOME}/Geant4/install/geant4.9.6.p04/bin`.
* `cmake3 ../../WCSim` : this executes the commands in `CMakeLists.txt` and generates
  the Makefiles for both the ROOT library as the main executable (for some OS, `cmake3` is just `cmake`).
* `make clean` : if necessary
* `make -j3 install` : will first compile the libWCSimRoot.so and libWCSimCore.so which you need for using
 the ROOT Dict from WCSim and then compile WCSim.

To recompile:
* Typically just `make install` will be enough and also redo the cmake phase if
  something changed.
* Sometimes you need to `make clean` first.
* When there are problems, try removing `CMakeCache.txt`, and redo the cmake.

Useful cmake commands:
* `make edit_cache` : customize the build.
* `make rebuild_cache` : redo the cmake phase.


### Using WCSim without building using Docker:

Docker allows you to use WCSim without compiling in an OS independant way. The Docker images are hosted on DockerHub and can be used by following the steps below.

1) Install Docker cross platform instructions can be found at https://www.docker.com/
2) Pull the WCSim image from docker hub by using `docker pull wcsim/wcsim:tag` where `tag` is the tagged version or use the tag `latest` to get the current develop branch 
3) Run the docker image and create a container `docker run --name=WCSim -i -t wcsim/wcsim:tag` this will give you a shell in the container's OS with WCSim already built. 
To save data from inside your docker image mount a local folder in the docker image at runtime and then anything placed in that directory will be available in that folder after exit. To do that run the following `docker run -v local_folder_path:docker_mount_path -i -t wcsim/wcsim:tag`
4) Once you have run the docker image, you will already be in `$WCSIMDIR` and WCSim (and prerequisites) will be setup. Therefore, you can just start running WCSim as normal from this directory
5) To exit the docker image `exit`

(Note: You only need to use the `docker run` command once to create the container. Once created you changes are saved in that container instance and you can start and stop the contianer at any time with  `docker start WCSim` and `docker stop WCSim`);

Extra docker commands:
1) See all images `docker images`
2) Delete an image `docker rmi imageID`
3) See all containers `docker ps -a`
4) Delete a container `docker rm ContainerID`

#### Using WCSim without building using Singularity

Singularity is a similar container tool with different philosphies. The most important being that you can't run as root. This means that it may be installed and available to use on your local cluster.

You should be able to run the docker container with singularity without any problems. Just to note that $WCSIMDIR will be read-only, therefore you should run WCSim elsewhere (if you forget you'll see a nasty seg fault - this is just because of the read-only directory).

## Running WCSim

To test that WCSim is working, try running the test macro `WCSim.mac`, which runs 10 electrons with 500 MeV of energy in the Super-Kamiokande detector. The command is one of the following, depending on how WCSim was built:

`./bin/Linux-g++/WCSim WCSim.mac`

`./exe/bin/Linux-g++/WCSim WCSim.mac`

`WCSim.mac` is well commented. Take a look inside (and also at other `.mac` files in `/macros/`) for the various options you can use to run WCSim

## Color Convention for visualization used in WCSimVismanager.cc

* gamma = green
* neutrino = yellow
* electron = blue
* positron = red
* muon = white
* muon+ = silver
* proton = magenta
* neutron = cyan

```
WCSim development is supported by the United States National Science Foundation.
```
