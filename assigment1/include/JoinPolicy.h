#pragma once
#include <string>
#include <vector>
class Simulation;

using std::string;
using std::vector;


class JoinPolicy {
        public:
             virtual int Join( Simulation &, vector <int> &)=0;
             virtual ~JoinPolicy(){};
             virtual JoinPolicy* clone()=0;
};

class MandatesJoinPolicy : public JoinPolicy {    
        public:
                 int Join( Simulation &, vector <int> &) override;
                 MandatesJoinPolicy* clone() override;

};

class LastOfferJoinPolicy : public JoinPolicy {   
        public:
                 int Join( Simulation &, vector <int> &) override ;
                 LastOfferJoinPolicy* clone() override; 

};