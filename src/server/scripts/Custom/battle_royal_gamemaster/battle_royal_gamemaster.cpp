//
// Created by Alex Boyd on 2019-08-04.
//
#include "ScriptMgr.h"
#include "ObjectAccessor.h"
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellInfo.h"

class npc_battle_royal_gamemaster : public CreatureScript
{
public:
    npc_battle_royal_gamemaster() : CreatureScript("npc_battle_royal_gamemaster") {}

    struct npc_battle_royal_gamemasterAI : public ScriptedAI
    {
        explicit npc_battle_royal_gamemasterAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }

        void Restart()
        {
            Initialize();
        }

        void Initialize()
        {
            me->Yell("The battle royal will begin in 1 minute!", LANG_UNIVERSAL);
        }

        void UpdateAI(uint32 diff) override
        {

        }

    private:
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_battle_royal_gamemasterAI(creature);
    }
};

void AddSC_battle_royal_gamemaster()
{
    new npc_battle_royal_gamemaster();
}
