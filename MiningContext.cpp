//
// Created by Pedro Guzman on 7/4/17.
//

#include "MiningContext.h"

// -----------------------------------------------------------------------
// METHOD IS RUNNING
// -----------------------------------------------------------------------
/**
 * Gets if current mining context is running or not. This method is used by
 * multiple mining threads to determine if they should run or stop running.
 * @return true if runnning or false is stopped.
 */
bool MiningContext::isRunning() {
    return this->_isRunning;
} // METHOD IS RUNNING ENDS ----------------------------------------------

// -----------------------------------------------------------------------
// METHOD INIT
// -----------------------------------------------------------------------
/**
 * Sets the mining context to run so that mining threads can run their mining
 * agents.
 */
void MiningContext::init() {
    this->_isRunning = true;
} // METHOD INIT ENDS ----------------------------------------------------

// -----------------------------------------------------------------------
// METHOD STOP
// -----------------------------------------------------------------------
/**
 * Sets a signal in the context to tell all running agents, that mining
 * context has finished so execution must be ended.
 */
void MiningContext::stop() {
    this->_isRunning = false;
} // METHOD STOP ENDS ----------------------------------------------------
