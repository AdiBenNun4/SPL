#include "Agent.h"
#include "SelectionPolicy.h"
#include "Graph.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy) , mCoalition(agentId)
{
    // original constructor
    //  You can change the implementation of the constructor, but not the signature!
}

//semi copy constructor
Agent::Agent( Agent *other, int partyId, Simulation &sim) :mAgentId(), mPartyId(partyId), mSelectionPolicy(other->mSelectionPolicy->clone()), mCoalition(other->mCoalition)
{
    mAgentId = makeAgentID(sim);
    sim.addAgent(*this);
    sim.addToCoalition(mCoalition, mPartyId);
}

// destructor
Agent::~Agent()
{
   if (mSelectionPolicy) delete mSelectionPolicy;
}

// copy constructor
Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(), mCoalition(other.mCoalition)
{
    mSelectionPolicy= other.mSelectionPolicy->clone();
}

// move constructor
Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(), mCoalition(other.mCoalition)
{
    mSelectionPolicy= other.mSelectionPolicy->clone();
}

// assignment operator
Agent &Agent::operator=(const Agent &other)
{
    if (this != &other)
    {
        mAgentId=other.mAgentId;
        mPartyId=other.mPartyId;
        mSelectionPolicy= other.mSelectionPolicy->clone();
        mCoalition=other.mCoalition;
    }
    return *this;
}

// move assignment operator
Agent &Agent::operator=(Agent &&other)
{
   if (mSelectionPolicy)
      delete mSelectionPolicy;
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
    mCoalition = other.mCoalition;
    return *this;
}

int Agent::makeAgentID(const Simulation simulation)
{
    return (simulation.getAgents()).size();
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalition()
{
    return mCoalition;
}

void Agent::step(Simulation &sim)
{
    int selectedPartyID = mSelectionPolicy->select(mCoalition, mPartyId, sim);
    if (selectedPartyID!=-1)
    {
        Party *p = sim.getParty(selectedPartyID);
        p->getOffers(*this); 
    }
}