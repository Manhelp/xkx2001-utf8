//Cracked by Roath
// wugou-jianfa.c 吴钩剑法

inherit SKILL;

mapping *action = ({
([     "action" : "$N突然夸步向前，一招「十步杀一人」，手中$w向$n的$l劈出",
       "force" : 120,
       "dodge" : 20,
       "damage" : 5,
        "lvl" : 0,
        "damage_type":  "割伤"
]),
([     "action" : "$N身子往下一矮身，同时一挥手中$w，一招「脱剑膝前横」，向$n的$l横劈而出",
       "force" : 120,
       "dodge" : 20,
       "damage" : 5,
        "lvl" : 9,
        "damage_type":  "割伤"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
       return 1;
}

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];

}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "sword")
               return notify_fail("你使用的武器不对。\n");
	 if ((int)me->query_skill("wugou-jianfa", 1) >= 30)
		return notify_fail("你的吴钩剑法已经无法再用练来提高了。\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("你的精力不够练吴钩剑法。\n");
       me->receive_damage("jingli", 30);
       return 1;
}
int valid_combine(string combo) 
{ 	if (strsrch(combo, "xiake") >= 0) 
		return 1;
	else
		return 0;
}
