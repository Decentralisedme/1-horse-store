# Intro to lower lavel bytecode
The exercise is to develop the same contract in Solidity, Yul and Huff, plus some inline assembly.
This is a great intro to lower level langs which helps to get a clear undestanding of EVM behaviour especially when it comes down to stack, storage, memory and how they interact via stack syntax.

## Tools:
These are tools which I found very usefull:
-   **Scripts**:
- Get the Function Signature: `cast sig "isHappyHorse(uint256)"`
- Conversion Hex to Dex and viceversa: `cast to-base 0x15180 dec`
- Foundry chisel: REPL 
- Test debug: `forge test --debug`
- huffmate: import Hashmap.huff / CommonErrors.huff


# Horse Store V1
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
$ remappings = [
    'foundry-huff=lib/foundry-huff/src',
    '@openzeppelin/=lib/openzeppelin-contracts/',
]
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

2. HorseStoreSolc.t.sol: contract is Base_TestV1, used to test solidity contracts
3. HorseStoreHuff.t.sol: contract is Base_TestV1, used to test huff contracts

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
## Huff
Give us the contract deployment
## Yul
We have inline assembly yul where we use yul in solidity,and we have stand alone Yul where we only ise Yul.
Install extension: Solidity + Yul Semantic Syntax
Yul has not `contracts` but `objects`
We need to write our contract deployment


# Horse Store V2
In version 2, HorseStore is a ERC721 contract so there are few considerations:
- ERC721 Interface Functions need to be declared:
```shell
$ '#'define function Transfer(address, uint256) nonpayable returns()
```
- ERC721 Interfaces Events need to declared
- Storage Slots to be delared as constants
- Immutable offsets also to be declared as constans




-   **Chisel**: Fast, utilitarian, and verbose 
## Documentation


```shell
$ forge build
```

### Test

```shell
$ forge test
```

