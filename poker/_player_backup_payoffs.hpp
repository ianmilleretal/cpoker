#ifndef _BACKUP_PLAYER
#define _BACKUP_PLAYER


#include "../card_cons.hpp"
#include "_player_count_payoffs.hpp"
#include "deck.hpp"


class _Backup_Payoffs_Player : public _Count_Payoffs_Player
{
protected:
    bool _is_backup;
    int _num_backups_ab;
    int _num_backups_ga;
    Payoff* _backup_ab[_Count_Payoffs_Player::BINOMIAL_13_5];
    Payoff* _backup_ga[_Count_Payoffs_Player::BINOMIAL_13_5];



public:
    _Backup_Payoffs_Player() :
        _is_backup(false),
        _num_backups_ab(0),
        _num_backups_ga(0),
        _Count_Payoffs_Player() {}
    _Backup_Payoffs_Player(Deck* pdeck) :
        _is_backup(false),
        _num_backups_ab(0),
        _num_backups_ga(0),
        _Count_Payoffs_Player(pdeck) {}

    void _backup();

    Payoff** get_backup_ab()
        {return this->_backup_ab;}
    Payoff** get_backup_ga()
        {return this->_backup_ga;}
    int get_num_backups_ab()
        {return this->_num_backups_ab;}
    int get_num_backups_ga()
        {return this->_num_backups_ga;}
};


#endif
