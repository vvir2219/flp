Parametrii liniei de comanda

1.Nu este unu

2.
absolut orice lucreaza cu fisiere de input/output sau are functionalitate optionala/extinsa sau ce poate primi input de orice fel
	- editoare de text (fisiere input/output, optiuni, posibilitate de editare direct din comanda)
	- indirectarea comenzilor (kill -n9 $(ps -ea | grep something))

3.
Python
#######

basic:
======

locatie: sys.argv (modulul sys)
tip de date: lista de string-uri
lungime luata prin lungimea listei: len(sys.argv)
primul argument e numele programului

extinderi:
==========

getopt
-------

getopt.getopt(args, options, [long_options])

args - argumente
options - string cu optiunile posibile (optiuni de o litera) (cu valoare adaugi un : dupa optiune)
long_options - lista de optiuni cu forma lunga (siruri de caratere) (cu valoare adaugi un = dupa optiune)

Adauga si aruncare de exceptii in caz de optiuni nerecunoscute sau daca optiunile cu valoare nu au valoare
Returneaza 2 valori 
	1 - lista de perechi de tipul (optiune, valoare)
	2 - restul argumentelor ce nu is optiuni 
		(de remarcat ca optiuni inseamna doar cele care incep cu "-" la optiuni de o litera si cu "--"
		la optiuni lungi)

argparse
---------

construct parsers for command line arrguments
here you define the rules by which arguments are parsed
you can have subparsers which act as commands and each parser's arguments can have type, destination variable(name), multiplicity, optionality, default value, 
action on argument found, and help string
the parser returns an object with the arguments as named attributes
this parser parses arguments after the program name				

Java
#####

locatie: through main function parameter 
tip de date: lista de string-uri
lungime luata prin lungimea listei: argv.length
primul argument NU e numele programului

extinderi:
==========

picocli
--------

constructs command line applications through addnotation on classes(basically it populates an addnotated class) and reflection
arguments are divided between options(starting with "-" or "--"), and positional arrguments and supports map options like -key1=val1 -key2=val2

Javascript
###########

locatie: process.argv
tip de date: lista de string-uri
lungime luata prin lungimea listei: argv.length
primul argument e node, urmatorul e numele programului

extinderi:
==========

https://stackoverflow.com/questions/4351521/how-do-i-pass-command-line-arguments-to-a-node-js-program/34782300#34782300
	Minimist: For minimal argument parsing.
	Commander.js: Most adopted module for argument parsing.
	Meow: Lighter alternative to Commander.js
	Yargs: More sophisticated argument parsing (heavy).
	Vorpal.js: Mature / interactive command-line applications with argument parsing.
	


4. Propuneri de extindere/imbunatatire.

named arguments (map like key=val)
typed arguments
	possible extension for object oriented programming languages
		struct-like arguments for class hierarchies
		say you have Base class and Derived class
		and at command line you could say Derived{ args-for-constructing-object }
		(not sure if actually usefull)
functions as commands (special command argument associated with function, could change all the other required arguments)
arguments to populate a global namespace of sorts (accesible everywhere with defined and typed variables)
optinon for direct association between arguments and flags/initialization functions

weird idea but worth a try(i feel it gets a litte too specific):
lets say you can define a list of commands for your program from which you can pick one to run
now lets say that your program is a service(does one thing) and you have a bunch of well defined "modules" which can "enhance" your service
a way to easily add or remove modules from the service (modules are ordered)
general example: program-name [{module args}] [{module args}][{module args}] command [{module args}]
specific example: service {log-module log-level=3 log-file=in.log} command {log-module log-level=3 log-file=out.log}

mai specific treaba pe aci
iau jumate si le documentez si specific

named arguments
===============
from the command line:
----------------------
named arguments shall be given as key=value, key='value', key="value", or without the '=' sign (just takes the next value)
if value has to have both ' and " present, they can be escaped with \ and the literal \ can be given as \\

positional arguments can be combined with named arguments but they require to retain their position relative to other positional arguments
for example:
	let there be 3 positional arguments denoted by p1, p2, and p3 and three named arguments k1=v1, k2=v2, and k3=v3
	the 3 named arguments can be given in any order but the p1, p2, and p3 arguments can be given only in this order
	but can be interleaved with the named arguments without further restrictions
in the case you may want to use the same argument as both positional and named, it has to have an order with all possible positional arguments
and in positional mode to respect that order relative to all the other positional arguments given
for example:
	let there be 3 named and positional arguments(3 with both possibilities): a1, a2, and a3
	in case they are given as a1=v1 a2=v2 and a3=v3, the order can be arbitrary
	in case one of them is given as positional, it's position again doesn't matter because it has no other positional arguments to be relative with
	in case 2 of them are given as positional, they shall retain the order, let them be a1 and a3, the possible combinations are:
		a2=v2 a1 a3
		a1 a2=v2 a3
		a1 a3 a2=v2

from the programming language:
------------------------------

