//Cracked by Roath
// /d/changbai/npc/chan.c 单正
// ALN 1/98

#ifndef NPCDATA
#define NPCDATA "/data/npc/"
#endif
#define SHANZHENG NPCDATA + "shan-zheng"

#define BANGJIAO  "/d/changbai/bj/"

#define BANGYIN   "/d/huanghe/obj/bangyin"
#define BANGYIN2  BANGJIAO + "bangyin2"
#define JIAN      BANGJIAO + "sword"
#define ZHANGLAO  BANGJIAO + "zhanglao"
#define LAMA      BANGJIAO + "lama"

#define BANGZHU   "/d/huanghe/npc/bangzhu"

inherit NPC;
inherit F_SAVE;

#include <ansi.h>
#include <room.h>
#include <localtime.h>

#include "/d/changbai/bj/info_bang.h"
#include "/d/changbai/bj/info_zhanglao.h"
#include "/d/changbai/bj/info_lama.h"
#include "/d/REGIONS.h"

string ask_bang(string);
string ask_bangyin();
string ask_jianghu();
string ask_jian();
string ask_mizong();

string query_save_file()
{
        return SHANZHENG;
}

void create()
{
        string *bangs;

        seteuid(getuid());

        if (!restore()) {
        set_name("单正", ({ "shan zheng", "shan", "judge" }));
        set("nickname", "铁面判官");
        set("long", 
"他生平嫉恶如仇，只要知道江湖上有什么不公道之事，定然伸手要管。\n"
"他满脸红光，当得起“童颜鹤发”四字，神情却甚谦和，不似江湖上传说的出手无情。\n");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 900);
        set("max_jing", 500);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 40);
        set("combat_exp", 400000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("wuxingbu", 100);
        set_skill("parry", 100);
        set_skill("cuff", 100);
        set_skill("wuxing-quan", 120);
        set_skill("club", 100);
        set_skill("ding-force", 100);
        set_skill("liuhe-qiang", 120);

        map_skill("club", "liuhe-qiang");
        map_skill("parry", "liuhe-qiang");
        map_skill("dodge", "wuxingbu");
        map_skill("cuff", "wuxing-quan");
        map_skill("force", "ding-force");

        prepare_skill("cuff", "wuxing-quan");

        bangs = keys(info_bang);
        for(int i = 0; i < sizeof(bangs); i++) {
                set("inquiry/" + bangs[i], (: ask_bang, bangs[i] :));
        }

        setup();
        }
        else {
                set("id", "shan zheng");
                set_name(query("name"), ({ query("id") }));
                setup();
                clear_condition();  
        }

        set("chat_chance", 10);
        set("chat_msg",({
                (: random_move :)
        }));

        set("inquiry", ([
                "帮" : (: ask_bang, "帮" :),
                "邪帮" : (: ask_bang, "邪帮" :),
                "帮主" : (: ask_bangyin :),
                "帮印" : (: ask_bangyin :),
                "bangzhu" : (: ask_bangyin :),
                "江湖" : (: ask_jianghu :),
                "jianghu" : (: ask_jianghu :),
                "铁剑门" : (: ask_jian :),
                "jian" : (: ask_jian :),
                "密宗" : (: ask_mizong :),
                "密宗高手" : (: ask_mizong :),
                "高手" : "江湖威望来自德行而非武功。",
        ]));

        carry_object("/clone/weapon/panguanbi")->wield();
}

void init()
{
        add_action("do_sue", "sue");
}

