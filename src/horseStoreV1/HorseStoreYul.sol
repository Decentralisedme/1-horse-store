// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract HorseStoreYul {
    uint256 numberOfHorses;

    function updateHorseNumber(uint256 newNumberOfHorses) external {
        // numberOfHorses = newNumberOfHorses;
        // Assembly: we just do this:
        assembly {
            // What we want is to store in a slol numb of horses
            sstore(numberOfHorses.slot, newNumberOfHorses)
        }
    }

    function readNumberOfHorses() external view returns (uint256) {
        // return numberOfHorses;
        assembly {
            // set a var
            let num := sload(numberOfHorses.slot)
            // Store it in memeory
            mstore(0, num)
            // Return the value
            return(0, 0x20)
        }
    }
}
