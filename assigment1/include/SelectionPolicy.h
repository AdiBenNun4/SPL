#pragma once
#include "Simulation.h"

class SelectionPolicy 
{
    public:
        virtual int select(int coalition, int myPartyID, Simulation &)=0;
        virtual ~SelectionPolicy(){};
        virtual SelectionPolicy* clone()=0;
};

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
      int select(int coalition, int myPartyID, Simulation &) override;
      MandatesSelectionPolicy* clone() override;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
      int select(int coalition, int myPartyID, Simulation &) override;
      EdgeWeightSelectionPolicy* clone() override;
};