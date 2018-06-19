//Cracked by Roath
// cimu.c 辟邪剑法「刺腕」之技
// wzfeng@XKX 99 9 

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "pixie_superskill.c"

void remove_effect(object target,int parry_skill);



int perform(object me, object target)
{
        string msg,perform_name;
		
        object weapon;
		
		
        int  ap, dp,ciwan_busy,attack_skill,parry_skill;
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「刺腕」之技只能在战斗中对敌人使用。\n");
		if(!living(target))
			return notify_fail("对付昏迷的人还需「刺腕」?\n");


        if( (int)target->query_temp("pixie/ciwan") )
                return notify_fail("你已刺中敌人双手要害！\n");

        if( me->query("neili") <= 300 )
                return notify_fail("你的内力不够！\n");

        if( me->query("jingli") <= 300 )
                return notify_fail("你的精力不够！\n");


        if( !objectp(weapon = me->query_temp("weapon")) )
                 return notify_fail("空手如何「刺腕」？？\n");

/*        if( (string)weapon->query("id") != "xiuhua zhen" && 
            (string)weapon->query("id") != "qijue zhen" )
                 return notify_fail("你没有趁手的兵器，不能施展「刺腕」绝技。\n");
*/
        if( ( (int)me->query_skill("pixie-jian", 1)) < 120 )
                return notify_fail("你的辟邪剑法不够娴熟，无法使出「刺腕」。\n");

		if( (string)me->query_skill_mapped("dodge") != "pixie-jian" )
                return notify_fail("你没有将辟邪剑法运在身法上，很难接近对手。\n");	
		
        //if( !target->is_killing(me->query("id")) ) target->kill_ob(me);
		perform_name="pixie-ciwan";

		ap = me->query_skill("sword");
		dp = target->query_skill("dodge");
		if(me->query("dex")>19)
		{
			ap+=ap;
		}
		if(me->query("combat_exp")<(target->query("combat_exp")/3))
			ap=1;

		weapon = me->query_temp("weapon");
		msg="";
		parry_skill=target->query_skill("parry");
		if(parry_skill<=0)
			parry_skill=0;

		//根据身法的高低来决定刺腕的时间。
		if(me->query("dex")>22&&me->query("dex")>target->query("dex"))
			ciwan_busy=me->query_dex();
		else
			ciwan_busy=me->query_dex()/2;

		//do super perform
		if(!do_prepare_superskill(perform_name,me,target,ap,dp))
		
		{
		    if(target->query_temp("pixie/cimu"))
		 {
			msg = HIB "\n趁$n双目失明之时，$N一声奸笑，使出辟邪剑法「刺腕」之技。\n"NOR;
			ap=ap+random(ap);
		}
		
                    if(me->query_temp("pixie/guimei") >0 )
                    {
                    msg += HIB "$N的身影犹如鬼魅一般，刹那间变得灵幻异常。\n"NOR;
                    ap=ap+random(ap);
                    }
                    
			msg += HIB "$N腰肢一摆，身影晃动，刹那见来到$n身前，双手闪电般递出，急刺$n手腕要害。\n"NOR;
		if( wizardp(me) &&me->query("env/pixie_test"))
		{
				printf(HIC"ap=%d\tdp=%d\n"NOR,ap,dp);
				printf(HIC"ciwan_busy=%d\n"NOR,ciwan_busy);
		}

        if( random(ap+dp) < dp )
        {
                msg += HIG"$p脸色微变，双手急收，有惊无险的避开这一招。\n" NOR;
	            me->start_busy(1 + random(1));

				me->delete_temp("pixie_performtime");

        }
        else
			if(!target->query_temp("pixie/cimu")
				&&random(target->query_temp("pixie_times/ciwan"))>1+random(10)
				&&random(target->query_int())>random(me->query_int()))
				{
				msg += HIG"$p先前已见过此招，心中略有防备，双手巧劲暗用，隔开这一招。\n" NOR;
				me->start_busy(1 + random(1));
				me->delete_temp("pixie_performtime");

				}
			else
			{
				if(target->query_temp("pixie/cimu"))
					{
					msg += HIR "\n$n知觉身前劲风扑来，知道大事不秒，惊慌中只觉手腕一痛，已然被刺中。\n"NOR;	
					}
				else
					{
					msg += HIR"$p大吃一惊，惊慌中不知如何是好，但觉手腕一痛，已然被刺中。\n" NOR; 
					}
					target->add_temp("apply/parry",  -parry_skill);
					target->set_temp("pixie/ciwan",1);
					target->set_temp("cannot_perform",1);
					target->set_temp("cannot_perform_msg","你双手要害被刺中，无法施用外功。");
					target->add_temp("pixie_times/ciwan",1 );
					target->add("eff_qi",-(random((int)me->query_skill("pixie-jian"))*4/3));
                    if( userp(me) )
					{
					target->set_temp("ciwan_power", parry_skill);
                    target->apply_condition("b_ciwan",1+(int)(ciwan_busy/15));
					
					}
					else
  	                me->start_call_out( (: call_other, __FILE__, "remove_effect", target, parry_skill :), ciwan_busy);


					set_perform(me,perform_name);
   				    me->set_temp("pixie_performtime",5);
					me->start_busy(1 + random(2));


			}
		}

					if(!me->query_temp("pixie_noop"))
					call_out("checking_pixieflg", 1, me, target);
					
					me->add("neili", -50);
					me->add("jingli", -50);
					message_vision(msg, me, target);
                  return 1;
}
void remove_effect(object target,int parry_skill)
{
		        if( !target ) return;
			target->add_temp("apply/parry",  parry_skill);
			target->delete_temp("pixie/ciwan");
			target->delete_temp("pixie_times/ciwan");
			target->delete_temp("cannot_perform");
			target->delete_temp("cannot_perform_msg");

	        if(target->is_fighting() )
			{
			target->start_busy(1 + random(1));
			message_vision(HIG"$N冲开手腕穴道，双手行动逐渐恢复正常。\n"NOR,target );
			}
}
			