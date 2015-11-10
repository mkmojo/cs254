This version of the code can handle global definitions within the same file.

##How to use the program:
    ruby xref.rb test/test

##Overall strategy:
Parse the dwarfdump output, construct objects for records in debug_info section and debug_line
section.

The records in debug_info section has information about all definitions in program.
The records in debug_line section has scoping informatoion.

Use the above two pieces of information, one can tell that at each scope, what definitions 
can be seen. That is if given a line in some source file, `xref` can tell what scope the line
is in. 

##Check List
- [x] Glboal variables within same file
- Local variables
- formal parameters
- types
- structure

##Extra Credit
None