# SE2 - Proyecto
Proyecto de la asignatura Sistemas Empotrados (Universidad de Zaragoza) 2014/15.

## Dependencies
* [Linaro Toolchain for Cortex-A](https://wiki.linaro.org/WorkingGroups/ToolChain). More precisely, the little endian hard float version (**arm-linux-gnueabihf**, at least 4.8). Pre-built binaries for Windows and Linux available: [here](http://releases.linaro.org/14.11/components/toolchain/binaries/).

Note: Ubuntu (>10.10), already includes the toolchain. 
```
apt-get install gcc-arm-linux-gnueabihf
```

## Build 

### Ubuntu 
```
make 
```

### Other
```
make -f Makefile_manual_install
```
