// 0x6080604052348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea264697066735822122011b56db01e1ad1287f59cded991b43104213badb339d81e88e5d1f07f690692864736f6c634300081a0033
// go to Playground / Memonic

/*
We know there ae 3 sections;
1. Creation Creation
2. Runtime
3. Metadata
*/

////////////////////////
// 1. Creation Creation
////////////////////////

// Free Memory Pointer: this always at the start
PUSH1 0x80; // [80]                             // 60 80
PUSH1 0x40; // [80, 40]                         // 60 40
MSTORE;     //                                  // 52: input: Top = offset =40 , bottom = size =80

// What this chunk do? Tells if NO value has been sent >> Jump to 0x0e PC JUMPDEST
// If value has been sent (ISZERO == 0) >> mxt step >> REVERT: stop execution
// IF no value has been sent (ISZERO == 1) >> JUMP to 0x0e

CALLVALUE;  // 34 // [msg.value]                      // 34 // we do not have it
DUP1;       // 80 // [msg.value, msg.value]           // 80 duplicate
ISZERO;     // 15 // [msg.value ==0, msg.value]       // 15 a == 0: 1 if a is 0, 0 otherwise: here 1
PUSH1 0x0e; // 60 0x0e // [0x0e, msg.value ==0?, msg.value] // 60 // 0x0e = 14 >> ProgramCounter>> where to jump
JUMPI;      // 57 // [msg.value]  (here=1=no value sent >>  we jump) // 57: jump to (topStack) if bottom is true, No Output so we habve on 1 msg.vlue left
PUSH0;      // 5f // [0x00, msg.value]                                  // 5f
DUP1;       // 80 // [0x00, 0x00, msg.value]
REVERT;     // fd // [msg.value] // revert Input: offset/size [0x00, 0x00]

// JumpDest = 0x0e when msg.value==0
JUMPDEST;   // 5B //    [msg.value] >> Value before JUMPI
POP;        // 50 //    []
PUSH1 0xa5; // 60 a5 // [0xa5] // 0x05 = 165
DUP1;       // 80 //    [0xa5, 0xa5]
PUSH1 0x1a; // 60 1a // [0x1a, 0xa5, 0xa5] // 0x1a = 26
PUSH0;      // 5f //    [0x00, 0x1a, 0xa5, 0xa5]
CODECOPY;   // 39 //    [0xa5]  // Input: destOffsets (Memory) / ofsset /size // Memory: [runtimecode]
PUSH0;      // 5f //    [0x00, 0xa5]
RETURN;     // f3 //    [] // Output: returns item from from Memory

INVALID;    // fe //

////////////////////
//  2. Runtimne Code: 
////////////////////

// Data: 6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea264697066735822122011b56db01e1ad1287f59cded991b43104213badb339d81e88e5d1f07f690692864736f6c634300081a0033
// calldata: 0xcdfead2e0000000000000000000000000000000000000000000000000000000000000007 

// 2.a Free Memoery Pointer 
PUSH1 0x80; // 60 0x80 //   [0x80]
PUSH1 0x40; // 60 0x40 //   [0x40,0x80]
MSTORE;     // 53 //        [] >> set free memory pointer

// 2.b:check no value has been sent
CALLVALUE;  // 34 //        [msg.value] // msg.value == 0
DUP1;       // 80 //        [msg.value, msg.value]
ISZERO;     // 15 //        [msg.value ==0, msg.value, msg.value] // yes it is zer >> 1 in the stuck
PUSH1 0x0e; // 60 0x0e //   [0x0e, msg.value ==0?, msg.value] // need to tell where to jump PC
JUMPI;      // 57 //        [msg.value]  // If 1>> Jump to 0x0e JUMPDEST, (here=1=we jump)
// We JUMP: we did not sent any value iszer YES >> =1 / Jumpif >< 0, 1><0 >> JUMP to e
PUSH0;      // 5f //        [0x00, msg.value]
DUP1;       // 80 //        [0x00, 0x00, msg.value]
REVERT;     // fd //        [msg.value]

