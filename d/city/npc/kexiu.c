//Cracked by Roath
// Jay 5/10/97
// Ryu 11/13/97
//change by wzfeng 99 12
#include <ansi.h>
inherit NPC;
//inherit F_SKILL;

int ask_work(); 
int do_proceed(object who, object ob);

void create()
{
        set_name("李克秀", ({ "li kexiu", "li" }));
        set_color("$YEL$");
        set("title", "水陆提督");
        set("gender", "男性");
        set("age", 43);
        set("str", 20);
        set("dex", 20);
        set("long", "此人精明强干，官运亨通，新任的浙江水陆提督，节制定海、温州等五镇，"
        "统辖提标五营，兼辖扬州等城守协，太湖、海宁等水师营。\n");
        set("combat_exp", 30000);
        set("shen_type", 0);
        set("attitude", "heroism");

        set("inquiry", ([
                "李沅芷" : "她是我女儿。\n",
                "行贿" : "休想对老夫行贿。\n",
                "受贿" : "老夫从不受贿。\n",
                "work" : (: ask_work :),
                "工作" : (: ask_work :),
        ]));

        set_skill("unarmed", 50);
        set_skill("force", 50);
        set_skill("sword", 50);
        set_skill("san-sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        map_skill("parry","san-sword");
        map_skill("sword","san-sword");
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 15);

        set("neili", 500); 
        set("max_neili", 500);
        set("jiali", 10);

        setup();
        carry_object("/clone/armor/junfu")->wear();
        carry_object(__DIR__"obj/gangjian")->wield();
}
private void go_home()
{
	if( !living(this_object()) ) return;
        message_vision("$N神色慌张地离开了。\n", this_object());
        this_object()->move("/d/city/ymzhengting");
	message_vision("$N快步走了过来。\n", this_object());
}
void init()
{
        if( environment() != load_object("/d/city/ymzhengting") ) {
		remove_call_out("go_home");
		call_out("go_home", 1);
	}
}	


int ask_work()
{
        object *all, *inv, ob, room, me=this_player();
        int i, k, j=0;

        all = users();

                for(i=0; i<sizeof(all); i++)
        {
         if(all[i]->query_temp("mark/巡捕") )
                        j++;
        }
        if (j>6){
                command("shake");
                command("say 本府现在不缺人手。");
                return 1;
        }

        if (me->query_temp("mark/巡捕", 1)){
                command("? "+me->query("id"));
                return 1;
        }

        if (me->query("PKS") > 19
        && me->query("combat_exp")/me->query("PKS") < 10000){
                command("hehe "+me->query("id"));
                command("say 你这不是自投罗网吗？");
                message_vision("$N一声冷笑，伸手在椅子上的机关一按，地上突然裂开一个大洞，$n意料之余跌了下去！\n", this_object(), me);
                me->apply_condition("city_jail", 50);

                inv = all_inventory(me);
                for(k=0; k<sizeof(inv); k++) {
                if(( inv[k]->query("armor_prop") && inv[k]->query("equipped"))
                || inv[k]->query("no_get"))continue;
                destruct(inv[k]);
                }
                me->move("/d/city/dalao");
                message("vision","只听“乒”地一声，一个昏沉沉的东西被扔了进来。\n", environment(me), me);
                return 1;
        }
        
        if(!( room = find_object("/d/taishan/fengchan")) )
        room = load_object("/d/taishan/fengchan");
        if (userp(me) && me->query("id") == room->query("winner") ) {
                command("say 阁下是武林盟主，本府可担待不起！");
                return 1;
        }

        if (me->query("combat_exp") < 50000){
                command("say 你是哪里来的小毛孩，闯到这儿来打趣老夫？");
                command("kick "+me->query("id"));
                me->move("/d/city/yamen");
        message("vision","只听“乒”地一声，" +me->query("name") +
                "从正厅里飞了出来。\n", environment(me), me);
                return 1;
        }

        say("李克秀哈哈大笑道；好！本府正缺人手，今天起你就在我手下任事吧！\n");
        me->set_temp("apply/short",
                    ({ HIR"巡捕  "NOR+me->query("name")+"("+capitalize(me->query("id"))+")"}));
        ob=new("/d/city/obj/bounty_list");
        ob->move(me);
        me->set_temp("mark/巡捕", 1);
        write("李克秀在案上翻了翻，找出一张文书递给你。\n");
        return 1;
}
int accept_kill(object me)
{
        command("say 来人啊，有刺客！\n");
        me->apply_condition("killer", 100);
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        command("say 本官这点三脚猫手艺怎敢跟人过招？");
        return 0;
}

