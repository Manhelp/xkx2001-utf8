//Cracked by Roath
// pojian.c 独孤九剑「破鞭式」
// qfy July 5, 1996.

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("破鞭式只能对战斗中的对手使用。\n");

	if( !objectp(weapon = target->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "hammer" ) {
	   if( !objectp(weapon = target->query_temp("weapon"))
	   || (string)weapon->query("skill_type") != "axe" )
		return notify_fail("破鞭式只能对用钢鞭、槌、锤、锥和斧的对手使用。\n");
	}

	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
		
	if( (int)me->query_skill("dugu-jiujian", 1) < 50 )
		return notify_fail("你的独孤九剑修为不够，还未学成「破鞭式」。\n");

        if( me->query("neili") <= 100 )
                return notify_fail("你的内力不够！\n");

	msg = CYN "$N使出独孤九剑的「破鞭式」，剑化流星，迅急无比地点向$n的手腕。\n";

	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2 ) {
		msg += "结果$p被$P攻了个措手不及，唯有舍弃"+weapon->query("name")+"以期自保。\n" NOR;
		weapon->move(environment(me));
		target->start_busy( (int)me->query_skill("sword") / 28 );
	} else {
		msg += "可是$p看破了$P的剑路，还招挡开。\n" NOR;
		me->start_busy(1 + random(3));
	}
	message_vision(msg, me, target);
	me->add("neili", -25);
	me->add("jingli", -10);

	return 1;
}
