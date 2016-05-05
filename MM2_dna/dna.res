TR
=======================================
------------->**************<-------------
layer_slice.feature_lbound = 3;
layer_sgroup.feature_lbound = 4;
layer_group.feature_lbound = 6;

layer_read.score_bound = 160;
layer_slice.score_bound = 284;
layer_sgroup.score_bound = 280;
layer_group.score_bound = 280;

layer_read.topk = 2400;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 200;

test Small:
prep_time = 22.3601, prep_bound = 603.0000
cut_time = 373.9993, cut_bound = 32.2000
Number of correct answers: 37/19116 = 0.0019

------------->**************<-------------
layer_slice.feature_lbound = 3;
layer_sgroup.feature_lbound = 3;
layer_group.feature_lbound = 5;

layer_read.score_bound = 120;
layer_slice.score_bound = 280;
layer_sgroup.score_bound = 270;
layer_group.score_bound = 270;

layer_read.topk = 1800;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 200;

test Small:
prep_time = 23.2847, prep_bound = 603.0000
cut_time = 93.4056, cut_bound = 32.2000
Number of correct answers: 9/19116 = 0.0005

------------->**************<-------------
layer_slice.feature_lbound = 3;
layer_sgroup.feature_lbound = 3;
layer_group.feature_lbound = 5;

layer_read.score_bound = 160;
layer_slice.score_bound = 300;
layer_sgroup.score_bound = 280;
layer_group.score_bound = 280;

layer_read.topk = 1800;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 200;
test Small:
prep_time = 19.6296, prep_bound = 603.0000
cut_time = 473.4644, cut_bound = 32.2000
Number of correct answers: 71/19116 = 0.0037


------------->**************<-------------
layer_slice.feature_lbound = 2;
layer_sgroup.feature_lbound = 3;
layer_group.feature_lbound = 3;

layer_read.score_bound = 160;
layer_slice.score_bound = 320;
layer_sgroup.score_bound = 310;
layer_group.score_bound = 300;

layer_read.topk = 1000;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 180;

test Small:
prep_time = 20.0608, prep_bound = 603.0000
cut_time = 684.8564, cut_bound = 32.2000
Number of correct answers: 89/19116 = 0.0047

------------->**************<-------------
ayer_slice.feature_lbound = 2;
layer_sgroup.feature_lbound = 3;
layer_group.feature_lbound = 3;

layer_read.score_bound = 160;
layer_slice.score_bound = 320;
layer_sgroup.score_bound = 310;
layer_group.score_bound = 300;

layer_read.topk = 800;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 120;

test Small:
prep_time = 20.0608, prep_bound = 603.0000
cut_time = 684.8564, cut_bound = 32.2000
Number of correct answers: 89/19116 = 0.0047
prep_time = 20.1763, prep_bound = 603.0000
cut_time = 537.5296, cut_bound = 32.2000
Number of correct answers: 81/19116 = 0.0042


DELL
=======================================
------------->**************<-------------
layer_slice.feature_lbound = 3;
layer_sgroup.feature_lbound = 3;
layer_group.feature_lbound = 5;

layer_read.score_bound = 120;
layer_slice.score_bound = 280;
layer_sgroup.score_bound = 270;
layer_group.score_bound = 270;

layer_read.topk = 1800;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 200;

test Small:
prep_time = 29.6527, prep_bound = 603.0000
cut_time = 606.1264, cut_bound = 32.2000
Number of correct answers: 33/19116 = 0.0017

------------->**************<-------------
layer_slice.feature_lbound = 2;
layer_sgroup.feature_lbound = 4;
layer_group.feature_lbound = 5;

layer_read.topk = 2400;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 200;

layer_read.score_bound = 120;
layer_slice.score_bound = 280;
layer_sgroup.score_bound = 270;
layer_group.score_bound = 270;
test Small:
prep_time = 30.0954, prep_bound = 603.0000
cut_time = 603.7418, cut_bound = 32.2000
Number of correct answers: 33/19116 = 0.0017

------------->**************<-------------
layer_slice.feature_lbound = 2;
layer_sgroup.feature_lbound = 3;
layer_group.feature_lbound = 3;

layer_read.topk = 1200;
layer_slice.topk = 2;
layer_sgroup.topk = 30;
layer_group.topk = 200;

layer_read.score_bound = 200;
layer_slice.score_bound = 3000;
layer_sgroup.score_bound = 290;
layer_group.score_bound = 280;
test Small:
prep_time = 30.2757, prep_bound = 603.0000
cut_time = 1579.7327, cut_bound = 32.2000
Number of correct answers: 77/19116 = 0.0040




slice = 160
=======================================
test Small:
trie_node_n = 59161208
leafs = 395849
prep_time = 5.5423, prep_bound = 603.0000

test Medium:
fail

test Large:
fail

slice = 80
=======================================
test Small:
trie_node_n = 26525841
leafs = 381058
prep_time = 2.7157, prep_bound = 603.0000


test Medium:
fail

test Large:
fail


slice = 50
=======================================
test Small:
trie_node_n = 18499999
leafs = 465251
prep_time = 2.7845, prep_bound = 603.0000


test Medium:
fail

test Large:
fail

slice = 40
=======================================
test Small:
trie_node_n = 14793288
leafs = 496532
prep_time = 2.5864, prep_bound = 603.0000


test Medium:
trie_node_n = 46652610
leafs = 1632938
trie_node_n = 71940612
leafs = 2547612
trie_node_n = 85279749
leafs = 3036169

test Large:
trie_node_n = 58726049
leafs = 1529515
fail next

slice = 20
=======================================
test Small:
trie_node_n = 4958302
leafs = 465482
prep_time = 1.5362, prep_bound = 603.0000


test Medium:
trie_node_n = 14884231
leafs = 1526822
trie_node_n = 22464872
leafs = 2382886
trie_node_n = 26249390
leafs = 2821665
prep_time = 11.0835, prep_bound = 5007.0000


test Large:
trie_node_n = 14884231
leafs = 1526822
trie_node_n = 28056925
leafs = 3028655
trie_node_n = 38174190
leafs = 4234132
trie_node_n = 46815609
leafs = 5289777
trie_node_n = 55389665
leafs = 6356407
trie_node_n = 63326019
leafs = 7358433
fail

slice = 15
==========================================
trie_node_n = 6505960
leafs = 1327194
trie_node_n = 11470638
leafs = 2617085
trie_node_n = 15005652
leafs = 3631699
trie_node_n = 17912412
leafs = 4514051
trie_node_n = 20658585
leafs = 5386383
trie_node_n = 23120140
leafs = 6194199
trie_node_n = 25296884
leafs = 6928744
trie_node_n = 27277242
leafs = 7614279
trie_node_n = 28877403
leafs = 8180251
trie_node_n = 30649517
leafs = 8816623
trie_node_n = 32340346
leafs = 9436950
trie_node_n = 33915549
leafs = 10022254
trie_node_n = 35016287
leafs = 10434664
trie_node_n = 36047310
leafs = 10825650
trie_node_n = 37051042
leafs = 11209659
trie_node_n = 38036596
leafs = 11587114
trie_node_n = 38965027
leafs = 11945668
trie_node_n = 39813754
leafs = 12277102
trie_node_n = 40408269
leafs = 12506980
trie_node_n = 41151381
leafs = 12801477
trie_node_n = 41561194
leafs = 12962471
trie_node_n = 41990126
leafs = 13132229

