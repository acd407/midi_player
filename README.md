## A simple sheet music player ( for program learning )

using Win32 midi api, play a kind of score .

### dependence

- A C++ compiler, such as `g++`, `clang++`, `msvc`

- win32 midi lib: `winmm`

- `fmtlib`

### bulid

I use win32 api, so only windows is support.

if you use MSYS/MSYS2/Cygwin or any other subsystem that can use bash, <br>
you can just use `./build.sh` to build the executable file.

if you use Visual Studio, you can create a new project and add source files by yourself. <br>
May be i will add vs prj file one day.

### directory & files

`/src` the source

`/include` include files dir

`/demo` the demo scores, you can also learn score rules there.

`/*.sh` several shell scripts that can compile files.

### others

this library is aimed at improve programing skills, <br> 
so i wrote several shell scripts instead of using makefile. the functions are:

- compile (needless to say), link libs, add include & lib dir

- skip the source when the modified time is newer than the object file

- clean object files

- demo



this lib is aimed to learn, the target is written in `/TODO`.

if you have better ideas, thanks for your issues.

my email address: mathtimes@foxmail.com




