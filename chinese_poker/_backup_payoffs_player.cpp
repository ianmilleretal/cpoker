#include "_backup_payoffs_player.hpp"


void _Backup_Payoffs_Player::_backup()
{
    for (int i=0; i < this->_num_payoffs; i++) {
        this->_backups[i] = this->_payoffs[i];
    }
    this->_num_backups = this->_num_payoffs;

    for (int i=0; i < this->_num_payoffs_3c; i++) {
        this->_backups_3c[i] = this->_payoffs_3c[i];
    }
    this->_num_backups_3c = this->_num_payoffs_3c;
}
