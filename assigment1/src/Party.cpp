#include "Party.h"
#include "JoinPolicy.h"
#include "Agent.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), timer(0) ,offers(), recievedFromCoalitions()
{
}

// destructor
Party::~Party()
{
    if(mJoinPolicy) delete mJoinPolicy;
}

// copy constructor
Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(), mState(other.mState), timer(other.timer), offers(other.offers), recievedFromCoalitions(other.recievedFromCoalitions)
{
    mJoinPolicy=other.mJoinPolicy->clone();
}

// move constructor
Party::Party(Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(), mState(other.mState), timer(other.timer), offers(other.offers), recievedFromCoalitions(other.recievedFromCoalitions)
{
    mJoinPolicy=other.mJoinPolicy->clone();
}

// assignment operator
Party &Party::operator=(const Party &other) 
{
    if (this != &other)
    {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        if(mJoinPolicy) delete mJoinPolicy;
        mJoinPolicy=other.mJoinPolicy->clone();
        mState = other.mState;
        timer = other.timer;
        offers = other.offers;
        recievedFromCoalitions = other.recievedFromCoalitions;
    }
    return *this;
}

// move assignment operator
Party &Party::operator=(Party &&other)
{
    if (mJoinPolicy) delete mJoinPolicy;
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;
    mState = other.mState;
    timer = other.timer;
    offers = other.offers;
    recievedFromCoalitions = other.recievedFromCoalitions;
    return *this;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string &Party::getName() const
{
    return mName;
}

int Party::getTimer() const
{
    return timer;
}

void Party::step(Simulation &s)
{
    if (mState != Joined)
    {
        if (mState == CollectingOffers)
        {
            if (timer < 2)
                timer++;
            else
            {
                mState = Joined;
                int agentID = mJoinPolicy->Join(s,offers); 
                Agent *a = s.getAgent(agentID);
                Agent(a, mId ,s);
            }
        }
    }
   
}

void Party::getOffers(Agent &a)
{
    mState = CollectingOffers;
    int coalitionId=a.getCoalition();
    if ((int)recievedFromCoalitions.size() <= coalitionId)
    {
        for(int i=recievedFromCoalitions.size() ; i<=coalitionId ;i++)
            recievedFromCoalitions.push_back(false);
    } 
    if(recievedFromCoalitions[coalitionId] != true)    
    {
        offers.push_back(a.getId());
        recievedFromCoalitions[coalitionId] = true;
    }
}

bool Party::gotOfferFromCoalition(int coalitionId)
{
     if ((int)recievedFromCoalitions.size() <= coalitionId)
    {
        for(int i=recievedFromCoalitions.size() ; i<=coalitionId ;i++)
            recievedFromCoalitions.push_back(false);
    } 
        return recievedFromCoalitions[coalitionId];
    
}





