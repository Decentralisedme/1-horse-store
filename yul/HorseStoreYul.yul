object "HorseStoreYul" {
    code{
        // Contract deployment
        datacopy(0, dataoffset("runtime"), datasize("runtime"))
        // slot =0 / start at runtime obj / copy for the entire size 
        return(0, datasize("runtime"))
        // we put the runtime code on chain
    }
    object "runtime" {
        code{}
    }
}