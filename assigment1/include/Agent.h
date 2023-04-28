#pragma once

#include <vector>
#include "Graph.h"
#include "Simulation.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent( Agent *other,int partyId, Simulation &sim);
    virtual ~Agent();
    Agent(const Agent &other);
    Agent(Agent&& other);
    Agent& operator=(const Agent& other);
    Agent& operator=(Agent&& other);
    int getPartyId() const;
    int getId() const;
    int getCoalition() ;
    void step(Simulation &);
    int makeAgentID(const Simulation simulation);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mCoalition;
};
