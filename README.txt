IMPORTANT: (Oct 29 2013) This program is still under initial development
and testing. Once it stabalized, I will remove this comment. If you want
to use it before that, feel free to contact me for status.

A Digispark program that performs an external buttom pressing when power
is applied.  See project/project.ino for details.

The project can be compiled and programed to a Digispark board using the
Digispark version of Arduino IDE. For more details see:

* http://digistump.com/products/1

* http://digistump.com/wiki/digispark

---

To program a compiled release (a .hex file) from this repository do:

[For Mac OSX]
1. Copy this repository to your computer (use git, download and 
   unzip, etc) 
2. Do not insert your Digispark to the comptuer yet.
3. In a shell terminal go the 'release' directory of your copy
   of this repository.
4. Identify the compiled release hex file you want to program
5. Type a command like
   ../tools/mac_osx/micronucleus button-minder-20131031-001-beta.hex
   where the second part is the name of the hex file you want to
   program.
4. When prompted, insert the Digispark to one of the your computer's 
   USB ports (make sure the Digispark is not connected to any other
   circuit with voltages that may damage your computer).
5. After 5-15 seconds, you will be prompted that the programming
   is completed. 
6. Remove the Digispark from the computer. Your Digispark is now
   programmed with Button Minder.

[For Windows]
Do the above with the following exceptions:
a. Install the Digispark drivers by unzipping the file
   tools/windows/digispark_windows_driver.zip and running installDriver.ext. 
b. Use the ../tools/windows/micronucleus.exe


An alternative way for programming the Digispark is to setup 
a Digispark Arduino IDE, load the source code from the 'project'
directory of this repository and program to your Digispark.
For more information see http://digistump.com.