// 2.C: CALLDATA_Size: check if there enough hex for a function
// JumpDest = 0x0e when msg.value==0 >> true =1 JUMP if 1 to JUMPDEST
// This checks if there is enough data for Function_Selector, the least is 0x04 (8bites), if is less (LT) >> Jump 
JUMPDEST;   // 5B //        [msg.value] >> Value before JUMPI
POP;        // 50 //        []
PUSH1 0x04; // 60 0x40 //   [0x04] 
CALLDATASIZE; // 36 //      [colldata_size, 0x04] /// size  = 24 bytes = 4 (function) + 20 (number 7 is 32 bytes)
LT;          // 10 //       [colldata_size < 0x04] compare a<b is TRUE then 1 / compare a<b is FALSE then 0: 24<4 >> FALOS  = 0 
// [0x24 < 0x04] >>LT [0]
PUSH1 0x30;  // 60 0x30 //  [0x30, 0x00]
JUMPI;       // 57 //       [] >> Jump if  >< 0: condition colldata_size < 0x40 is FALSE (0): so =0 >> NO JUMP
// WE DID NOT JUMP
// 2.D: Function Dispacher >> UpdateNumbOfHorses
PUSH0;       // 5f //       [0x00]
CALLDATALOAD;// 35 //       [32bytes of calldata] = cdfead2e00000000000000000000000000000000000000000000000000000000 
PUSH1 0xe0;  // 60 e0 //    [0xe0, 32bytes of calldata]  == 
SHR;         // 1C //       [calldata[0:4]] ?? we have selected the function [cdfead2e]
DUP1;        // 80 //       [calldata[0:4], calldata[0:4]]    
PUSH4 0xcdfead2e; // 63 cdfead2e // [0xcdfead2e, calldata[0:4], calldata[0:4]] Push 4 bytes, whihc is our fucntion
EQ;          // 14 //            [0xcdfead2e==calldata[0:4],calldata[0:4]]  >> calldata[0:4] is 0xcdfead2e so [1,0xcdfead2e ]
PUSH1 0x34; // 60 34 //          [0x34, 1, 0xcdfead2e]
JUMPI;      // 57 //             [0xcdfead2e]    if calldata[0:4] = 0xcdfead2e >> JUMP 0x34 (updateNumberOfHorses) JUMP to Progrm Counter 0x034
// WE JUMP: jump if >< 0:it is cose  EQ = 1  

// 2.E Function Dispacher >> readNumbOfHorse
DUP1;       // 80 //            [calldata[0:4],calldata[0:4]] >> in Huff we do not do DUP again
PUSH4 0xe026c017; // 63 e026c017 // [0xe026c017,calldata[0:4],calldata[0:4]]
EQ;         // 14 //                [0xe026c017==calldata[0:4],calldata[0:4]]
PUSH1 0x45; // 60 45 //         //  [0x045, 0xe026c017==calldata[0:4],calldata[0:4]]
JUMPI;       // 57 //           [calldata[0:4]]  if calldata[0:4] = 0xe026c017 >> JUMP 0x45
// We went through 2 Funct Dispatchers >> if no match gcode keeps going to REVERT >>

// 2.F REVERT
// calldata_size < 0x04: ment no function to select,JUMP here where we revert
JUMPDEST;       // 5B //
PUSH0;          // 5f //        // [0x00]
DUP1;           // 80 // [0x00, 0x00]
REVERT;         // fd // []

// 2.G Jumped from 2.D = Func Dispacher Update: calldata[0:4] = 0xcdfead2e
JUMPDEST;       // 5B //        [calldata[0:4]]
PUSH1 0x43;     // 57 43 //     [0x43, 0xcdfead2e] 
PUSH1 0x3f;     // 57 3f //     [0x3f, 0x43, 0xcdfead2e]
CALLDATASIZE;   // 36 //        [calldata_size, 0x3f, 0x43, 0xcdfead2e]
PUSH1 0x04;     // 57 04 //     [0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]  // calldata_size = 24
PUSH1 0x59;     // 57 59 //     [0x59, 0x04, calldata_size, 0x3f, 0x43, calldata[0:4]]
JUMP;           // 56 //        [0x04, 24, 0x3f, 0x43, 0xcdfead2e] >> jump to 59
// We JUMP

