// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import {Test, console2} from "forge-std/Test.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";

/** Tests For Sol and Huff contracts */

abstract contract Base_TestV1 is Test {
    HorseStore public horseStore;
    
    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    function testReadValue() public {
        uint256 initialValue = horseStore.readNumberOfHorses();
        assertEq(initialValue,0);
    }

    function testWriteValue() public {
        // dec 777 >> hex 0x309
        uint256 horseNumber= 777;
        horseStore.updateHorseNumber(horseNumber);
        assertEq(horseStore.readNumberOfHorses(), horseNumber);
    }

}
