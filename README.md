# DBKeys

A collection of database benchmarks and micro-benchmarks. 

## Code Usage
``
make 
./dbkeys <benchmark id> <params>
``

## Micro-Benchmarks

### Aggregation
``
SELECT G, SUM(S)
FROM table
GROUP BY G;
``

This micro-benchmark executes the SQL query above, which groups all rows of a 
table based on the values of column G. For each group, we sum the values 
of column S for all rows that belong to said group.

Execute the aggregation microbenchmark:
``
./dbkeys agg <input_size> <no_unique_groups>
``
### Join
``
SELECT *
FROM fact, dimension
WHERE fact.a = dimension.b;
``

This micro-benchmark executes the SQL query above, which join tables fact 
and dimension based on the values of attributes fact.a and dimension.b.

Execute the join microbenchmark:
``
./dbkeys join <fact table size> <dimension table size>
``
