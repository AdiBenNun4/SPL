#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"
#include "Parser.h"
using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;
    void addAgent(Agent);
    void addToCoalition(int coalition, int partyID);
    int getCoalitionMandates(int coalition);

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const; 
    const Party &getParty(int partyId) const;
    Party* getParty(int partyId);
    const vector<vector<int>> getPartiesByCoalitions() const;
    const Agent & getAgent(int agentID) const;
    Agent * getAgent(int agentID);

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<vector<int>> coalitions;
};
