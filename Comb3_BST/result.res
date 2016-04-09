data:
in_e3.txt
in_e5.txt
in_e7.txt

splay_v1.0:
splay_v1+++:	hard_splay, hard_insert, hard_remove
splay_v1---:	simple_splay, simple_insert, simple_remove
splay_v2+:		hard_splay, simple_insert, simple_remove, hard_top_down_access
splay_v2-:		hard_splay, simple_insert, simple_remove, simple_top_down_access

(ms)			e3		e5		e7
treap			15		1194	23894
set				48		1173	22213
splay_v1+++		26		1663	33498
splay_v1++-		12		1548	33611
splay_v1+-+		8		1563	31804
splay_v1+--		7		1515	31038
splay_v2+		0		1404	29701
splay_v2-		15		1388	27128

	e5 		e7
set	2218  	34082
+++ 7083	115662
-++	9064
++- 9402
-+- 8096
+-- 8660
--- 9473
--+ 8981
+-+ 8015  	100588