int do_sue(string arg)
{
        object ob, obj, me = this_player();
        mapping sue, sue_site, sued;
        string my, your, *times, yourfam;
        int i, total, period;

        if( is_busy() || is_fighting() ) 
                return notify_fail("单正正忙着。\n");

        if( !(ob = find_player(arg)) ) {
                ob = new(USER_OB);
                ob->set("id", arg);
                if( !ob->restore() ) {
                        command("say 没有这个人。");
                        destruct(ob);
                        return 1;
                }
                ob->set_temp("insue", 1);
                call_out("do_destroy", 1, ob);
        }

        yourfam = (string)ob->query("family/family_name");
        if( ob->query("sell_woman/" + me->query("id"))
        &&  (int)ob->query("combat_exp") > 100000
        &&  (  yourfam == "少林派"
            || yourfam == "峨嵋派"
            || yourfam == "武当派"
            || yourfam == "华山派"
            || yourfam == "大理段家" ) ) {
                ob->delete("sell_woman/" + me->query("id"));
                ob->set("incharge", time());
                ob->save();
                command("nod");
                command("say 我将转告五岳剑派掌门人左冷禅。");
                log_file("SuePK", sprintf("%s于%s时起诉%s贩卖妇女\n", me->query("name"), ctime(time()), ob->query("name")));
                return 1;
         }

        if( me->query_temp("my_killer") != ob->query("id") ) {
                command("say 最近" + ob->query("name") + "没有伤害你呀。");
                return 1;
        }

        if( me->query_temp("pking/" + ob->query("id")) ) {
                command("say 你自己闯的祸，不能怨别人。");
                return 1;
        }

        if( (int)ob->query("combat_exp") < (int)me->query("combat_exp") ) {
                command("say 这种私人恩怨太多了，你还是自强不息啊。");
                return 1;
        }

        if( (int)me->query("combat_exp") > 300000 ) {
                command("say 你已经在武林中成名了，还是自强不息吧。");           
                return 1;
	}

        start_busy(2);
        me->delete_temp("my_killer");

        my = me->query("id");
        your = ob->query("id");

        if( !mapp(sue = query("sue")) ) {
                sue = ([]);
                sue_site = ([]);
                sued = ([]);
        } else {
                if( !mapp(sue_site = query("sue_site")) ) sue_site = ([]);
                sued = query("sued");

                times = keys(sue);
                for(i = 0; i < sizeof(times); i++) {
                        if(time() > atoi(times[i]) + 86400) {
                                map_delete(sue, times[i]);
                                map_delete(sue_site, times[i]);
                                map_delete(sued, times[i]);
                        }
                }

                times = keys(sue);
                total = 0;
                for(i = 0; i < sizeof(times); i++) {
                        if( sue[times[i]] == my && sued[times[i]] == your ) {
                                command("say 你不久前刚告过此人，不过现在还没有调查清楚。");
                                save();
                                return 1;
                        }

                        if( sue_site[times[i]] == query_ip_name(me) ) {
                                command("say 你的朋友刚告过此人，不过现在还没有调查清楚。");
                                save();
                                return 1;
                        }

                        if( sued[times[i]] == your ) total++;
		}
        }

        command("nod");

        switch((string)ob->query("family/family_name")) {
	case "武当派" : period = 10; break;
	case "少林派" : period = 10; break;
        case "华山派" : period = 15; break;
        case "峨嵋派" : period = 15; break;
        case "桃花岛" : period = 20; break;
        case "丐帮"    : period = 20; break;
        case "白驼山庄" : period = 30; break;
        case "星宿派" : period = 30; break;
        default              : period = 25; break;
        }

        if( random(total) >= period/2 ) {
                command("say 我将转告武当掌门人张三丰和五岳剑派掌门人左冷禅，由他们两位武林领袖人物处理此事。");
                ob->set("incharge", time());
                ob->save();

                log_file("SuePK", sprintf("%s于%s时告倒%s\n", me->query("name"), ctime(time()), ob->query("name")));            

                for(i = 0; i < sizeof(times); i++) {
                        if( sued[times[i]] == your ) {
                log_file("SuePK", sprintf("%s也于%s被%s从%s起诉过\n", ob->query("name"), ctime(atoi(times[i])), sue[times[i]], sue_site[times[i]]));
                                map_delete(sue, times[i]);
                                map_delete(sue_site, times[i]);
                                map_delete(sued, times[i]);
                        }
                }
                save();

                if( ob->query_temp("insue") ) 
                        return 1;

                message_vision("$N匆匆忙忙离开了。\n", this_object());
                move("/d/wudang/xiaoyuan");
                message_vision("$N走了过来。\n", this_object());

                if( obj = present("zhang sanfeng", environment()) ) {
                        message_vision("$N对$n说道：最近张真人别来无恙？只是" + ob->query("name") + "在武林中残杀无辜，还需张真人出面处理此事。\n", this_object(), obj);
                        message_vision("$N说道：此乃我武当份内之事，单判官不客气，我立即就去处理。\n", obj);

                        message_vision("$N匆匆忙忙离开了。\n", obj);
                        obj->move(environment(ob));
                        message_vision(HIR"\n$N对$n喝道：" + RANK_D->query_rude(ob) + "居然敢危害武林，实在是死有余辜。\n"NOR, obj, ob);
                        obj->set_leader(ob);
                        obj->kill_ob(ob);
                }

                message_vision("$N匆匆忙忙离开了。\n", this_object());
                move("/d/taishan/daizong");
                message_vision("$N走了过来。\n", this_object());
                return 1;    
        }

        command("say 等调查清楚，武林中自有人替你出面。");
        set("sue/" + time(), my);
        set("sue_site/" + time(), query_ip_name(me));
        set("sued/" + time(), your);
        save();
        return 1;
}