// 2.H: SSTORE >> we jump here anytime we need to store
// We jumpe from [0x3f,  7, 0x43, 0xcdfead2e]
// Jumped from 1-Func Dispacher Read: calldata[0:4] = 0xe026c017
JUMPDEST;       // 5b //        [0xe026c017]
PUSH0;          // 5f //        [0x00, 0xe026c017]
SSTORE;         // 55 //        
JUMP;           //    //

JUMPDEST;       // 5b // 
STOP;

// 2. Jumped from Func Dispacher Read: calldata[0:4] = 0xe026c017
JUMPDEST;       // 5b // 
PUSH0;
SLOAD;
PUSH1 0x40; 
MLOAD;
SWAP1;
DUP2;
MSTORE;
PUSH1 0x20; 
ADD;
PUSH1 0x40; 
MLOAD;
DUP1;
SWAP2;
SUB;
SWAP1;
RETURN;

// 2. JUMP from 2.G: Sol is checking if there are enough calldata 
// We Have function 4-bytes but the we have a number uint256 =  32bytes = 0x20 TOT 0x024
// 2.G: Func Dispacher Update:  0xcdfead2e = calldata[0:4] =
// Tot Call Data = 
JUMPDEST;       // 5b //    [0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e] = [0x04, 24, 0x3f, 0x43, 0xcdfead2e]
PUSH0;          // 5f //    [0x00, 0x04, 24, 0x3f, 0x43, 0xcdfead2e]
PUSH1 0x20;     // 60 20 // [0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]
DUP3;           // 82 //    [0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e] 
DUP5;           // 84 //    [calldata_size, 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]
SUB;            // 03 //    [calldata_size - 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]]
// SLT is basically checking if there is more calldata in addition to funct selector? 
// 0x20 = 32bytes: SL If calldats size -04 < 32bytes  True = 1
SLT;            // 12 //    [calldata_size - 0x04 < 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]]
// calldata_size - 0x04 < 0x20 == 24 - 4 < 20 ==== NO > 0: [0x00, 0x00, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]]]
ISZERO;         // 15 //    [0x01, 0x00, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]]
PUSH1 0x68;     // 60 68 // [0x68, 0x01, 0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]
JUMPI;          // 57 //    [0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e] // 0x01 >< 0 Then JUMP to 68
// We JUMPI: if >< 0 we jump: taht is 1 >> we jump to 68
PUSH0;          // 5f //
DUP1;           // 80 //
REVERT;         // fd //

// colldata_size = 24 (0x20=32 bytes for th7 + 0x04 for the function) = 0x24
JUMPDEST;       // //       [0x04, calldata_size, 0x3f, 0x43, 0xcdfead2e]
POP;                //      [calldata_size, 0x3f, 0x43, 0xcdfead2e]
CALLDATALOAD;       //      [7, 24, 0x3f, 0x43, 0xcdfead2e]  
SWAP2;                //    [0x3f, 24, 7, 0x43, 0xcdfead2e]
SWAP1;              //      [24, 0x3f,  7, 0x43, 0xcdfead2e]
POP;                //      [0x3f,  7, 0x43, 0xcdfead2e]
JUMP;               //      [0x3f,  7, 0x43, 0xcdfead2e]

INVALID
LOG2;
PUSH5 0x6970667358; 

INVALID

SLT;
KECCAK256;
GT;

INVALID;

PUSH14 0xb01e1ad1287f59cded991b431042;
SGT;

INVALID
INVALID

CALLER;
SWAP14;
DUP2;

INVALID

DUP15;
TSTORE;

INVALID;

SMOD;

INVALID;

SWAP1;
PUSH10 0x2864736f6c634300081a; 
STOP; 
CALLER;