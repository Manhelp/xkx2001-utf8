//Cracked by Roath
//  lugaox.c  陆高轩

inherit NPC;
// inherit F_MASTER;

string ask_jieyao();
string ask_sheyao();
string ask_huang();
string ask_book();
void apply_gift(object, int);

string *lujob = ({
        "/d/shenlong/obj/fengchao",
        "/d/shenlong/obj/hougan",
});

void create()
{
        set_name("陆高轩", ({ "lu gaoxuan","lu" }));
        set("long",
                "四十来岁年纪，文士打扮，神情和蔼可亲。\n");
        set("gender", "男性");
        set("age", 41);
        set("attitude", "peaceful");

        set("shen_type", -1);
        set("score", 50000);
        set("shen", -15000);

        set("str", 36);
        set("int", 30);
        set("con", 28);
        set("dex", 30);

        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("jiali", 60);
        set("combat_exp", 160000);

        set_skill("force", 100);
        set_skill("dulong-dafa", 80);
        set_skill("dodge", 100);
        set_skill("lingshe-shenfa", 80);
        set_skill("strike", 80);
        set_skill("huagu-mianzhang", 80);
        set_skill("parry", 120);
        set_skill("sword", 100);
        set_skill("medicine", 80);
        set_skill("literate", 90);
//      set_skill("digging", 100);
//      set_skill("magic", 50);
//      set_skill("shenlong-magic", 50);

        set_temp("apply/attack", 60);
        set_temp("apply/damage", 40);
        set_temp("apply/dodge", 50);

        map_skill("force", "dulong-dafa");
        map_skill("dodge", "lingshe-shenfa");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "huagu-mianzhang");
//      map_skill("magic", "shenlong-magic");

        prepare_skill("strike", "huagu-mianzhang");

        create_family("神龙教", 2, "教众");
        set("inquiry", ([
                "解药" : (:ask_jieyao:),
                "豹胆易筋丸" : (:ask_jieyao:),
                "医经" : (: ask_book :),
                "yishu"  : (: ask_book :),
                "蛇药" : (: ask_sheyao :),
                "雄黄" : (: ask_huang :),
        ]));

        set("chat_chance", 5);
        set("chat_msg", ({
                "陆大夫自言自语道：云南一带茶华山里一定有上等蜂巢。\n",
                "陆大夫自言自语道：武夷山那只千年猴精不知死了没有。\n",
        }) );

        set("book1_count", 1);
        set("book2_count", 1);
        set("book3_count", 1);

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

int recognize_apprentice(object ob)
{
        if( (int)ob->query_temp("mark/陆") < 1 )
                return 0; 
        ob->add_temp("mark/陆", -1);
        return 1;
}

string ask_huang()
{
        object ob, me = this_player();

        if( !me->query("sg/spy") ) 
                return RANK_D->query_respect(me) +
                "与本教素无来往，不知此话从何谈起？";

        if(  present("xionghuang", me) )
                return RANK_D->query_respect(this_player()) + "你现在身上不是雄吗，怎么又来要了？真是贪得无餍！";

        if( time() < me->query("huang/time") + 1800 )
                return RANK_D->query_respect(me) + "你不是刚要过雄黄，怎么又来要了？过段时间再来吧。";

        me->set("huang/time", time()); 
        ob = new("/d/shenlong/obj/xionghuang");
        ob->move(me);
        return "好吧，这块雄黄你就拿去吧。";
}

string ask_sheyao()
{
        object me = this_player();

        if( !me->query("sg/spy") ) 
                return RANK_D->query_respect(me) + "与本教素无来往，不知此话从何谈起？";

        if( !me->query_condition("snake_poison") )
                return"你好好的，要蛇药干吗？";

        if( me->query("gender") == "男性" )
                say("嘿嘿，真没出息，为了方姑娘连命都不要了？\n");
        else    say("叹！是不是方姑娘又欺侮你了？\n");

        message_vision("$N对$n说道：把嘴张开。\n", this_object(), me);
        message_vision("$N把嘴张得大大的。\n", me);
        message_vision("只见$N把一包蛇药全倒进$n嘴里\n", this_object(), me);
        message_vision("$N乐不可支地对$n说道：多谢陆大夫！\n", me, this_object()
);

        call_out("lucure", 1 + random(2), me);
        return "下次小心了。";
}

void lucure(object me)
{
        message_vision("$N吐出一口黑血，脸色看起来红润多了。\n", me);
        me->clear_condition("snake_poison");
}

string ask_jieyao()
{
        object ob, me = this_player();

        if( !me->query("yijin_wan") )
                return "解药怎么能随便乱吃？\n";
/*
        if( (int)me->query("combat_exp") < 100000 )
                return "凭你这点道行，也敢来窥视解药？\n";
*/
        if( (int)me->query_temp("lu/jieyao") )
	        return "你没有找到识得甲骨文的行家？\n";

        command("sigh");
        say("陆高轩说道：要不是我妻儿控制在教主手里，我早离开神龙教了。\n");

        ob = new("/d/shenlong/obj/zihua");
        ob->move(me);
        me->set_temp("lu/jieyao", 1);
        message_vision("$N将一" + ob->query("unit") + ob->query("name") + "交给$n。\n", this_object(), me);
        return "如果你能访得一位识得甲骨文的行家将它译出来，我就给你解药。\n";
}

