# DBKeys

A collection of database benchmarks and micro-benchmarks. This project will evolve in a test-harness, that defines a set of desired micro-benchmarks. Each benchmark is defined by its input and output. The test-harness provides the input to each competitor, times the executions and verifies the produced output.

## Code Usage
```
make 
./dbkeys <benchmark id> <params>
```

## Micro-Benchmarks

### Aggregation
```
SELECT G, SUM(S)
FROM table
GROUP BY G;
```

This micro-benchmark executes the SQL query above, which groups all rows of a 
table based on the values of column G. For each group, we sum the values 
of column S for all rows that belong to said group. Example:
```
Relation: Students
--------------------------------------------
| Student Name | Major | # Enrolled Courses | 
--------------------------------------------
|      A       |   CS  |          6         |
|      B       |   EE  |          2         |
|      C       |   EE  |          5         |
|      D       |   EE  |          2         |
|      E       |   CS  |          2         |
|      F       |   EE  |          1         |
|      G       |   CS  |          0         |
--------------------------------------------

SELECT Major, SUM(# Enrolled Courses)
FROM Students
GROUP BY Major

-----------------------------------
| Major | SUM(# Enrolled Courses) |
-----------------------------------
| CS    |          8              |
| EE    |         10              |
-----------------------------------
```

### Parameteres that affect an aggregation:
| Parameter        |        Value      |
| ---------------- | ----------------- |
| Input Size       |   > 0             |
| #Unique Groups   |   [1, Input Size] |

#### What are good ranges for the aggregation parameters?

Input Size: [10^4, 10^9] rows

Unique Groups: [10, Input Size)/2] rows

Note: Of course our initial experiments do not have to scale to inputs with 1B rows.
We can start with small inputs < 10M and examine the cases of interest
for each architecture. For example, for CAPE we considered a few cases; the entire
input fits in the associative memory, the input fits in a CPU cache (best cache for our competitor), 
the input is many times larger than the associative memory. We similarly varied 
the #unique groups; the groups fit in the associative memory, 
the cpu cache, many times larger than both.

### Implementation Details

Both columns of the input are 32-bit integer numbers.

### Running the aggregation benchmark

Execute the aggregation microbenchmark:
```
./dbkeys agg <input_size> <no_unique_groups>
```

### Join
```
SELECT *
FROM fact, dimension
WHERE fact.FA = dimension.B;
```

This micro-benchmark executes the SQL query above, which join tables fact 
and dimension based on the values of attributes fact.A and dimension.b.  
Example:
```
Relation: fact
-------------------
|  FA |  FB |  FC | 
-------------------
|  2  |  -  |  -  |
|  3  |  -  |  -  |
|  5  |  -  |  -  |
|  2  |  -  |  -  |
-------------------

Relation: dimension
-------------
|  DA |  DB | 
-------------
|  1  |  -  |
|  2  |  -  |
|  3  |  -  |
|  4  |  -  |
|  5  |  -  |
-------------

-------------------------------
| FA | DA | FB | FC | DA | DB |
-------------------------------
| 2 |  2  |  - |  - |  - |  - |
| 3 |  3  |  - |  - |  - |  - |
| 5 |  5  |  - |  - |  - |  - |
| 2 |  2  |  - |  - |  - |  - |
-------------------------------
```

Execute the join microbenchmark:
```
./dbkeys join <fact table size> <dimension table size>
```

### Notes about joins
The fact table is usually many times larger that a dimension table (1:12 ratio).
Each row of the fact table matches to one row of the dimension table (pk-fk join).

#### What are good ranges for the join parameters?

Fact Size: [10^5 - 10^9] rows

Dimension Size: [10^4 - 10^8] rows

Note: Of course our initial 
experiments do not have to scale to inputs with 1B rows. We can start with 
small inputs < 10M and examine the cases of interest for each acceleerator. 

### Implementation Details

Both FA and DA columns are 32 bit integers.

## TODO
- Discuss how to do verification of results

## References
[1] [Castle Paper] (http://pages.cs.wisc.edu/~chronis/files/castle_extended.pdf)
