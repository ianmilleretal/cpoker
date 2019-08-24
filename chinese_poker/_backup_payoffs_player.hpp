#ifndef _BACKUP_PLAYER
#define _BACKUP_PLAYER


#include "../card_cons.hpp"
#include "_count_payoffs_player.hpp"
#include "deck.hpp"


class _Backup_Payoffs_Player : public _Count_Payoffs_Player
{
protected:
    bool _is_backup;
    int _num_backups;
    int _num_backups_3c;
    Payoff* _backups[_Count_Payoffs_Player::BINOMIAL_13_5];
    Payoff* _backups_3c[_Count_Payoffs_Player::BINOMIAL_13_5];



public:
    _Backup_Payoffs_Player() :
        _is_backup(false),
        _num_backups(0),
        _num_backups_3c(0),
        _Count_Payoffs_Player() {}
    _Backup_Payoffs_Player(Deck* pdeck) :
        _is_backup(false),
        _num_backups(0),
        _num_backups_3c(0),
        _Count_Payoffs_Player(pdeck) {}

    void _backup();

    Payoff** get_backups()
        {return this->_backups;}
    int get_num_backups()
        {return this->_num_backups;}
    Payoff** get_backups_3c()
        {return this->_backups_3c;}
    int get_num_backups_3c()
        {return this->_num_backups_3c;}
};


#endif
