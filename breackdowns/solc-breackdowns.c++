// 0x6080604052348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea264697066735822122011b56db01e1ad1287f59cded991b43104213badb339d81e88e5d1f07f690692864736f6c634300081a0033
// go to Playground / Memonic

/*
We know there ae 3 sections;
1. Creation Creation
2. Runtime
3. Metadata
*/
// --- 1. Creation Creation
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

// --- 2. Runtimne Code: 6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea264697066735822122011b56db01e1ad1287f59cded991b43104213badb339d81e88e5d1f07f690692864736f6c634300081a0033
// 2.a Free Memoery Pointer 
PUSH1 0x80; // 60 0x80 //   [0x80]
PUSH1 0x40; // 60 0x40 //   [0x40,0x80]
MSTORE;     // 53 //        [] >> set free memory pointer

// 2.b 
CALLVALUE;  // 34 //        [msg.value] // msg.value == 0
DUP1;       // 80 //        [msg.value, msg.value]
ISZERO;     // 15 //        [msg.value ==0, msg.value, msg.value] // yes it is zer >> 1 in the stuck
PUSH1 0x0e; // 60 0x0e //   [0x0e, msg.value ==0?, msg.value] // need to tell where to jump PC
JUMPI;      // 57 //        [msg.value]  // If 1>> Jump to 0x0e JUMPDEST, (here=1=we jump)
PUSH0;      // 5f //        [0x00, msg.value]
DUP1;       // 80 //        [0x00, 0x00, msg.value]
REVERT;     // fd //        [msg.value]

// JumpDest = 0x0e when msg.value==0 >> true =1 JUMP if 1 to JUMPDEST
// This checks if there is enough data for Function_Selector, the least is 0x04 (8bites), if is less (LT) >> Jump 
JUMPDEST;   // 5B //        [msg.value] >> Value before JUMPI
POP;        // 50 //        []
PUSH1 0x04; // 60 0x40 //   [0x40] 
CALLDATASIZE; // 36 //      [colldata_size, 0x40]
LT;          // 10 //       [colldata_size < 0x40] compare if a<b then 1 (true)
PUSH1 0x30;  // 60 0x30 //  [0x30, colldata_size < 0x40]
JUMPI;       // 57 //       [] >> Jump if condition colldata_size < 0x40 is true (1): Ifa calldata is small we jump
// If calldata_size <0x04 (means no function to select) then >>>> calldata_jump to 0x30

// Function Dispacher in SOL / funciton selector for UpdateNumbOfHorses
PUSH0;       // 5f //       [0x00]
CALLDATALOAD;// 35 //       [32bytes of calldata]      
PUSH1 0xe0;  // 60 e0 //    [0xe0, 32bytes of calldata]
SHR;         // 1C //       [calldata[0:4]] ?? we have selected the function
DUP1;        // 80 //       [calldata[0:4], calldata[0:4]]    
PUSH4 0xcdfead2e; // 63 cdfead2e // [0xcdfead2e, calldata[0:4], calldata[0:4]] Push 4 bytes, whihc is our fucntion
EQ;          // 14 //            [0xcdfead2e==calldata[0:4],calldata[0:4]]
PUSH1 0x34; // 60 34 //          [0x34, 0xcdfead2e==calldata[0:4], calldata[0:4]]
JUMPI;      // 57 //             [calldata[0:4]]    if calldata[0:4] = 0xcdfead2e >> JUMP 0x34 (updateNumberOfHorses) JUMP to Progrm Counter 0x034

// Funct Selector for readNumbOfHorse
DUP1;       // 80 //            [calldata[0:4],calldata[0:4]] >> in Huff we do not do DUP again
PUSH4 0xe026c017; // 63 e026c017 // [0xe026c017,calldata[0:4],calldata[0:4]]
EQ;         // 14 //                [0xe026c017==calldata[0:4],calldata[0:4]]
PUSH1 0x45; // 60 45 //         //  [0x045, 0xe026c017==calldata[0:4],calldata[0:4]]
JUMPI;       // 57 //           [calldata[0:4]]  if calldata[0:4] = 0xe026c017 >> JUMP 0x45

// calldata_size < 0x04: ment no function to select,JUMP here where we revert
JUMPDEST;       // 5B //
PUSH0;          // 5f //        // [0x00]
DUP1;           // 80 // [0x00, 0x00]
REVERT;         // fd // []

JUMPDEST;
PUSH1 0x43; 
PUSH1 0x3f; 
CALLDATASIZE;
PUSH1 0x04; 
PUSH1 0x59; 
JUMP;
JUMPDEST
PUSH0
SSTORE
JUMP
JUMPDEST
STOP
JUMPDEST
PUSH0
                                                                                                            SLOAD
                                                                                                                PUSH1 0x40 MLOAD
                                                                                                                    SWAP1
                                                                                                                        DUP2
                                                                                                                            MSTORE
                                                                                                                                PUSH1 0x20 ADD
                                                                                                                                    PUSH1 0x40 MLOAD
                                                                                                                                        DUP1
                                                                                                                                            SWAP2
                                                                                                                                                SUB
                                                                                                                                                    SWAP1
                                                                                                                                                        RETURN
                                                                                                                                                            JUMPDEST
                                                                                                                                                                PUSH0
                                                                                                                                                                    PUSH1 0x20 DUP3
                                                                                                                                                                        DUP5
                                                                                                                                                                            SUB
                                                                                                                                                                                SLT
                                                                                                                                                                                    ISZERO
                                                                                                                                                                                        PUSH1 0x68 JUMPI
                                                                                                                                                                                            PUSH0
                                                                                                                                                                                                DUP1
                                                                                                                                                                                                    REVERT
                                                                                                                                                                                                        JUMPDEST
                                                                                                                                                                                                            POP
                                                                                                                                                                                                                CALLDATALOAD
                                                                                                                                                                                                                    SWAP2
                                                                                                                                                                                                                        SWAP1
                                                                                                                                                                                                                            POP
                                                                                                                                                                                                                                JUMP
                                                                                                                                                                                                                                    INVALID
                                                                                                                                                                                                                                        LOG2
                                                                                                                                                                                                                                            PUSH5 0x6970667358 INVALID
                                                                                                                                                                                                                                                SLT
                                                                                                                                                                                                                                                    KECCAK256
                                                                                                                                                                                                                                                        GT
                                                                                                                                                                                                                                                            INVALID
                                                                                                                                                                                                                                                                PUSH14 0xb01e1ad1287f59cded991b431042 SGT
                                                                                                                                                                                                                                                                    INVALID
                                                                                                                                                                                                                                                                        INVALID
                                                                                                                                                                                                                                                                            CALLER
                                                                                                                                                                                                                                                                                SWAP14
                                                                                                                                                                                                                                                                                    DUP2
                                                                                                                                                                                                                                                                                        INVALID
                                                                                                                                                                                                                                                                                            DUP15
                                                                                                                                                                                                                                                                                                TSTORE
                                                                                                                                                                                                                                                                                                    INVALID
                                                                                                                                                                                                                                                                                                        SMOD
                                                                                                                                                                                                                                                                                                            INVALID
                                                                                                                                                                                                                                                                                                                SWAP1
                                                                                                                                                                                                                                                                                                                    PUSH10 0x2864736f6c634300081a STOP CALLER