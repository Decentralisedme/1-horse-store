// SPDX-License-Identifier: MIT

pragma solidity ^0.8.20;

contract HorseStore {
    uint256 numberOfHorses;

    function updateHorseNumber(uint256 newNumberOfHorses) external {
        numberOfHorses = newNumberOfHorses;
    }

    function readNumberOfHorses() external view returns (uint256) {
        return numberOfHorses;
    }
}
/*
FROM Remix
- Input: 0xcdfead2e0000000000000000000000000000000000000000000000000000000000000001

 1. Where did this data come from?
 2. How Remix knows what has to be updated?

*/