string ask_book()
{
        object ob, *obs, me = this_player();
        int lvl;
        
        if( !me->query("yijin_wan") )
                return RANK_D->query_respect(this_player()) + 
                "与本教素无来往，不知此话从何谈起？";

        if( (int)me->query("sg/exp") < 1000 )
                return "就凭" + RANK_D->query_respect(this_player()) + "在教中的表现，医经之事就免谈了。";

        lvl = me->query_skill("medicine", 1);

        if( lvl < 30 ) {
                if( query("book1_count") < 1 )
                        return "你来晚了，你所需要的医经已经有人拿走了。";
                obs = filter_array(children("/d/shenlong/obj/yijing1.c"), (: clonep :));
                if( sizeof(obs) )
                        return "你来晚了，你所需要的医经已经有人拿走了。";
                ob = new("/d/shenlong/obj/yijing1");
                ob->move(me);
                add("book1_count", -1);
                return "好吧，这本『黄帝内经』你拿回去好好钻研。";
        } else if( lvl < 60 ) {
                if( query("book2_count") < 1 )
                        return "你来晚了，你所需要的医经已经有人拿走了。";
                obs = filter_array(children("/d/shenlong/obj/yijing2.c"), (: clonep :));
                if( sizeof(obs) )
                        return "你来晚了，你所需要的医经已经有人拿走了。";
                ob = new("/d/shenlong/obj/yijing2");
                ob->move(me);
                add("book2_count", -1);
                return "好吧，这本『十四经发挥』你拿回去好好钻研。";
        } else if( lvl < 90 ) {
                if( query("book3_count") < 1 )
                        return "你来晚了，你所需要的医经已经有人拿走了。";
                obs = filter_array(children("/d/shenlong/obj/yijing3.c"), (: clonep :));
                if( sizeof(obs) )
                        return "你来晚了，你所需要的医经已经有人拿走了。";
                ob = new("/d/shenlong/obj/yijing3");
                ob->move(me);
                add("book3_count", -1);
                return "好吧，这本『孙思邈千金方』你拿回去好好钻研。";
        }

        return "阁下熟知医理，我这儿没有合适的医经可供你钻研。";
}

int accept_object(object who, object ob)
{
        mapping my;
        int i, tot, bonus;

        if( who->query_temp("lu/jieyao") && ob->name() == "颂词" ) {
                who->delete("yijin_wan");
                my = who->query_entire_dbase();
                tot = my["str"] + my["int"] + my["con"] + my["dex"];
                tot -= 80;
                if( tot > 0 ) {
                        for(i = 0; i < tot; i ++) {
                                switch (random(4)) {
                                        case 0: my["str"]--; break;
                                        case 1: my["int"]--; break;
                                        case 2: my["con"]--; break;
                                        case 3: my["dex"]--; break;
                                }
                        }
		}
                            
                who->delete("sg");
                who->delete("sgjob");
                who->set("sg/cured", 1);
                who->delete("yijin_wan");
                apply_gift(who, 0);

                command("touch " + who->query("id"));
                message_vision("陆高轩从衣袋里掏出一粒药丸塞进了$N的嘴里。\n", who);
                command("whisper " + who->query("id") + " " + "此事可千万不能张扬出去。\n");

                call_out("destroy", 1, ob);
                return 1;
        }

        if( member_array(base_name(ob), lujob) == -1 )
                return 0;

        command("nod");
        call_out("destroy", 1, ob);

        if( ob->query("owner") != who->query("id") ) {
                command("say 呵，呵，呵，你运气真好捡了一" + ob->query("unit") + ob->query("name") + "。");
                return 1;
        }

        if( (bonus = who->query("combat_exp")) > 100000 ) {
                command("say 这种小事以后就不用你操劳了。");
                return 1;
        }

        if( random(6) )
        who->add("sg/exp", 1);

        bonus = 50 + (100000 - bonus) / 200;
        who->add("combat_exp", bonus + random(bonus));
        who->add_temp("mark/陆", bonus/10);
        return 1;
}

void destroy(object ob)
{
        destruct(ob);
}

void apply_gift(object me, int flag)
{
        int i;
        int tmpstr, tmpint, tmpcon, tmpdex;
        mapping my = me->query_entire_dbase();

        tmpstr = tmpint = tmpcon = tmpdex = 10 + flag;

        for (i = 0; i < 40; i++) {
                switch (random(4)) {
                        case 0: tmpstr++; break;
                        case 1: tmpint++; break;
                        case 2: tmpcon++; break;
                        case 3: tmpdex++; break;
                }
        }

        if (tmpstr <= 30) my["str"] = tmpstr;   else my["str"] = 30;
        if (tmpint <= 30) my["int"] = tmpint;   else my["int"] = 30;
        if (tmpcon <= 30) my["con"] = tmpcon;   else my["con"] = 30;
        if (tmpdex <= 30) my["dex"] = tmpdex;   else my["dex"] = 30;
}