int accept_object(object who, object ob)
{
        object *inv;
        int i;
        if (userp(ob) && ob->query("PKS") >= 50)
                return do_proceed(who, ob);
        else if(userp(ob)) return 0;

        if (!ob->query("money_id")) {
                command("sneer");
                command("say 老夫身为浙江提督，怎可受你的小恩小惠？");
                return 0;
        }
        if (ob->query("money_id") && ob->value() < 10000) {
                command("hmm");
                command("say 休想对老夫行贿。");
                return 0;
        }
        if (!who->query_condition("killer")) {
                command("shake " + who->query("id"));
                command("say 多个朋友多条路。你很聪明，老夫就和你交个朋友吧。");
                return 1;
        }
        if (ob->value() < who->query("combat_exp")/10) {
                command("look " + who->query("id"));
                command("say 你的案子非同一般，这点钱我先收着，不过就怕不够打点的。");
                return 1;
        }

        command("secret " + who->query("id"));
        command("whisper " + who->query("id")+ " 你的事就包在我身上了，你放心走吧。");
        who->apply_condition("killer",0);       
        return 1;
}

int do_proceed(object who, object ob)
{       
        object *inv, obj, gold, room;
        int bonus, i;

        ob->clear_condition();
        ob->set("startroom", "/d/city/dalao");

        inv = all_inventory(ob);
                for(i=0; i<sizeof(inv); i++) {
                if(( inv[i]->query("armor_prop") && inv[i]->query("equipped"))
                || inv[i]->query("no_get"))continue;
                destruct(inv[i]);
                }

//      if (!present(ob, this_object())) return 1;

        if (!ob->query_temp("armor/shoulder")){
        bonus = ob->query("combat_exp")/10;
        if (bonus > 3000) bonus = 3000;

        if(!( room = find_object("/d/taishan/fengchan")) )
        room = load_object("/d/taishan/fengchan");

        if ( ob->query("id") != room->query("winner") ){
        if(ob->query("PKS") > 99){
        who->add("combat_exp", bonus);
        ob->add("combat_exp", -bonus);
        ob->apply_condition("city_jail", 500);
                }

        else if(ob->query("PKS") > 74){
        who->add("combat_exp", bonus*2/3);
        ob->add("combat_exp", -bonus*2/3);
        ob->apply_condition("city_jail", 300);
                }

        else if(ob->query("PKS") > 49){
        who->add("combat_exp", bonus/2);
        ob->add("comba_exp", -bonus/2);
        ob->apply_condition("city_jail", 200);
                }
        if(ob->query("city_jail") > 4)
                ob->apply_condition("city_jail", 600);
        }
        
        obj=new("/d/city/obj/pblian");
        obj->move(ob);
        obj->set("embedded", 1);
        ob->add("PKS", -1);
        ob->add("city_jail", 1);
        obj->do_embed();
        }

        message_vision("$N吩咐左右给$n穿上琵琶骨，拖进大牢。\n", this_object(), ob);
        call_out("move_ob", 1, ob);

        command("thumb "+who->query("id"));
        gold=new("/clone/money/gold");
        gold->set_amount(10);
        gold->move(who);
        command("say 这是你的赏金，下去歇着吧！");      
        write("李克秀给你一些黄金！\n");
        command("chat "+ob->query("title")+ob->query("name")+"于今日" 
                + NATURE_D->game_time() +"被本府收监。");
        log_file("Jail", sprintf("%s(%s)把%s(%s)送进 city jail on %s.\n",
                  who->query("name"), who->query("id"), ob->query("name"), ob->query("id"), ctime(time())));
        return 1; 
}
void move_ob(object ob)
{
        ob->move("/d/city/dalao");
        message("vision", "只听“乒”地一声，一个昏沉沉的家伙被扔了进来。\n", environment(ob), ob);
}