int accept_object(object who, object ob)
{
        object room;
        int exp, p_exp, bonus, record, period;
        string my_id, file = base_name(ob);

        switch(file) {
        case JIAN:
                if( ob->query("my_killer") != who->query("id") )
                        return notify_fail("这种冒名的事，你也干？！\n");

                if( (int)who->query("combat_exp") < 300000 )
                        return notify_fail("一定是冒名吧。\n");

                command("touch " + who->query("id"));
                command("say 铁剑门终于有救了！");

                period = time() - (int)who->query("shan/time4");
                if( period > 480 ) period = 480;
                if( period <  60 ) period =  60;

                bonus = (int)ob->query("bonus") * period / 600;
                record = bonus + random(bonus);
                who->add("combat_exp", record);

                who->set("shan/time4", time());
                log_file("test/ShanBonus", sprintf("%s于%s时上交了%s，拿了%s经验点\n", who->query("name"), ctime(time()), ob->name(), chinese_number(record)));
                call_out("do_destroy", 1, ob);
                return 1;

	case BANGYIN:
                my_id = who->query("id");
                if( ob->query("my_killer") != my_id )
                        return notify_fail("这种冒名的事，你也干？！\n");

                if( !( room = find_object("/d/taishan/fengchan")) )
                        room = load_object("/d/taishan/fengchan");
                if( my_id == room->query("winner") )
                        return notify_fail(RANK_D->query_respect(who) + "是当今武林盟主，我小小一个判官岂能对您说三道四？");

                if( !( room = find_object("/d/taishan/xiayi")) )
                        room = load_object("/d/taishan/xiayi");
                if( my_id == room->query("winner") )
                        return notify_fail(RANK_D->query_respect(who) + "是当今武林盟主，我小小一个判官岂能对您说三道四？");

                if( !( room = find_object("/d/taishan/zhengqi")) )
                        room = load_object("/d/taishan/zhengqi");
                if( my_id == room->query("winner") )
                        return notify_fail(RANK_D->query_respect(who) + "是当今罚恶使者，我小小一个判官岂能对您说三道四？");

                exp = (int)ob->query("combat_exp");
                p_exp = (int)who->query("combat_exp");

                if( p_exp > exp + 1000 ) {
                        command("nod");
                        command("say 这对你来说是小事一桩，我就不夸你了。");
                        call_out("do_destroy", 1, ob);
                        return 1;
                }

                command("thumb " + who->query("id"));
                if( (string)who->query("family/family_name") != "武当派" )
                        who->add("shen", exp / 100);

                bonus = 10 + 200 * exp / (exp + p_exp);

                record = bonus + random(bonus);
                who->add("combat_exp", record);

                log_file("test/ShanPlaying", sprintf("%s于%s时拿了%s经验点，上交了%s", who->query("name"), ctime(time()), chinese_number(record), ob->query("long")));
                call_out("do_destroy", 1, ob);
                return 1;
        }

        return notify_fail("单正说道：这不是我想要的。\n");
}

void do_destroy(object ob)
{
        destruct(ob);
}

