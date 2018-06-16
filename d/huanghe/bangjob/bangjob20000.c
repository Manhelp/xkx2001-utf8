//Cracked by Roath
// /d/huanghe/bangjob/bangjob20000.c
// by aln 2 / 98

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *bangjobs = ({
        ([      "name"  :  "王五",
                "file"  :  "/d/city/npc/guidao",
                "area"  :  "扬州醉仙楼",
                "type"  :  "杀",
                "bonus" :  15,
                "score" :  4,
        ]),

        ([      "name"  :  "空空儿",
                "file"  :  "/d/city/npc/qigai.c",
                "area"  :  "扬州城",
                "type"  :  "杀",
                "bonus" :  40,
                "score" :  20,
        ]),

        ([      "name"  :  "巡捕",
                "file"  :  "/d/city/npc/xunbu",
                "area"  :  "扬州城",
                "type"  :  "杀",
                "bonus" :  50,
                "score" :  15,
        ]),

        ([      "name"  :  "段陉",
                "file"  :  "/d/dali/npc/duanjin",
                "area"  :  "定安府",
                "type"  :  "杀",
                "bonus" :  50,
                "score" :  30,
        ]),

        ([      "name"  :  "常长风",
                "file"  :  "/d/forest/npc/chang",
                "area"  :  "扬州郊外",
                "type"  :  "杀",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "花剑影",
                "file"  :  "/d/forest/npc/hua",
                "area"  :  "扬州郊外",
                "type"  :  "杀",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "戚芳",
                "file"  :  "/d/foshan/npc/qifang",
                "area"  :  "佛山镇",
                "type"  :  "杀",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "凤一鸣",
                "file"  :  "/d/foshan/npc/yiming",
                "area"  :  "佛山镇",
                "type"  :  "杀",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "逍遥子",
                "file"  :  "/d/forest/npc/xiaoyaozi",
                "area"  :  "扬州郊外",
                "type"  :  "杀",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "刘虹瑛",
                "file"  :  "/d/quanzhou/npc/liuhongying",
                "area"  :  "泉州扬威武馆",
                "type"  :  "杀",
                "bonus" :  20,
                "score" :  6,
        ]),

        ([      "name"  :  "龙铨",
                "file"  :  "/d/quanzhou/npc/longquan",
                "area"  :  "泉州扬威武馆",
                "type"  :  "杀",
                "bonus" :  20,
                "score" :  6,
        ]), 

        ([      "name"  :  "刀客",
                "file"  :  "/d/taishan/npc/dao-ke",
                "area"  :  "泰山",
                "type"  :  "杀",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "剑客",
                "file"  :  "/d/taishan/npc/jian-ke",
                "area"  :  "泰山",
                "type"  :  "杀",
                "bonus" :  12,
                "score" :  3,
        ]),

        ([      "name"  :  "土匪头",
                "file"  :  "/d/wudang/npc/tufeitou",
                "area"  :  "武当山",
                "type"  :  "杀",
                "bonus" :  50,
                "score" :  17,
        ]),

        ([      "name"  :  "长剑",
                "file"  :  "/clone/weapon/changjian",
                "type"  :  "寻",
                "bonus" :  8,
                "score" :  1,
        ]),

        ([      "name"  :  "墓碑",
                "file"  :  "/d/forest/npc/obj/mubei",
                "type"  :  "寻",
                "bonus" :  25,
                "score" :  10,
        ]),

        ([      "name"  :  "河图",
                "file"  :  "  ",
                "type"  :  "寻",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "洛书",
                "file"  :  "  ",
                "type"  :  "寻",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "广陵散",
                "file"  :  "  ",
                "type"  :  "寻",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "率意帖",
                "file"  :  "  ",
                "type"  :  "寻",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "棋谱",
                "file"  :  "  ",
                "type"  :  "寻",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "行旅图",
                "file"  :  "  ",
                "type"  :  "寻",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "金戒指",
                "file"  :  "/d/city/npc/obj/goldring",
                "type"  :  "寻",
                "bonus" :  15,
                "score" :  5,
        ]),

        ([      "name"  :  "紫袍",
                "file"  :  "/d/dali/obj/zipao",
                "type"  :  "寻",
                "bonus" :  25,
                "score" :  10,
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),

        ([      "type"  :  "截镖",
        ]),
});

void create() { seteuid(getuid()); }

mapping query_job()
{
        return bangjobs[random(sizeof(bangjobs))];
}
