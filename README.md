# RDR2-Photo-Extractor v2.0
A computer app that extracts photos froom Red Dead Redemption 2 and converts them to jpgs. This app runs in the terminal from a native executable that you can run with just a click.

# How To Use It
First you want to locate the file on your desktop. Your RDR2 screenshots/photos will typically be in  ```C:\Users\Your_Username_here\Documents\Rockstar Games\Red Dead Redemption 2\Profiles\Your_Profile\``` and will start with PRDR.

When you run the exe file, you will be asked to choose whether you want to convert a single file or an entire folder. You will then be asked to provide the location of the file/folder. You can use either slashes or backslashes for folder navigation and spaces are accepted, so both ```.\FolderName\FileName``` and ```./FolderName/FileName``` will work. When extracting, the extracted photo will be in the folder of the original file, however I will be working on option to specify an output folder in the future.

For those who don't know how to navigate through the filesystem, ```./``` or ```.\``` means to start at the current folder, and ```../``` or ```..\``` means to go to the parent folder.

Once the app is done, it will tell you and just press enter to close the app. Now you have your RDR2 photos converted to jpg.

# Compiling Yourself
If you want to compile the program yourself, then you are free to do so. I have changed the version of my compiler since MinGW didn't support the g++ version I needed. I am now using [MSYS2](https://www.msys2.org/) to get g++.