// job1
string ask_bang(string name)
{
        object *obj, room;
        string *bangs, str, region, file;
        int i, temp;

        if( name == "帮" ) 
                return "江湖上有" + chinese_number(sizeof(info_bang)) + "个邪帮帮主经常搞乱，有" + chinese_number(sizeof(empty_bangs)) + "个帮没有得力的帮主掌管。";

        if( name == "邪帮" ) {
                bangs = keys(info_bang);
                str = "江湖上邪帮有：";
                temp = sizeof(bangs);
		for( i = 0; i < temp; i++ ) {
                        if( i != temp - 1 )
                                str += bangs[i] + "，";
                        else    str += bangs[i] + "。";
                }

                return str;
        }

        obj = filter_array(children(BANGZHU), (: clonep :));
        if( sizeof(obj) ) {
	        for(i = 0; i < sizeof(obj); i++) {
                        if( obj[i]->query("bangname") == name ) {
                                command("nod");
                                room = environment(obj[i]);
                                if( !room )
	                        return name + "帮主" + info_bang[name] + "最近失踪了。";

                                file = base_name(room);
                                if( strsrch(file, "/d/") != 0 
                                || !mapp(room->query("exits")) )
                                return name + "帮主" + info_bang[name] + "最近失踪了。";
				
                                region = explode(file, "/")[1];
                                return name + "帮主" + info_bang[name] + "，最近在" + region_names[region] + "一带集众为非作歹！！！";
                        }
                }
        }

        command(":)");
        return name + "帮主" + info_bang[name] + "最近安分守纪。";
}

// job2
string ask_bangyin()
{
        object *obj, ob, me = this_player(), room;
        string *bangs, bang, myfam, my_id;
        int i;

        if( time() < (int)me->query("shan/time2") + 60 )
                return RANK_D->query_respect(me) + "不是刚向我打听过吗？\n";

        my_id = (string)me->query("id");
        if( !( room = find_object("/d/taishan/fengchan")) )
                room = load_object("/d/taishan/fengchan");
        if( my_id == room->query("winner") )
                return RANK_D->query_respect(me) + "是当今武林盟主，怎也贪这小帮之主？！";

        if( !( room = find_object("/d/taishan/xiayi")) )
                room = load_object("/d/taishan/xiayi");
        if( my_id == room->query("winner") )
                return RANK_D->query_respect(me) + "是当今赏善使者，怎也贪这小帮之主？！";

        if( !( room = find_object("/d/taishan/zhengqi")) )
                room = load_object("/d/taishan/zhengqi");
        if( my_id == room->query("winner") )
                return RANK_D->query_respect(me) + "是当今罚恶使者，怎也贪这小帮之主？！";

        myfam = (string)me->query("family/family_name");
        if( (int)me->query("shen") < 10000
        &&   myfam != "少林派" )
                return RANK_D->query_respect(me) + "是黑道上的人，老夫岂能放心将一帮之主托付给你？";

        if( (int)me->query("combat_exp") < 300000 )
                return RANK_D->query_respect(me) + "还是在江湖上多混几年吧。";

        if( (int)me->query("combat_exp") > 800000 )
                return RANK_D->query_respect(me) + "已是世外高手，何必再涉这趟混水？";

        if( myfam == "大理段家" )
                return RANK_D->query_respect(me) + "乃大理国人氏，对中原武林不太熟悉吧。";

        if( myfam == "丐帮" )
                return RANK_D->query_respect(me) + "已入丐帮，何不为丐帮尽心尽力？";

        if( myfam != "少林派"
        &&  myfam != "武当派"
        &&  myfam != "峨嵋派"
        &&  myfam != "华山派" )
                return RANK_D->query_respect(me) + "非名门正派出身，老夫岂能放心将一帮之主托付给你？";

 //       if( present("bangyin", me) )
        if( stringp(me->query_temp("shan/bangzhu")) )
                return RANK_D->query_respect(me) + "手上不是已经有了一帮帮印了吗？";
            
        obj = filter_array(children(BANGYIN2), (: clonep :));
        if( sizeof(obj) >= 3 )
                return "最近江湖太平无事，你下次再来吧。";

        bangs = empty_bangs;
        if( sizeof(obj) ) {
                for(i = 0; i < sizeof(obj); i++)
                        bangs -= ({obj[i]->query("bangname")});
        }
        bang = bangs[random(sizeof(bangs))];

        ob = new(BANGYIN2);
        ob->set("bangname", bang);
        ob->set("long", bang + ob->query("name") + "。\n");
        ob->set("owner", me->query("id"));
        ob->move(me);
        me->set_temp("shan/bangzhu", bang);

        message_vision("$N将" + bang + ob->query("name") + "交给了$n。\n", this_object(), me);
        command("congra");
        me->set_temp("apply/short",
                ({ bang + HIR"帮主"NOR + me->query("name")+"("+capitalize(me->query("id"))+")" }));

        log_file("test/ShanPlaying", sprintf("%s于%s时当上了%s帮主\n", me->query("name"), ctime(time()), bang));

        me->set("shan/time2", time());
        return "望" + RANK_D->query_respect(me) + "早日将" + bang + "改编成一个侠义之帮。";
}

