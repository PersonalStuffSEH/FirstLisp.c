# FirstLisp.c - Brackish
I want to try making a Lisp without any help from AI or tutorials

It's called `Brackish` like the saline water due to the fact that there are brackets
I didn't want to spend hours thinking of a name so I just took that
The file extension is `.brac` although that is really not checked
(You could name it .foo and it would probably still work until I decide otherwise)

This isn't a university project, I was bored one evening and thought why not?
I am procrastinating on the game netcode for the tank game and tower of hanoi
Hopefully when I do start university I can hand this in

```
(print "Hello, World!")
```
or
```
(program "hello world" (print "Hello, World!"))
```
The latter is useful if you, for some reason, want to use multiple files

This language is really sloppily made so there will be bugs
The plan for this language is to make it partially self-hosted
```
./brackish brackish.brac srccode.brac
```
brackish.py is where I translate my problems into Python to solve
But at this point my C file is further along than my Python file

The `logo.jpg` I got online from DuckDuckGo when you search "Brackish water", and filter "Free to Modify, Share, and Use Commercially"
My jourey and the problems I faced are in doc/problems.md and feature suggestions are in doc/features.md
#### Please do suggest things in there, any other pull request will be denied as this is a practice project for me
##### Make your own lisp (you can fork it) I promise it is fun

It is also in one file because file navigation practice.
Normally I would put the DS/A into their own file, the file reading into another one.
But I want to practice navigating large files.

These are currently some of the suggestions:
- The standard library is called `Water`
- The package manager is called `Saline`
- The build system is called `Dinghy` / `Ship`
- To run you do `dingy sail file.brac`
- To load a library into memory you do `saline dock <library>`
? is debug info (beginning of expr) and hello world looks like
#### Of course, none of these features are yet implemented. This is just for the future

Special thanks to @affanhamid for coming up with all these puns
