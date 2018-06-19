//Cracked by Roath
inherit NPC;
int auto_perform();
int ask_me();

void create()
{
	set_name("南海鳄神", ({ "nanhai eshen", "eshen"}));
	set("nickname", "凶神恶煞");
	set("long", 
"此人的一个脑袋大得异乎寻常，一张阔嘴中露出白森森的利齿，一对眼睛却是又圆又小。\n");
	set("gender", "男性");
	set("age", 45);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 1500);
	set("max_jing",1000);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 50);
	set("combat_exp", 700000);
	set("env/wimpy", 40);
	set_temp("apply/armor", 70);
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: auto_perform :),
                "南海鳄神说道：他妈的，哪个敢不听老子的话，被老子揪住，喀嚓一下扭断了他的脖子。\n",
                "南海鳄神突然发怒大声道：”老子是岳老二，不是岳老三！\n",
		"南海鳄神突然小眼中光芒四射，向你脸上骨碌碌一转，你不由得打了个寒战。\n", 
        }) );

 set("inquiry", ([
	"测试" : (: ask_me :),
	"测试武功" : (: ask_me :),
        ]));

	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("ding-dodge", 150);
	set_skill("ding-force", 150);
	set_skill("ding-unarmed", 150);
	set_skill("strike", 150);
	set_skill("blade", 150);
	set_skill("canglang-bian", 150);
	set_skill("luan-blade", 150);
	set_skill("whip", 150);

	map_skill("dodge", "ding-dodge");
	map_skill("blade", "luan-blade");
	map_skill("parry", "luan-blade");
        map_skill("force", "ding-force");
	map_skill("whip", "canglang-bian");
        map_skill("unarmed", "ding-unarmed");

	setup();
	switch( random(2) )
        {
                case 0:
                         if (clonep()) carry_object("/clone/unique/eweibian", "/clone/weapon/changbian")->wield();
			 if (clonep()) carry_object("/clone/unique/eyujian", "/clone/weapon/gangdao");
                         break;
                case 1:
                         if (clonep()) carry_object("/clone/unique/eyujian", "/clone/weapon/gangdao")->wield();
			 if (clonep()) carry_object("/clone/unique/eweibian", "/clone/weapon/changbian");
			 break;
        }
	carry_object("/d/city/obj/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_accept", "accept");
}


int auto_perform()
{
        object me = this_object();
        object target = me->select_opponent();
        object weapon = me->query_temp("weapon");

        if ( !objectp(target)
          || !random( (int)me->query("combat_exp") * 2
                   / (int)target->query("combat_exp") + 1) ) return 0;

        if ( objectp(weapon) ) {
                if ( weapon->query("skill_type") == "blade" )
	command("cut " + target->query("id"));
	return;
	}
}

int ask_me()
{
object me=this_player();
if ((int)me->query_temp("marks/西夏nan")) 
	{	
say("南海鳄神狂笑了一阵：你要是不怕死，就试试(accept test)，看老子不拧断了你的脖子？\n");
	return 1;
	}
/* else	{
	say("南海鳄神怒喝道：滚，老子心烦，不滚看老子一下拧断你的脖子！\n");
	return 1;
	}
*/
}

int do_accept(string arg)
{
        mapping guild;
	object me=this_player();
if (!(int)me->query_temp("marks/西夏nan")) 
return notify_fail ("你瞎试什么？\n");
        

        if( arg== "test" ) {
                say("\n南海鳄神点了点头，说道：很好，这是第一招....\n\n");
                COMBAT_D->do_attack(this_object(), this_player(),
query_temp("weapon"));
COMBAT_D->do_attack(this_object(), this_player(),
query_temp("weapon"));

                if( (int)this_player()->query("qi") < 0 
                || !present(this_player(), environment())) {

say("南海鳄神叹了口气，说道：连第一招都撑不过，真是自不量力....\n");
                        return 1;
                }
                say("\n南海鳄神说道：这是第二招....\n\n");
                COMBAT_D->do_attack(this_object(), this_player(),
query_temp("weapon"));
COMBAT_D->do_attack(this_object(), this_player(),
query_temp("weapon"));

                if( (int)this_player()->query("qi") < 0 
                || !present(this_player(), environment())) {

say("南海鳄神「哼」地一声，说道：便是有这许多不怕死的家伙....\n");
return 1;
                }
                say("\n南海鳄神说道：第三招来了....\n\n");
                COMBAT_D->do_attack(this_object(), this_player(),
query_temp("weapon"));
		COMBAT_D->do_attack(this_object(), this_player(),
query_temp("weapon"));

                if( (int)this_player()->query("qi") < 0 
                || !present(this_player(), environment())) {

say("南海鳄神叹道：可惜，没拧断这个龟儿子的脖子....\n");
                        return 1;
                }

say("\n南海鳄神睁大了一双怪眼说道：他妈妈的．．．！\n\n");
                this_player()->set_temp("xixia/testpass", 2);
                this_player()->delete_temp("marks/西夏nan");
		return 1;
        }
        return 0;
}

