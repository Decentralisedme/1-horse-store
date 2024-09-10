object "HorseStoreYul" {
    code{
        // Contract deployment
        datacopy(0, dataoffset("runtime"), datasize("runtime"))
        // slot =0 / start at runtime obj / copy for the entire size 
        return(0, datasize("runtime"))
        // we put the runtime code on chain
    }
    object "runtime" {
        code{
            // Function dispatcher
            switch selector()
            // Funct: updateHorseNumber(uint256)
            case 0xcdfead2e {
                // function with parameter = decodeUint(0)
                storeNumber(decodeAsUint(0)) 
            }

            // Funct: readNumberOfHorses()
            case 0xe026c017 {
                returnUint(readNumber())
            }
            // None is matched:
            default {
                revert(0,0)
            }

            function storeNumber(newNumber){
                sstore(0,newNumber)
            }

            function readNumber() -> storedNumber {
                // just get what is a zero position
                storedNumber := sload(0)
            }

            /* -- decoding functions --*/
            function selector() -> s {
                // we divide the call data for that number (57 digits in length)
                // it will return the s variable which is the Funct selector
                s := div(calldataload(0), 0x100000000000000000000000000000000000000000000000000000000)
            }

            function decodeAsUint(offset) -> v {
                // from where we pull from
                let positionInCalldata := add(4,mul(offset,0x20))
                // here is same size check seen in breackdown
                // if calldata is < position then revert
                if lt(calldatasize(), add(positionInCalldata,0x20)) {
                    revert(0,0)
                }
                v := calldataload(positionInCalldata)
            }

            function returnUint(v) {
                mstore(0,v)
                return(0,0x20)
            }
        }
    }
}