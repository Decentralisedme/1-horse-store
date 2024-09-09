# Horse Store
1. write basic simplestorage/horsestore

#### Process
1. I send the data
2. Dispacher selects the function
3. Dispacher sends the data to the funciton

## Tests
#### Set-up:
1. Huff Foundry Extension - Fundry-Huff- to be installed:
```shell
$ forge install huff-language/foundry-huff --no-commit
```
2. Foundry.toml to be updated: 
```shell
$ ffi = true
```
This will allow to use/import the `{HuffDeplo}`

#### Crating tests and running them:
Wrote the following files:
1. Base_TestV1.t.sol: abstract contract that contains all the tests
Two test functions:
```shell
$ function testReadValue() public {}
```
```shell
$ function testWriteValue() public {}
```

2. HorseStoreSolc.t.sol: contract is Base_TestV1, use to test solidity contracts
3. HorseStoreHuff.t.sol: contract is Base_TestV1, use to test huff contracts

To run the tests you can simply:
```shell
$ forge test
```
Or if you want to check Huff test only:
```shell
$ forge test --match-path *Huff* -vvv
```
With debag you can check the steps on each Opcode - 
```shell
$ forge test --match-path *Huff* --debug testReadValue -vvv
```





-   **Chisel**: Fast, utilitarian, and verbose 
## Documentation


```shell
$ forge build
```

### Test

```shell
$ forge test
```

