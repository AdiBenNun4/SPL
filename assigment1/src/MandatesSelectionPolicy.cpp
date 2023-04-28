#include <string>
#include "SelectionPolicy.h"
#include "Simulation.h"

using std::string;

 int MandatesSelectionPolicy::select(int coalition, int myPartyID, Simulation &sim) 
{
    Graph g = sim.getGraph();
    int numOfParties = g.getNumVertices();
    int mandatesMax = 0;
    int selectedPartyID = -1;

    for (int id = 0; id < numOfParties; id++)
    {
        Party *party = g.getParty(id);
        State partyState = party->getState();
        bool gotOffer=party->gotOfferFromCoalition(coalition);
        int mandates = g.getMandates(id);
        int weight = g.getEdgeWeight(myPartyID, id);
        if (mandates > mandatesMax && weight > 0 && partyState != Joined && gotOffer==false)
        {
            selectedPartyID = id;
            mandatesMax = mandates;
        }
    }
    return selectedPartyID;
}

MandatesSelectionPolicy* MandatesSelectionPolicy::clone(){
    MandatesSelectionPolicy* sp=new MandatesSelectionPolicy();
    return sp;
}



