# Utils
> Utils is a compilation of useful, hardware independent, functions, data types, macros and definitions.

## Table of contents
* [General info](#general-info)
* [Screenshots](#screenshots)
* [Technologies](#technologies)
* [Setup](#setup)
* [Features](#features)
* [Status](#status)
* [Inspiration](#inspiration)
* [Contact](#contact)

## General info
This is a compilation of useful functions, data types, macros and definitions. New functionalities can be added so that there is no need to reimplement them for every new project.

## Screenshots
No screenshots available.

## Technologies
The following libs are present in this repository:
* **basic_graphics** - This is a modified version of Adafruit GFX library for Arduino into a code 100% C compatible. It has its own repository and is added as a submodule.
* **control** - A compilation of controller implementations. Up to this date, the only controller implemented is a PID discretized using the bilinear transform (Tustin's method), which means the controller can be designed using continuous time techniques and the controller parameters input directly to the lib.
* **linear_algebra** - A C library with implementations of basic operations with vectors and matrices.
* **std_headers** - Data types, macros and definitions that might be useful in C applications.
* **sys_identification** - Functions useful in modeling systems online using measurement data. Up to this date, only the least mean square (LMS) and recursive mean square algorithms are implemented.
* Other functionalities may be added in the future.

## Setup
The instalation of this lib into a project of any platform is quite simple. You basicaly have four different options for how to add this repository into your project.

### If you are not interested in updates
Just download the repository as a zip file [through this link](https://github.com/passoswell/utils/archive/refs/heads/master.zip), extract the content and move it to the desired folder inside your project. Note that you will have to download the submodules manualy using the same procedure on their respective repositories.

### Adding as a submodule to your git repository
To do that, just open the terminal inside the folder where you have your repository cloned, open the terminal and type:
```
git submodule add git@github.com:passoswell/utils.git
```
You can also specify a destination folder by using instead the following command in the terminal:
```
git submodule add git@github.com:passoswell/utils.git <destination folder>
```
Do not forget to substitute <destination folder> by the path of the folder where you want the submodule installed. For instance, if the folder should be called "common" instead of "utils":
```
git submodule add git@github.com:passoswell/utils.git common
```
Or if it must be stored inside a folder called "external":
```
git submodule add git@github.com:passoswell/utils.git external/utils
```

### Just clonning the repository and all submodules
For that, open the terminal on the desired folder and use the command below:
```
git clone --recurse-submodules git@github.com:passoswell/utils.git
```
This command will download all the submodules.

### Just clonning the repository but some or no submodules
To download the repository without the submodules, just use the command:
```
git clone git@github.com:passoswell/utils.git
```
This way, the submodules are not downloaded. 
To download a specific submodule, open the terminal inside the "utils" folder and use the following command:
```
git submodule update --init <submodule name>
```
Do not forget to substitute <submodule name> by the name of the desired submodule, which coincides with the name of its folder. For instance, to download the basic_graphics submodule, use:
```
git submodule update --init basic_graphics
```

### Adding the libs to your project
This task is dependent on the tools and IDEs used and is not covered by this readme.

## Code Examples
Example codes for most of the modules are available in the "examples" folder. For the git submodules, a "examples" folder is present in their own folder.

## Features
No features are listed.

## Status
Project is: _in progress_. New features will be added with time and necessity.

## Inspiration
This project aspire to compile in one repository features that where used by the author in the past and will become handy in future projects.

The template for this readme file was created by [@flynerdpl](https://www.flynerd.pl/).

## Contact
Created by [@passoswell](https://github.com/passoswell).
