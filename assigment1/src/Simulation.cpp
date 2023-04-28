#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) , coalitions()
{
    for (Agent &a:agents)
    {
        coalitions.push_back( vector <int> {a.getPartyId()});
    }
    
}

void Simulation::step()
{
    int numOfParties = mGraph.getNumVertices();
    for (int id = 0; id < numOfParties; id++) 
    {
        Party *party = mGraph.getParty(id);
        party->step(*this);
    }

    for (Agent a : mAgents)
    {
        a.step(*this); 
    }
}

bool Simulation::shouldTerminate() const
{
    int mandatesTotal = 0;
    for (int i=0; i <(int) coalitions.size(); i++)
    {
        int mandatesCurrent = 0;
        for (int j=0; j <(int) coalitions[i].size(); j++)
        {
            int partyMandates = mGraph.getMandates(coalitions[i][j]);
            mandatesTotal += partyMandates;
            mandatesCurrent += partyMandates;
            if (mandatesTotal == 120 || mandatesCurrent > 60)
                return true;
        }
    }
    return false;
}

void Simulation::addAgent(Agent agent)
{
    mAgents.push_back(agent);
}

void Simulation::addToCoalition(int coalition, int partyID)
{
    coalitions[coalition].push_back(partyID);
}

int Simulation::getCoalitionMandates(int coalition)
{
    int mandates = 0;
    for (int i = 0; i <(int) coalitions[coalition].size(); i++)
    {
        mandates += mGraph.getMandates(coalitions[coalition][i]);
    }
    return mandates;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party* Simulation::getParty(int partyId){
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    return coalitions;
}

const Agent &Simulation::getAgent(int agentID) const
{
    return mAgents[agentID];
}

 Agent *Simulation::getAgent(int agentID) 
{
    return &mAgents[agentID];
}







