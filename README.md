# FirstLisp.c - Brackish
I want to try making a Lisp without any help from AI or tutorials

A language running on a C interpreter (`BraCkish`)

It's called `Brackish` like the saline water due to the fact that there are brackets.<br>
I didn't want to spend hours thinking of a name so I just took that.<br>
The file extension is `.brac` although that is really not checked.<br>
(You could name it `.foo` and it would probably still work until I decide otherwise)

This isn't a university project, I was bored one evening and thought why not?<br>
I am procrastinating on the game netcode for the tank game and tower of hanoi.<br>
Hopefully when I do start university I can hand this in.<br>

To print hello, world! do: (note that you ***must*** wrap expressions in parentheses):
```
(print "Hello, World!")
```
or
```
(program "hello world" (print "Hello, World!"))
```
The latter is useful if you, for some reason, want to use multiple files.<br>
I don't recommend it because this is proof-of-concept more than anything.

This language is really sloppily made so there will be bugs. Just shoot me a message or add a feature suggestion.<br>
The plan for this language is to make it partially self-hosted;
```
./brackish brackish.brac srccode.brac
```
brackish.py is where I translate my problems into Python to solve, but at this point my C file is further along than my Python file.<br>
What stops me from making this in Python entirely is the fact that Python:
1. lacks pointers (pointers do exist with `ptr[0] = value` but it gets messy very fast)
1. isn't as fun to program in as it is in C (Python does a lot of algorithms for you, and I like my algorithms)
1. doesn't let me micro-optimise memory usage


The `logo.jpg` I got online from DuckDuckGo when you search "Brackish water", and filter "Free to Modify, Share, and Use Commercially"
My jourey and the problems I faced are in doc/problems.md and feature suggestions are in doc/features.md
#### Please do suggest things in there, any other pull request will be denied as this is a practice project for me
##### Make your own lisp (see `LICENSE.md`) I promise it is fun

It is also in one file because file navigation practice.<br>
Normally, I would put the DS/A into their own file, the file reading into another one, the structs into headers, etc.<br>
Then compile the headers with a sed script, and have a fully fletched atomic transferable build system.<br>
Reason why I didn't is because I would like to practice navigating large files in Emacs.

These are currently some of the suggestions:
- The standard library is called `Water`
- The package manager is called `Saline`
- The build system is called `Dinghy` / `Ship`
- To run you do `dingy sail file.brac`
- To load a library into memory you do `saline dock <library>`
- ? is debug info (beginning of expr)
#### Of course, none of these features are yet implemented. This is just for the future

Special thanks to [@affanhamid](https://github.com/affanhamid) for coming up with the suggestions
