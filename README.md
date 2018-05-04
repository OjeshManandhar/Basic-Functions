# Basic-Functions
Some of the functions I use in my codes
This repo is just like [QBASIC-func-through-C](https://github.com/OjeshManandhar/QBASIC-func-through-C)

### Requisites
Certian function from [QBASIC-func-through-C](https://github.com/OjeshManandhar/QBASIC-func-through-C) are used.

So you need to install this static library in **Code::Blocks** or you can just copy-paste those function.

### Development
I used **Code::Blocks 17.12** as IDE and compiler on Windows 10.

### Installing/Cloning
To clone it on your local machine,
- Clone this repository to your local machine.
```shell
git clone https://github.com/OjeshManandhar/Basic-Functions
```
- Go inside the directory where you placed the cloned repo
- Now install [QBASIC-func-through-C](https://github.com/OjeshManandhar/QBASIC-func-through-C)
- Build the project
- Link the *.a* file created after building
  + Goto *Settings* tab on navigation bar then *Compiler...*
  + Goto *Linker settings* tab in *Global compiler settings*
  + Click *add* and browse to the Project folder
  + The *.a* file is inside *bin\Debug\\*
- Add *basic_func.h* in **Code::Blocks** header folder
  + Goto the directory where you installed **Code::Blocks**
  + Open *CodeBlocks* folder
  + Open *MinGW* folder
  + Open *include* folder
  + Copy *basic_func.h* from the cloned folder and paste it here
- Then just include *QBASIC_func_C.h* anytime you want to use these function in your code
```C
#include <basic_func.h>
```

### Further Improvements
If you're interested, feel free to fork and submit PR.
- More conversion codes
- Easier algorithm for conversion and other functions
  
### License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