Aditionally to what i defined above, i will define additional names of arguments (optionally) to be called from the command line(but not from the program)
so, there will be argument aliases(all disjunct, no two aliases or names in named arguments can be the same) which can substitute key names in the command line
the format of the arguments that can be given from the command line shall be configured for each program as so:
there shall be a programming construct with which the arguments configuration can be specified:
<configuration_clause> : "define arguments : [" <arguments_list> "]"
<arguments_list> : <argument_configuration> |
		   <arguments_list> "," <argument_configuration>
<argument_configuration> : <name>["/"<alias_list>] ["(" ["optional"]  ["positional"] ["named"] ")"]
<alias_list> <- <name> | <alias_list>"/"<name>

then at the runtime, the arguments shall be retreived from a global dictionary under the name "args"
where each argument shall be found under it's name or if the argument is optional and not given, the undefined value shall be found under that name
the default is for arguments to be positional. if named is selected, they can only be named unless positional attribute is explicitly used

exception will be thrown in the case of bad arguments(non-existent, to many, etc)
if no configuration is given, arguments cannot be passed to the program and exception is thrown if arguments are passed

typed arguments	(expanding what i said above)
===============

from the command line:
----------------------

the specification above remains the same, but the user defined types that will be parsed have to be given in a format known to the program
typed arguments can be given as a string, case in which the explicit type of the argument(as defined in the program, not a subtype) will be taken.
Types have to be a predefined data type or has to have a parser(class function or explicitly given function).
User defined types can also be given as follows: "{"<type>":"<string>"}" where the <string> will be the the input for the parser to construct the object 
and the <type> will be the type of the argument as defined in the source code(with the clause argument_configurations) or a subtype of that type

from the programming language:
------------------------------
i will add another attribute which cannot be given with any other attribute, that is the flag attribute, case in which <type> becomes implicitly boolean
it is from the command line as a flag and be given as -<name> if the name is a single letter or --<name> if name is composed of multiple letters, where 
<name> is the name of the argument or any of it's aliases
now <argument_configuration> will change, and has an obligatory field, <type>(if argument is not flag)
<argument_configuration> : <name> ":" <type>[":"<parser>] ["(" ["optional"]  ["positional"] ["named"] ")"] |
                           <name> "( flag )" 
<type> : fixed predefined data types or a fixed user defined type which has a parser for it from string(can be read from string),
     parser will be a class function by the name "fromString(string str)", and can be called as <type>.fromString(str)
	 if such a parser is not present, the configuration must have the <parser> argument, which is a function with the following signature:
		"<type> <parser_name>(string str)" where <type> is the type or a subtype of it
	 Class parser has lower priority over the <parser> argument
     In case of the argument given as <type>"{ data }", the parser function can only be used if it returns a type that is <type> or a subtype of it
     if it's not given a parser, the subtype mentioned has to have the class function "fromString"
     

The defaults for each argument are: positional(so arguments without attributes are obligatory, positional, and cannot be given as named or flag)
Named flag overrides the positional flag, if an argment is needed to be both, both attributes have to be specified

Examples:


--------------------- 1 ----------------------

let there be a program "convert" which transforms between file formats xml, json and yaml
this program usually takes input from standard input and writes to standard output in a plain format (no pretty printing)
but it can take a number of arguments: input file, output file, output format(input format is automatically recognized), output inplace

this program needs the folowing parameters: input file(optional, positional), output file(optional & named, name output_file), 
output format(named, name: to), output inplace(flag -i)

from the programming language:

define arguments : [
    input_file : File : open ( optional ), // here input_file is an argument of type file, parsed by the open function which opens a file by path
    output_file : File : open ( optional named ),
    target_format/to : string ( named ),
    inplace/i ( flag )
]

the program automatically transforms input_file and output_file to files given the path, and they can be accesed directly from "args" variable
ex: args.input_file <- file or undefined(throws error if the file does not exist)

example of program use:

convert to xml // takes data from standard input and converts to xml to standard output
convert data.dat to json // takes data from the input file data.dat(positional argument)
convert to json data.dat // same thing, positional argument but can be used in any position because it's the only positional argument
convert -i data.dat to json // converts inplace data.dat
convert data.dat to json output_file=data.json // writes to the output file

"covert -i to xml data.dat" is equivalent to "convert --inplace to xml data.dat"

--------------------- 2 ----------------------

let there be a program "f" which accepts logging with different log levels and optionally a log file
log levels can be: info, warning, error
if no logger is given, no logging can happen, else, logging will happen according to logger
logger will have log level and can be of different types: StandardLogger(outputs to stderr), FileLogger(outputs to file)
so, the program can have argument logger which is optional and positional and it's parsed by the data types hierarchy

from the programming language:

we have to have interface logger, class stdlogger, class filelogger, so:

interface Logger {
    string log_level;
    void log("message");
    
    static Logger fromString(string str);
}

class StandardLogger : Logger {
    // implementation
}

class FileLogger : Logger {
    File output_file;
    // implementation
}

define arguments : [
    logger : Logger ( optional )
]

from the command line:

f // starts program, no logging
f trace // trace logging with default logger(hopefully there is a static method in interface Logger implmenting fromString)
f { StandardLogger : trace } // starts f with standard logger
f { FileLogger : "trace.log, trace"} // starts f with file logger with trace output in trace.log




