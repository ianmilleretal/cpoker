#ifndef _PLAYER_COMPOSE_TURNIN
#define _PLAYER_COMPOSE_TURNIN





class _Player_Compose_Turnin : public _Count_Payoffs_Player
{
private:
    //Strategies for composing turn-ins: e.g. ABG = Alpha, Beta, Gamma
    enum class Strat {ABG=0, AGB, BAG, BGA, GAB, GBA};

protected:
    Strat _strategy;


public:
    _Player_Compose_Turnin() : _Count_Pyaoffs_Player() {}
    _Player_Compose_Turnin(Deck* dck) : _Count_Payoffs_Player(dck) {}

    
    



#endif
