#include <string>
#include "JoinPolicy.h"
#include "Simulation.h"
using std::string;

int LastOfferJoinPolicy::Join(Simulation &sim, vector<int> &offers) 
{
    return offers[offers.size()-1];
}

LastOfferJoinPolicy* LastOfferJoinPolicy::clone(){
    LastOfferJoinPolicy* jp=new LastOfferJoinPolicy();
    return jp;
}
