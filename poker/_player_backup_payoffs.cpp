#include "_player_backup_payoffs.hpp"


void _Backup_Payoffs_Player::_backup()
{
    for (int i=0; i < this->_num_payoffs_ab; i++) {
        this->_backup_ab[i] = this->_payoffs_ab[i];
    }
    this->_num_backups_ab = this->_num_payoffs_ab;

    for (int i=0; i < this->_num_payoffs_ga; i++) {
        this->_backup_ga[i] = this->_payoffs_ga[i];
    }
    this->_num_backups_ga = this->_num_payoffs_ga;
}
