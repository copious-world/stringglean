
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

## The Programs and What They Do

Here is the list of programs to date:

1. `stringglean.cpp`
2. `hashreplacer.cpp`
3. `clear_empty_lines.cpp`

The first three programs are related to the parameter transformation task. The fourth program is more for generating static html files.

**stringglean**
> takes files from a directory with each file containing any text, preferably a program and gleans the strings. That is, it looks for strings defined in progamming style, delimitted by quot or double quote. E.g. **'** or **"**.
> The program places strings into a map, which maps the strings to an index. The program outputs the map into JSON format, which may be piped into a file from the command line. The best way to call *stingglean* is as follows:
> >stringglean *input_dir* *extension_filter* > index.txt
> 
> The paramters have defaults. So, without the paremters is the same as
> > stringglean . luapp
> 
> The directory is where the files are. The program will only operate on the files with extensions that match the second parameter.
> 

In the tools directory are a few helful scripts. One of these calls on the programs to transform the files. Here is the script from tools/builapp.sh

```
dir=$1
level=$2
echo ${dir} ${level}
stringglean ./${dir}/src-pp luapp > ./${dir}/gazzeter.txt
bash ./tools/rungpp.sh ${dir} ${level}
#
echo "hashreplacer"
bash ./tools/hashreplacer.sh ${dir}
echo "clear_empty_lines"
clear_empty_lines ./${dir} lua
```

Notice the line after the call to *stringglean*. It invokes a script that rungs **gpp**. **gpp** is the [generic preprocessor](https://math.berkeley.edu/~auroux/software/gpp.html). You will find, in the repsitory, a *.hua* file. It is macro definition file for use in **lua** programs. As for as I know, the Lua team does not use *.hua* files. But, such a file can be used to include macros to be fed to **gpp**. The header file supplied is for the example of setting log levels (or other levels) which will select statements for staying in the program or not.

Here is the script that is used to call up **gpp** for processing **luapp** files. (Note: **luapp** is a play on cpp or other such preprocessing callouts.):

```
#run gpp on the files in the included directory.
echo $1
pushd ./$1
pwd
#
if [ -z $2 ]; then
	level=4
else
	level=$2
fi
#
files=$(ls ./src-pp/*.luapp)
mkdir ./mtmp
for ff in $files
do
	fstem=$(basename $ff .luapp)
	echo $level
	#
	gpp +n -DLOG_LEVEL=$level $ff > ./mtmp/"$fstem".lua
done
popd
```

Once the files are operated upon by the previous two procsses, they are ready for parameter transformation.


**hashreplacer**
> takes as input parameters, a file, a prefix which identifies a function call that has to be transformed, a map of strings to integers, and finally a template form indicating how to format the string id in the transformed programs.
> 
> Here is an example:
> `hashreplacer $ff 'g_mlcl.' gazzeteer.txt '@' > "$fstem".lua`
> 
> *$ff* is a variable in a **bash** script that contains a file name.
> *'g_mlcl.'* is a prefix to a log library object. The name of the map, produced by **stringglean** follows. The last parameter says that the string id will be put in without other characters around it.
> 
> If the fourth parameter had been '(int)(@)', then the string id would be the number cast to an integer. This **C** style cast is not part of Lua, however.
> 
> **hashreplacer** outputs to standard output.
> 

Once **hashrepacer** has run, the process for transforming the file is done. But, since it may be helpful to go back and look at the transformed file, **clear\_empty\_lines** may be used to remove empty space in the file that might have been left by **gpp** or other programs. The output, however is not what the programmer should have to read for debugging purposes.

An example for this processing is in the directoy *gateway*.

