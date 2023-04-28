#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
using std::string;

class JoinPolicy;
class Simulation;
class Agent;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    virtual ~Party();
    Party(const Party &other);
    Party(Party&& other);
    Party& operator=(const Party& other);
    Party& operator=(Party&& other);
    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    int getTimer()const;
    void getOffers(Agent &);
    bool gotOfferFromCoalition (int coalitionId);
    
private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    vector <int> offers;
    vector <bool> recievedFromCoalitions;
};
