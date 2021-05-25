## DBKeys

In this project we evaluate PIM/novel architectures for databases.
We hypothesize that a collaborative approach that utilizes novel 
processing elements across memory/storage devices is key to maximize 
performance.
 
Databases answer user submitted queries. Queries are decomposed into a limited 
set of well defined operators (i.e. filter, aggregation, join). Each of the 
core operators follows a different processing pattern. Database operators are 
defined at a logical level. There are multiple implementation for each
operator (i.e. for a cpu: hash based or sort based). The best implementation 
depends on the data (size, distribution) and query at hand but also the 
performance characteristics of the hardware. 

Understanding the performance we can achieve for each operator for each PIM
device is the first step. The insights gained from this study will inform our 
next steps. The end result could be that some operators 
(or maybe parts of them) are best suited for some architectures or 
processing paradigms. Combining multiple PIM devices could potentially 
yield the best performance.

This project could approach a multi-PIM system from a design perspective 
(what are the best processing paradigms per db operator? what is the best way to
combine novel processing elements?) rather than focusing on the best absolute
performance we can achieve today. A single thread implementation of an operator
(designed for a traditional CPU) is a sufficient baseline for this stage. 


### Paper Sketch

- Hardware trends dictate the need for novel architectures following 
new processing paradigms. We present a set of interesting approaches.
- Experimental and theoritical evaluation of novel architectures (and processing 
paradigms) for the core database operators. Present how to map database 
operators to each architecture and what are the benefits/limitations.
-  Investigate a collaborative approach where multiple technologies are 
combined to maximize performance. 
- Present how a database could optimize execution for a multi-PIM system.
