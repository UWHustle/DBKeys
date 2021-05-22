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

Input Size: 0 - 100*10^6.

Unique Groups: 100-(Input Size)/2

Note: These values ranges are a good startting point. Of course our initial experiments do not have to scale to inputs with 100M rows. We can start with small inputs < 10M and examine the cases of interest for each acceleerator. For example, for CAPE we considered a few cases; the entire input fits in the associative memory, the input fits in a CPU cache (best cache for our competitor), the input is many times larger than the associative memory. We similarly varied the #unique groups; the groups fit in the associative memory, the cpu cache, many times larger than both.

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
WHERE fact.a = dimension.b;
```

This micro-benchmark executes the SQL query above, which join tables fact 
and dimension based on the values of attributes fact.a and dimension.b.

Execute the join microbenchmark:
```
./dbkeys join <fact table size> <dimension table size>
```
