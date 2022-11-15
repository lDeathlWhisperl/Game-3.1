#pragma once

#include "Skeleton.h"
#include "Zombie.h"
#include "Draugr.h"

#include "Imp.h"
#include "Possessed.h"
#include "Mancubus.h"

#include "Mummy.h"
#include "Gin.h"
#include "Ghoul.h"

class Spawner
{
public:
	virtual Undead* spawn_undead() = 0;
	virtual Demon* spawn_demon() = 0;
	virtual Spirit* spawn_spirit() = 0;
};