# Summer of Bitcoin

This is my attempt at the task given to me for application of Summer of Bitcoin

I managed to get the miner's gas fee to be **5,704,530**.<br/>
And the number of transactions that we included were _3,999,904_.

### Tu run it locally:

```
g++ main.cpp -o solution.out
./solution.out
```

### Output you should receive:

```
Reading data from "mempool.csv"
Data successfully read from "mempool.csv"
Calculating the transactions that are optimal for the given constraints.
Maximum Possible Fee that can be earned by the miner is: 5704530
The total block weight to get the above fee is: 3999904
Writing transaction IDs to "block.txt"
3178 have been successfully written to "block.txt"
```
