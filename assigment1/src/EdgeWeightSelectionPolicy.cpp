#include <string>
#include "SelectionPolicy.h"
#include "Simulation.h"

using std::string;
int EdgeWeightSelectionPolicy::select(int coalition, int myPartyID, Simulation &sim) 
{
Graph g = sim.getGraph();
int numOfParties = g.getNumVertices();
int edgeWeightMax = 0;
int selectedPartyID = -1;
for (int id = 0; id < numOfParties; id++)
{
    Party *party = g.getParty(id);
    State partyState = party->getState();
    bool gotOffer = party->gotOfferFromCoalition(coalition);
    int weight = g.getEdgeWeight(myPartyID, id);
    if (weight > edgeWeightMax && partyState != Joined && gotOffer == false) 
    {
        selectedPartyID = id;
        edgeWeightMax = weight;
    }
}
return selectedPartyID;
}

EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::clone(){
    EdgeWeightSelectionPolicy* sp=new EdgeWeightSelectionPolicy();
    return sp;
}