// job3
string ask_jianghu()
{
        object *obj, ob, me = this_player();
        string *places, place;
        int i, temp;

        if( time() < (int)me->query("shan/time3") + 120 )
                return RANK_D->query_respect(me) + "不是刚向我打听过吗？\n";

        if( (int)me->query("shen") < 100000
        &&  (string)me->query("family/family_name") != "少林派" )
                return RANK_D->query_respect(me) + "是黑道上的人，只怕魔教是" + RANK_D->query_respect(me) + "引来的。";

        if( (int)me->query("combat_exp") < 500000 )
                return RANK_D->query_respect(me) + "还是在江湖上多混几年吧。";

        obj = filter_array(children("ZHANGLAO"), (: clonep :));
        if( (temp = sizeof(obj)) >= 3 )
                return RANK_D->query_respect(me) + "能否尽一些义务，扫除魔教势力？";

        if( temp = sizeof(obj) ) {
                for(i = 0; i < sizeof(obj); i++) {
                        if( obj[i]->query("bj_victim") == me->query("id") )
                                return RANK_D->query_respect(me) + "也太让我武林正派人士失望了。";
                }
        }

        if( temp >= 3 )
                return RANK_D->query_respect(me) + "能否尽一些义务，扫除魔教势力？";

        ob = new("ZHANGLAO");
        ob->set("bj_victim", me->query("id"));
        places = keys(zl_places);
        place = places[random(sizeof(places))];
        ob->move(place);
        message("vision",
                ob->name() + "走了过来。\n",
                environment(ob), ({ob}));

        me->set("shan/time3", time());
        log_file("test/ShanPlaying", sprintf("%s于%s时授命保护%s\n", me->query("name"), ctime(time()), zl_places[place]));
        command("sigh");
        return "最近魔教搔扰" + zl_places[place] + "，搞得整个江湖不得安宁。";
}


// job4
string ask_jian()
{
        object *obj, room, lama, ob = this_player();
        string place;
        int i, temp;

        if( (int)ob->query("combat_exp") < 500000 ) {
                command("shake " + ob->query("id"));
                return "此事太过艰难，非你力可为。";
        }

        if( time() < (int)ob->query("shan/time4") + 60 )
                return RANK_D->query_respect(ob) + "不是刚向我打听过吗？\n";

        ob->set("shan/time4", time());

        obj = filter_array(children(LAMA), (: clonep :));

        if( temp = sizeof(obj) ) {
                for(i = 0; i < temp; i++) {
                        if( !(room = environment(obj[i])) ) {
                                destruct(obj[i]);
                                command("sigh");
                                return "铁剑门“掌门之宝”失踪了，眼看就要大难临头了。";
                        }

                        if( !mapp(room->query("exits")) 
                        ||  strsrch(base_name(room), "/d/") != 0 ) {
                                destruct(obj[i]);
                                command("sigh");
                                return "铁剑门“掌门之宝”失踪了，眼看就要大难临头了。";
                        }
                }

                command("shout");
                return "江湖盛传铁剑门“掌门之宝”已被密宗高手所获。";
        }

        place = lama_places[random(sizeof(lama_places))];
        lama = new(LAMA + "2");
        lama->move(place);
        message("vision",
                lama->name() + "走了过来。\n",
                environment(lama), ({lama}));

        lama = new(LAMA);
        lama->move(place);
        message("vision",
                lama->name() + "走了过来。\n",
                environment(lama), ({lama}));

        command("shout");
        return "江湖盛传铁剑门“掌门之宝”已被密宗高手所获。";
}


string ask_mizong()
{
        object ob, *obj, room;
        string file;

        obj = filter_array(children(LAMA), (: clonep :));

        if( !sizeof(obj) ) return "我也不知道他们在哪里。";

        ob = obj[random(sizeof(obj))];
        if( !(room = environment(ob)) ) {
                destruct(ob);
                return "我也不知道他们在哪里。";
        }

        if( strsrch((file = base_name(room)), "/d/") != 0 ) {
                destruct(ob);
                return "我也不知道他们在哪里。";
        }

        command("nod");
        return "江湖上传闻，最近他们出没在" + region_names[explode(file, "/")[1]] + "一带。";
}
