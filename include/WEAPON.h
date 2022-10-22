#include "MASTER.h"
class WEAPON
{
    public:
        int Damage;
        int FireRate;
        int EnergyCost;

        WEAPON();
        void setWeaponStat();
    private:
        std::map<std::string, int> GunType;
        void setGunType();
};