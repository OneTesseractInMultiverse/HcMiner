//
// Created by Pedro Guzman on 7/4/17.
//

#ifndef HC_MINER_ABSTRACTMINER_H
#define HC_MINER_ABSTRACTMINER_H
/*
 * -----------------------------------------------------------------------
 * INCLUDE HEADERS
 * -----------------------------------------------------------------------
 */
#include <thread>
#include <string>
#include "MiningContext.h"

// =======================================================================
// CLASS ABSTRACT MINER
// =======================================================================
/**
 * Defines a base class that must be implemented by any performance data mining
 * agent. Extending this class provides the ability
 */
class AbstractMiner{
public:

    // -------------------------------------------------------------------
    // METHOD SET CONTEXT
    // -------------------------------------------------------------------
    /**
     * Sets the handle to the context
     * @param context A handle to the mining context that provides access to
     */
    void setContext(MiningContext* context){
        this->_context = context;
    } // METHOD SET CONTEXT ENDS -----------------------------------------

    // -------------------------------------------------------------------
    // METHOD RUN
    // -------------------------------------------------------------------
    /**
     * Starts the logic implemented here on child classes on a new thread
     */
    virtual void run() = 0;

    // -------------------------------------------------------------------
    // METHOD SPAWN
    // -------------------------------------------------------------------
    /**
     * Starts running logic implemented by run() method ins separate thread
     * and returns the new thread.
     * @return The new thread that where logic implemented by run() method
     *          is now contained.
     */
    std::thread spawn(){
        return std::thread(&AbstractMiner::run, this);
    } // METHOD SPAWN ENDS -----------------------------------------------
protected:
    MiningContext* _context;
}; // CLASS ABSTRACT MINER ENDS ------------------------------------------

#endif //HC_MINER_ABSTRACTMINER_H
