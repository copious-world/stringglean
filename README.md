
# stringglean

tools for preprocessing script based programs e.g. Lua

In this repository, there is the code fore several command line programs which prepare files by altering their contents.
Some of the programs do string subsitutions. Others rewrite function calls. 

The programs that rewrite function calls are employed for the purpose of taking an easily readable set of code that 
someone might write and changing it into something more nearly compiled. The transforamation is more of a compression of the calls.
For example, strings may be simply hashed (indexed) and turned into integer parameters for functions that will restrict 
the operation on the parameters to a fixed amount of memory. String operations for formatting can be postponed by the functions.
And so, the string manipulation operations will be removed from the program. A string gazzeteer 
(not geographical for this pejoration) may be produced in order to retain the program's original strings. Or, a translation may
later be provided.

#The programs and what they do
