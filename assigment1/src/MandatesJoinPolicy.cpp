#include <string>
#include "JoinPolicy.h"
#include "Simulation.h"
using std::string;

      int MandatesJoinPolicy:: Join(Simulation &sim,  vector<int> & offers) 
    {
        int maxMandates=0;
        int agentIdMaxM=-1;
        for (int i=0 ; i< (int) offers.size(); i++){
        int currAgentID=offers[i];
        int agentMandates=sim.getCoalitionMandates(sim.getAgent(currAgentID)->getCoalition());
        if(agentMandates>maxMandates) {
                maxMandates=agentMandates;
                agentIdMaxM=currAgentID;
        }
        }
        return agentIdMaxM;
    }

    MandatesJoinPolicy* MandatesJoinPolicy::clone(){
      MandatesJoinPolicy* jp=new MandatesJoinPolicy();
       return jp;
    }





