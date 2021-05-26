## DBKeys

In this project we evaluate PIM/novel architectures for databases.
We hypothesize that a collaborative approach that utilizes novel 
processing elements across memory/storage devices is key to maximize 
performance.
 
Databases answer user submitted queries. Queries are decomposed into a limited 
set of well defined operators (i.e. filter, aggregation, join). Each of the 
core operators follows a different processing pattern. Database operators are 
defined at a logical level. There are multiple implementations for each
operator (i.e. for a cpu: hash based or sort based). The best implementation 
depends on the data (size, distribution) and query at hand but also the 
performance characteristics of the hardware. 

As a first step we should study the performance we can achieve for each
operator for each PIM device. The insights gained from this study will inform
our next steps. The end result could be that some operators 
(or maybe parts of them) are best suited for some architectures or 
processing paradigms. Combining multiple PIM devices could potentially 
yield the best performance.

This project could approach a multi-PIM system from a design perspective 
(what are the best processing paradigms per db operator? what is the best way to
combine novel processing elements?). 

A single thread implementation of an 
operator (designed for a traditional CPU) is a sufficient baseline for this
stage. Multi-threaded/GPU baselines will be considered in the future.

### Goals
- Implement and evaluate core database operators for each
architecture/processing paradigm. Identify advantages and limitations.
- The aggregation operator is the first one we should study. Is is not a
trivial operator (like a filter) but not as complex as a join. Efficiently
implementing an aggregation operator is not a solved problem even for
traditional systems.
- Define the appropriate baselines for our study.

### Paper Sketch

- Hardware trends dictate the need for novel architectures following 
new processing paradigms. We present a set of interesting approaches.
- Experimental and theoretical  evaluation of novel architectures (and processing 
paradigms) for the core database operators. Present how to map database 
operators to each architecture and what are the benefits/limitations.
-  Investigate a collaborative approach where multiple technologies are 
combined to maximize performance. 
- Present how a database could optimize execution for a multi-PIM system.
