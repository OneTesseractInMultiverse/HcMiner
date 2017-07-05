//
// Created by pedro on 7/4/17.
//

#ifndef HC_MINER_MININGCONTEXT_H
#define HC_MINER_MININGCONTEXT_H


class MiningContext {
public:
    bool isRunning();
    void stop();
    void init();

private:
    bool _isRunning;

};


#endif //HC_MINER_MININGCONTEXT_H
