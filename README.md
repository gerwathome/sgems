### About
SGeMS is the Stanford Geostatistical Modeling Software.  More information is available on the [SGeMS website](http://sgems.sourceforge.net/). The open source version of the software has not been updated for a number of years, and it has become less transparent as to how it should be compiled using prerequisites available on current machines.  The purpose of this README and of this repository is to ease the process of obtaining and using SGeMS.

This current version of the README file is an edited version of the original readme obtained from the Subversion repository at SourceForge.  In order to allow compilation with currently available libraries in Ubuntu 16.04, a few minor code changes have been made.  Any changes are offered under the original licensing scheme.

Note that this version of SGeMS is 2.5b, which appears to be the latest version available with an open source license.  A more recent version, with somewhat more restricitve licensing, may be found on [GitHub](https://github.com/sayantanx/ar2tech-SGeMS-public).  Commercial development of SGeMS continues under the name AR2GEMS by [Advanced Resources and Risk Technology](http://www.ar2tech.com/).

A windows executable is available for SGeMS 2.5b at the [SGeMS website](http://sgems.sourceforge.net/?q=node/77).  It appears to run fine on an Ubuntu 16.04 machine using the windows compatibility layer [wine](https://www.winehq.org/).  While this is nominally the same version as the souce code in the SourceForge Subversion repository, the source code version has a Debug item in the menu bar.  This may just be an option chosen during compilation.  Comparative testing hasn't yet been undertaken to see if there are other differences.

### The (Mostly) Original README
This rudimentary readme file contains information on how to compile S-GeMS on Unix systems. For Windows systems, only Visual C++ 6 with Intel compiler 7.x or 8.x, or Visual C++ .Net 2003 are currently supported. A workspace file (.dsw/.sln) is available in directory WinGsTLAppli.  Project files (.dsp/.vcproj) are available in each subdirectory of GsTLAppli.

S-GeMS is distributed under two licenses (choose one): the GPL license and the
Xfree license. Copies of these two licenses are in files LICENSE.GPL and 
LICENSE.XFREE.

Note: The name of this software has changed several times, so you might find that it is sometimes called GEMS, Simulacre, or GsTLAppli...

###Compiling
Warning: the compilation process of S-GeMS is not streamlined yet, and might require some manual intervention. Before you try to compile S-GeMS, make sure that you have the following libraries:
- Qt     (www.trolltech.com)
- Coin   (www.coin3d.org)
- SoQt   (www.coin3d.org)
- SimVoleon (www.coin3d.org)
- Python (www.python.org)  
- GsTL   (http://pangea.stanford.edu/~nremy/GTL/GsTL_home.html)

*Earlier versions of Qt and Coin cannot be used in a commercial setting unless you purchase the appropriate license. Current versions of Qt and Coin have been released under open source licenses.*

1. Edit file ".qmake.cache" and modify the path variables. One common mistake when setting the paths in .qmake.cache: the top-level directory of GsTL contains a directory that is also called GsTL and contains the source files. The GSTLHOME variable must be set to the top-level directory, not to the nested GsTL directory. So GSTLHOME=/tmp/GsTL, not /tmp/GsTL/GsTL. Similarily, the top-level directory of SGeMS contains a directory called GsTLAppli. Set GSTLAPPLI_HOME=/tmp/SGeMS, not /tmp/SGeMS/GsTLAppli.
2. If you want to compile in release mode, edit "config.qmake" and
   change line:
      `CONFIG +=  debug warn_on`
   to
      `CONFIG +=  release warn_on`
   (remove "warn_on" to decrease the number of compiler warnings) 
3. Run qmake (just type "qmake") to generate the top-level makefile.
4. Finally, run make.
5. The executable will be output to $GSTLAPPLI_HOME/bin/linux/s-gems. It will probably be necessary to set LD_LIBRARY_PATH so linux can find the sgems shared libraries. These libraries are in $GSTLAPPLI_HOME/lib/linux and $GSTLAPPLI_HOME/plugins/designer:
    export LD_LIBRARY_PATH=$GSTLAPPLI_HOME/lib/linux:$GSTLAPPLI_HOME/plugins/designer
Library $GSTLAPPLI_HOME/plugins/designer/libGsTLwidgets.so is a plug-in for Qt. If Qt can't find that plug-in, parts of the interface will be missing. You can copy libGsTLwidgets.so to $QTDIR/plugins/designer, or use qtconfig to add a new plug-ins search path.
6. Before you run the software, define a variable called GSTLAPPLIHOME to  point to the root directory of S-GeMS .

###Generating Makefiles:

Makefiles are generated using qmake and .pro files. All .pro files should already be there. This part explains how to use shell script "Makemake" to generate the pro files and the corresponding Makefiles.  To generate a makefile:

1. Define in MMakefile any non-default variable. MMakefile can be used to override the target name (TARGET=name), add paths to the include path (INCLUDEPATH += /new/path), etc. See qmake help for all available options.
2. For an executable application run: 
`Makemake -a`
For a library run:
`Makemake -l`
     Makemake will generate a .pro file and the corresponding makefile.     Makemake should be rerun each time new source files are added.  By default Makemake will attempt to compile all the files in the directory. If more than one file contains a main() function, compilation will fail. To remove the extra files, put the following line in MMakefile:
`SOURCES -= extra_file.cpp`
`HEADERS -= extra_file.h`

If your target is an executable, you can also run "make link" to obtain a link to the compiled executable in the current directory (note that the rule for "link" is generated by Makemake, so if you don't use Makemake to generate the makefile, there won't be any "link" rule ).

###Back to the Edited README
 The following sections are alternate approaches. One should choose to install a windows binary, compile from SourceForge, or compile from GitHub.  It is unnecessary to do all three to use SGeMS. 
####Installing Windows Binary on Ubuntu 16.04 From SourceForge

This is not necessary for compiling SGeMS on Ubuntu.  It is only offered at an alternative to someone who wishes to run SGeMS on Ubuntu without the bother of compilation. 

First install wine.  I am using version 1.8, although other versions would probably work.
```bash
sudo apt-get install wine1.8
```
Next download the appropriate binary (32 bits or 64 bits with or without Nvidia) from the [SGeMS website](http://sgems.sourceforge.net/?q=node/77).  To install, either right click and open with wine, or change to the download directory and use the command line:
```bash
wine SGeMS-x64-beta-ar2tech-installer-non-NVIDIA.exe
```
This will bring up a normal windows installer dialog.  Follow the directions as normally done to install a windows program.  To use the installed program, the same right click or command line options used for installation should be used.

####Compilation for Ubuntu 16.04 From SourceForge
This process assumes that you have write permission to the destination where the repositories will be checked out.  I am placing the files in /usr/local/src.  Even using sudo, checking out a subversion repository tends to have problems with subdirectories, so I have made the src directory writable to the adm group, and added myself to that group.  This approach allows the compilation process to proceed without repeated use of sudo, but still requires sudo to install the libraries and executables in the /usr/local directory structure.  An alternate approach would be to place the repos in your home directory.
```bash
sudo chgrp -R adm /usr/local/src
sudo chmod g+w /usr/local/src
sudo adduser <username> adm
```
First we add the necessary prerequisite libraries and include files available from the Ubuntu repositories.
```bash
sudo apt-get install libqt4-dev libsoqt4-dev \
libboost1.58-dev python2.7-dev libcoin80v5 \
build-essential subversion cvs mercurial git
```
Unfortunately, there is no Debian/Ubuntu package for SIMVoleon.  It will need to be obtained from the repository, and compiled locally.  This installs the SIMVoleon library in /usr/local/lib.
```bash
cd /usr/local/src
hg clone https://bitbucket.org/Coin3D/simvoleon 
cd simvoleon
./configure --prefix=/usr/local
make
sudo make install
```
The current version of GsTL now in SourceForge no longer includes the boost libraries, and has the the problematic include paths corrected, so the [original instructions](http://imgp.nbi.dk/compile_sgems.php/)  to fix these problems are not necessary.  GsTL is a template library, and doesn't need to be compiled.  It needs to be placed in a location where it can be found.  This procedure will install the library in /usr/local/include.  The location may be changed by modifying the PREFIX variable.  If the installation directory is changed, then it will also be necessary to change the GSTLHOME variable in the sgems .qmake.cache file.
```bash
cd /usr/local/src
cvs -z3 -d:pserver:anonymous@a.cvs.sourceforge.net:/cvsroot/gstl co -d GsTL-cvs -P GsTL
cd  ./GsTL-cvs
echo 'PREFIX = /usr/local' > Makefile
echo 'GSTL = ./GsTL' >> Makefile
echo 'install: force' >> Makefile
echo '\tcp -R -p -f ${GSTL} ${PREFIX}/include' >> Makefile
echo force : >> Makefile
sudo make install
```
Now we obtain SGeMS from SourceForge, and edit the paths in .qmake.cache, as described in the original README. 
```bash
cd /usr/local/src
svn checkout https://svn.code.sf.net/p/sgems/svn/trunk sgems-svn
cd sgems-svn
sed -i '/^GSTLHOME/s/^.\+$/GSTLHOME = \/usr\/local\/include/' .qmake.cache
sed -i '/^GSTLAPPLI_HOME/s/^.\+$/GSTLAPPLI_HOME = \/usr\/local\/src\/sgems-svn/' .qmake.cache
sed -i '/^INVENTOR_LIB/s/^.\+$/INVENTOR_LIB = \/usr\/lib\/x86_64-linux-gnu/' .qmake.cache
sed -i '/^INVENTOR_INCLUDE/s/^.\+$/INVENTOR_INCLUDE = \/usr\/include\/Inventor/' .qmake.cache
sed -i '/^BOOST_INCLUDE/s/^.\+$/BOOST_INCLUDE = \/usr\/include\/boost/' .qmake.cache
sed -i '/^PYTHON_LIB/s/^.\+$/PYTHON_LIB = \/usr\/lib\/x86_64-linux-gnu/' .qmake.cache
sed -i '/^PYTHON_INCLUDE/s/^.\+$/PYTHON_INCLUDE = \/usr\/include\/python2.7/' .qmake.cache
sed -i '/^PYTHON_SO/s/^.\+$/PYTHON_SO = python2.7/' .qmake.cache
sed -i '/^CUR_PLATFORM/s/^.\+$/CUR_PLATFORM = linux/' .qmake.cache
```
After several tries at compiling SGeMS, it became clear that a few minor modifications were necessary.  First the permissive compiler flag had to be set, because the compiler was uncomfortable with the scope of some of the variable definitions.  Second, one function definition had to be moved after the one immediately following it, because the compiler had trouble finding the second function.
```bash
cd /usr/local/src/sgems-svn
sed -i '/warn_on/a QMAKE_CXX += -fpermissive' config.qmake
# explanation of following sed foo
# 1. get rid of the carriage returns in the original file
# 2. put the function to be moved (378-411) into the hold buffer
# 3. switch the contents of the hold buffer into the pattern buffer at line 427, so that it will be printed
sed -i 's/\r//;378,411 {H;d};427 x' /usr/local/src/sgems-svn/GsTLAppli/geostat/utilities.h
```
Now SGeMs may be compiled.  We will also create a script to launch sgems, and place it in /usr/local/bin.  If the SGeMS subversion repository was not placed in /usr/local/src, then the PREFIX variable in the run script will need to be changed.
```bash
cd /usr/local/src/sgems-svn
qmake
make
# in csh the '!" needs to be escaped; remove '\' in bash
echo '#\!/bin/sh' > run_sgems
echo 'PREFIX = /usr/local/src/' >> run_sgems
echo 'GSTLAPPLIHOME=${PREFIX}sgems-svn/' >> run_sgems
echo 'export GSTLAPPLIHOME' >> run_sgems
echo 'SGBIN=${GSTLAPPLIHOME}bin/linux/' >> run_sgems
echo 'SGLIB=${GSTLAPPLIHOME}lib/linux/' >> run_sgems
echo 'PILIB=${GSTLAPPLIHOME}plugins/designer/' >> run_sgems
echo 'PATH=$PATH:$SGBIN' >> run_sgems
echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SGLIB:$PILIB' >> run_sgems
echo '${SGEMS_BIN}sgems &>/dev/null &' >> run_sgems
chmod ugo+x run_sgems 
sudo mv run_sgems /usr/local/bin/.
```
#### Conversion to Git
Now we will convert the GsTL and SGeMS repositories to git, and upload them to GitHub.  A longer term goal would be to create an Ubuntu PPA for easy sharing of SGeMS.  The previous edits of the SourceForge repos will be done, and committed to the git repository.

First GsTL:
```bash
cd /usr/local/src
git cvsimport -d:pserver:anonymous@a.cvs.sourceforge.net:/cvsroot/gstl -C GsTL GsTL
cd  ./GsTL
echo 'PREFIX = /usr/local' > Makefile
echo 'GSTL = ./GsTL' >> Makefile
echo 'install: force' >> Makefile
echo '\tcp -R -p -f ${GSTL} ${PREFIX}/include' >> Makefile
echo force : >> Makefile
git add Makefile
git commit -m "added a Makefile to install GsTL for a linux machine"
```
Next SGeMS:
```bash
echo 'nico97492 = Nicolas Remy <nremy@pangea.stanford.edu>' > /tmp/users.txt
echo 'aboucher =  Alexandre Boucher <aboucher@ar2tech.com>' >> /tmp/users.txt
echo 'rgupta82 = Rahul Gupta <unknown@somewhere.com>' >> /tmp/users.txt
echo 'Rahul Gupta = Rahul Gupta <unknown@somewhere.com>' >> /tmp/users.txt
cd /usr/local/src/
git svn clone  https://svn.code.sf.net/p/sgems/svn/trunk sgems --authors-file=/tmp/users.txt --no-metadata --prefix ""
cd sgems
sed -i '/^GSTLHOME/s/^.\+$/GSTLHOME = \/usr\/local\/include/' .qmake.cache
sed -i '/^GSTLAPPLI_HOME/s/^.\+$/GSTLAPPLI_HOME = \/usr\/local\/src\/sgems-svn/' .qmake.cache
sed -i '/^INVENTOR_LIB/s/^.\+$/INVENTOR_LIB = \/usr\/lib\/x86_64-linux-gnu/' .qmake.cache
sed -i '/^INVENTOR_INCLUDE/s/^.\+$/INVENTOR_INCLUDE = \/usr\/include\/Inventor/' .qmake.cache
sed -i '/^BOOST_INCLUDE/s/^.\+$/BOOST_INCLUDE = \/usr\/include\/boost/' .qmake.cache
sed -i '/^PYTHON_LIB/s/^.\+$/PYTHON_LIB = \/usr\/lib\/x86_64-linux-gnu/' .qmake.cache
sed -i '/^PYTHON_INCLUDE/s/^.\+$/PYTHON_INCLUDE = \/usr\/include\/python2.7/' .qmake.cache
sed -i '/^PYTHON_SO/s/^.\+$/PYTHON_SO = python2.7/' .qmake.cache
sed -i '/^CUR_PLATFORM/s/^.\+$/CUR_PLATFORM = linux/' .qmake.cache
sed -i '/warn_on/a QMAKE_CXX += -fpermissive' config.qmake
sed -i 's/\r//;378,411 {H;d};427 x' ./GsTLAppli/geostat/utilities.h
# in csh the '!" needs to be escaped; remove '\' in bash
echo '#\!/bin/sh' > run_sgems
echo 'PREFIX=/usr/local/src/' >> run_sgems
echo 'GSTLAPPLIHOME=${PREFIX}sgems/' >> run_sgems
echo 'export GSTLAPPLIHOME' >> run_sgems
echo 'SGBIN=${GSTLAPPLIHOME}bin/linux/' >> run_sgems
echo 'SGLIB=${GSTLAPPLIHOME}lib/linux/' >> run_sgems
echo 'PILIB=${GSTLAPPLIHOME}plugins/designer/' >> run_sgems
echo 'PATH=$PATH:$SGBIN' >> run_sgems
echo 'LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SGLIB:$PILIB' >> run_sgems
echo '${SGEMS_BIN}sgems &>/dev/null &' >> run_sgems
chmod ugo+x run_sgems 

git add .qmake.cache config.qmake ./GsTLAppli/geostat/utilities.h run_sgems
git commit -m 'modify to allow compilation on Ubuntu 16.04 and create a run script'
```

####Compilation for Ubuntu 16.04 Using this GitHub Repository
This process is very similar to the process described above for downloads from SourceForge, except that the necessary edits have already been made.  Again we assume that you have write permission to the destination where the repositories will be checked out.  I am placing the files in /usr/local/src and have made the src directory writable to the adm group, and added myself to that group.  An alternate approach would be to place the repos in your home directory.
```bash
sudo chgrp -R adm /usr/local/src
sudo chmod g+w /usr/local/src
sudo adduser <username> adm
```
First we add the libraries and include files available from the Ubuntu repositories.
```bash
sudo apt-get install libqt4-dev libsoqt4-dev \
libboost1.58-dev python2.7-dev libcoin80v5 \
build-essential subversion cvs mercurial git
```
Unfortunately, there is no Debian/Ubuntu package for SIMVoleon.  It will need to be obtained from the repository, and compiled locally.  This installs the SIMVoleon library in /usr/local/lib.
```bash
cd /usr/local/src
hg clone https://bitbucket.org/Coin3D/simvoleon 
cd simvoleon
./configure --prefix=/usr/local
make
sudo make install
```
Now get GsTL and SGeMS from GitHub, compile them, and install them.  If alternate choices for install directories are made, then the appropriate scripts will need to be edited.
```bash
cd /usr/local/src/
git clone https://github.com/gerwathome/GsTL
cd GsTL
sudo make install
cd ..
git clone https://github.com/gerwathome/sgems
cd sgems
qmake
make
sudo mv run_sgems /usr/local/bin/.
```
It would be desirable to alter the make process for sgems to allow use of 'sudo make install', but I'm not there, yet.
