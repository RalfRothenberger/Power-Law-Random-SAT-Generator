# Power-Law Random SAT Generator
## Preface
Generator for random SAT instances as proposed in the paper *Towards industrial-like random SAT instances* (IJCAI 2009) by Carlos Ansótegui, Maria Luisa Bonet, and Jordi Levy.
This generator has been used for generating the experimental results in the papers *Phase Transitions for Scale-Free SAT Formulas* (AAAI 2017) by Tobias Friedrich, Anton Krohmer, Ralf Rothenberger, and Andrew M. Sutton and *Bounds on the Satisfiability Threshold for Power Law Distributed Random SAT* (ESA 2017) by Tobias Friedrich, Anton Krohmer, Ralf Rothenberger, Thomas Sauerwald, and Andrew M. Sutton.
## Installation
Just call

``> make``

No configuration or specifics needed.
## Usage
The generator can generate three kinds of instances.
* **Random k-SAT:** The classical model, where each k-clause is drawn with uniform probability.
* **Power-Law k-SAT:** One of the new models proposed by Ansótegui et al., where the variables for each k-clause are drawn according to a power-law probability distribution.
* **Double Power Law:** Another new model proposed by Ansótegui et al., where clause lengths are drawn according to a power-law distribution. Then variables per clause are drawn according to a (possibly different) power-law probability distribution.

### Example
``> CreateSAT -g p -v 100 -c 426 -k 3 -p 2.5 -f test -u 1``

Creates a random 3-CNF with 100 variables and 426 clauses.
Variable frequencies are power-law distributed with power-law exponent 2.5
Variables are unique per clause.
Formula is written in cnf format to test.cnf in the base directory.

### Options
```
-g d|p|u
        choose between power-law distributed variables (p) or double power-law (d) or uniform (u)
-v <number of variables>
-c <number of clauses / scaling factor>
-k <clause length>
        for double power-law this is the average clause length
-p <power-law exponent of variables>
-b <power-law exponent of clauses>
        only for double power-law
-f <output file>
        in cnf-format, the ending will be added automatically
-u 0|1
        should variables be unique per clause(1) or not(0)
-q
        start quietly
-s
        seed value (int), system time is used if none is given
```
