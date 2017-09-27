



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%1---------------------------------------------------------
figure;
hold on;

%figuresize(5, 4, 'inches');

box on;
x1 = [5000,10000,20000,30000,40000];
simg1= [1922,2830,4241,5259,5915];
opt1= [4452,7864,12560,14941,16275];
pre1= [2128,4023,6640,8046,8651];
preg1= [1980,3066,4622,5851,6563];
opre1= [2801,5526,9591,11937,13297];
mpdc5 = distinguishable_colors(5);
plot(x1, simg1, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, pre1, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x1, preg1, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, opre1, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, opt1, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%

xlabel('|W|', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [5000,10000,20000,30000,40000];
simg2= [1.304000,2.568000,4.864000,6.672000,8.527000];
opt2= [2.029000,4.316000,10.989000,20.110000,28.923000];
pre2= [0.016000,0.019000,0.024000,0.031000,0.038000];
preg2= [0.0719,0.1352,0.3457,0.4347,0.7150];
opre2= [0.009000,0.032000,0.041000,0.057000,0.081000];
mpdc5 = distinguishable_colors(5);
plot(x2, simg2, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, pre2, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x2, preg2, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, opre2, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, opt2, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [5000,10000,20000,30000,40000];
simg3= [4.324219,4.640625,4.523438,4.761719,4.878906];
opt3= [45.765625,80.437500,160.617188,233.027344,302.386719];
pre3= [6.437500,6.480469,6.601563,6.726563,6.824219];
preg3= [17,17,18,18,18];
opre3= [28.480469,28.718750,29.042969,29.328125,29.570313];
mpdc5 = distinguishable_colors(5);
plot(x3, simg3, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, pre3, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x3, preg3, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, opre3, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, opt3, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x3 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x3);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [5000,10000,20000,30000,40000];
simg4= [1808,2956,4241,5220,5918];
opt4= [4412,8057,12560,15084,16260];
pre4= [2030,3902,6640,8215,9152];
preg4= [1901,3224,4622,5757,6581];
opre4= [3027,5771,9591,11858,13127];
mpdc5 = distinguishable_colors(5);
plot(x4, simg4, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, pre4, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x4, preg4, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, opre4, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, opt4, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('|R|', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = [5000,10000,20000,30000,40000];
simg5= [1.081000,2.133000,4.864000,7.468000,9.888000];
opt5= [3.370000,8.039000,10.989000,13.971000,17.111000];
pre5= [0.015000,0.018000,0.024000,0.031000,0.037000];
preg5= [0.0775,0.1673,0.3199,0.4597,0.5880];
opre5= [0.012000,0.020000,0.041000,0.053000,0.056000];
mpdc5 = distinguishable_colors(5);
plot(x5, simg5, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, pre5, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x5, preg5, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, opre5, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, opt5, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
%set(gca, 'XLim', [25, 125]);
xlabel('|R|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x6 = [5000,10000,20000,30000,40000];
simg6= [4.332031,4.503906,4.523438,4.753906,4.882813];
opt6= [43.390625,85.285156,160.617188,233.699219,304.035156];
pre6= [6.417969,6.480469,6.601563,6.703125,6.820313];
preg6= [17,17,18,18,19];
opre6= [28.472656,28.640625,29.042969,29.242188,29.585938];
mpdc5 = distinguishable_colors(5);
plot(x6, simg6, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, pre6, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x6, preg6, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, opre6, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, opt6, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
%set(gca, 'XLim', [25, 125]);
xlabel('|R|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [1.0,1.5,2.0,2.5,3.0];
simg7= [2348,3296,4241,5595,7134];
opt7= [8142,10579,12560,15128,17195];
pre7= [4143,5539,6640,8017,9169];
preg7= [2331,3487,4622,6306,8097];
opre7= [6029,8026,9591,11431,13025];
mpdc5 = distinguishable_colors(5);
plot(x7, simg7, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, pre7, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x7, preg7, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, opre7, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, opt7, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%

xlabel('Dr', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR','POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = [1.0,1.5,2.0,2.5,3.0];
simg8= [4.813000,4.686000,4.864000,4.705000,4.812000];
opt8= [8.978000,10.013000,10.989000,12.316000,11.831000];
pre8= [0.031000,0.024000,0.024000,0.025000,0.024000];
preg8= [0.3359,0.3393,0.3431,0.3835,0.4563];
opre8= [0.019000,0.029000,0.041000,0.044000,0.078000];
mpdc5 = distinguishable_colors(5);
plot(x8, simg8, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, pre8, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x8, preg8, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, opre8, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, opt8, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = [1.0,1.5,2.0,2.5,3.0];
simg9= [4.644531,4.640625,4.523438,4.625000,4.519531];
opt9= [66.554688,107.191406,160.617188,229.566406,327.441406];
pre9= [6.589844,6.593750,6.601563,6.589844,6.585938];
preg9= [17,17,18,19,19];
opre9= [28.812500,28.937500,29.042969,29.253906,29.347656];
mpdc5 = distinguishable_colors(5);
plot(x9, simg9, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, pre9, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x9, preg9, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, opre9, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, opt9, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [20,30,50,100,200];
simg10= [7723,6211,4241,2348,405];
opt10= [14110,13334,12560,12767,8149];
pre10= [8775,7692,6640,6071,3586];
preg10= [8161,6673,4622,2572,380];
opre10= [12769,11084,9591,8332,4704];
mpdc5 = distinguishable_colors(5);
plot(x10, simg10, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, pre10, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x10, preg10, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, opre10, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, opt10, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('Grid', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = [20,30,50,100,200];
simg11= [4.956000,4.860000,4.864000,4.944000,4.862000];
opt11= [11.047000,9.657000,10.989000,10.752000,8.785000];
pre11= [0.024000,0.028000,0.024000,0.026000,0.023000];
preg11= [0.3816,0.2813,0.2956,0.2959,0.2431];
opre11= [0.038000,0.040000,0.041000,0.036000,0.044000];
mpdc5 = distinguishable_colors(5);
plot(x11, simg11, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, pre11, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x11, preg11, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, opre11, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, opt11, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
%set(gca, 'XLim', [25, 125]);
xlabel('Grid', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = [20,30,50,100,200];
simg12= [4.492188,4.644531,4.523438,4.496094,4.726563];
opt12= [195.074219,170.277344,160.617188,149.824219,65.492188];
pre12= [5.046875,5.406250,6.601563,12.070313,34.054688];
preg12= [18,18,18,17,17];
opre12= [9.980469,14.750000,29.042969,33.582031,40.386719];
mpdc5 = distinguishable_colors(5);
plot(x12, simg12,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, pre12, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x12, preg12, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, opre12, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, opt12, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x12 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x12);
%set(gca, 'XLim', [25, 125]);
xlabel('Grid', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%13---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x13 = [12,24,48,96,144];
simg13= [4273,4420,4241,4238,4029];
opt13= [11987,12655,12560,12364,11886];
pre13= [7846,7421,6640,5965,5512];
preg13= [4904,4980,4622,4470,4149];
opre13= [11191,10951,9591,8256,7375];
mpdc5 = distinguishable_colors(5);
plot(x13, simg13, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, pre13, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x13, preg13, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, opre13, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, opt13, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x13 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x13);
%

xlabel('Time Slot', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%14---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x14 =  [12,24,48,96,144];
simg14= [5.085000,5.072000,4.864000,4.725000,4.654000];
opt14= [13.552000,11.251000,10.989000,9.492000,8.745000];
pre14= [0.025000,0.025000,0.024000,0.040000,0.024000];
preg14= [1.1450,0.6130,0.2615,0.1618,0.1193];
opre14= [0.029000,0.049000,0.041000,0.037000,0.031000];
mpdc5 = distinguishable_colors(5);
plot(x14, simg14, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, pre14, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x14, preg14, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, opre14, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, opt14, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x14 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x14);
%set(gca, 'XLim', [25, 125]);
xlabel('Time Slot', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR','POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%15---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x15 =  [12,24,48,96,144];
simg15= [4.742188,4.484375,4.523438,4.515625,4.507813];
opt15= [524.535156,301.890625,160.617188,86.195313,59.578125];
pre15= [5.210938,5.675781,6.601563,8.425781,10.261719];
preg15= [25,21,18,17,17];
opre15= [12.171875,17.304688,29.042969,53.890625,77.957031];
mpdc5 = distinguishable_colors(5);
plot(x15, simg15,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, pre15, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x15, preg15, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, opre15, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, opt15, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x15 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x15);
%set(gca, 'XLim', [25, 125]);
xlabel('Time Slot', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%16---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x16 = [0.25,0.375,0.5,0.625,0.75];
simg16= [4289,4226,4241,4264,4127];
opt16= [12413,12370,12560,12251,12007];
pre16= [6515,6579,6640,6530,6239];
preg16= [4699,4666,4622,4674,4493];
opre16= [9462,9522,9591,9360,9086];
mpdc5 = distinguishable_colors(5);
plot(x16, simg16, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, pre16, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x16, preg16, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, opre16, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, opt16, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x16 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x16);
%

xlabel('\mu', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%17---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x17 = [0.25,0.375,0.5,0.625,0.75];
simg17= [5.264000,5.097000,4.864000,4.503000,4.398000];
opt17= [10.266000,10.303000,10.989000,10.215000,10.771000];
pre17= [0.025000,0.024000,0.024000,0.025000,0.024000];
preg17= [0.3644,0.2535,0.2902,0.2310,0.2884];
opre17= [0.045000,0.042000,0.041000,0.039000,0.040000];
mpdc5 = distinguishable_colors(5);
plot(x17, simg17, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, pre17, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x17, preg17, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, opre17, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, opt17, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x17 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x17);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%18---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x18 = [0.25,0.375,0.5,0.625,0.75];
simg18= [4.640625,4.636719,4.523438,4.640625,4.640625];
opt18= [163.128906,160.582031,160.617188,156.457031,150.785156];
pre18= [6.593750,6.582031,6.601563,6.601563,6.597656];
preg18= [19,18,18,17,17];
opre18= [29.054688,29.011719,29.042969,28.996094,29.062500];
mpdc5 = distinguishable_colors(5);
plot(x18, simg18,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, pre18, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x18, preg18, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, opre18, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, opt18, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x18 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x18);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%19---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x19 = [0.25,0.375,0.5,0.625,0.75];
simg19= [4058,4112,4241,4315,4341];
opt19= [12290,12284,12560,12442,12479];
pre19= [6610,6512,6640,6516,6497];
preg19= [4472,4513,4622,4726,4799];
opre19= [9416,9360,9591,9418,9420];
mpdc5 = distinguishable_colors(5);
plot(x19, simg19, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, pre19, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x19, preg19, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, opre19, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, opt19, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x19 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x19);
%

xlabel('\sigma', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%20---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x20 = [0.25,0.375,0.5,0.625,0.75];
simg20= [4.488000,4.728000,4.864000,4.883000,4.846000];
opt20= [9.991000,10.695000,10.989000,10.195000,10.005000];
pre20= [0.024000,0.025000,0.024000,0.032000,0.024000];
preg20= [0.3157,0.3432,0.3607,0.3194,0.3477];
opre20= [0.049000,0.051000,0.041000,0.054000,0.045000];
mpdc5 = distinguishable_colors(5);
plot(x20, simg20, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, pre20, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x20, preg20, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, opre20, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, opt20, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x20 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x20);
%set(gca, 'XLim', [25, 125]);
xlabel('\sigma', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%21---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x21 = [0.25,0.375,0.5,0.625,0.75];
simg21= [4.722656,4.636719,4.523438,4.503906,4.507813];
opt21= [162.394531,156.738281,160.617188,158.968750,158.949219];
pre21= [6.585938,6.589844,6.601563,6.589844,6.585938];
preg21= [17,17,18,18,18];
opre21= [28.996094,29.046875,29.042969,29.050781,29.031250];
mpdc5 = distinguishable_colors(5);
plot(x21, simg21,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, pre21, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x21, preg21, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, opre21, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, opt21, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x21 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x21);
%set(gca, 'XLim', [25, 125]);
xlabel('\sigma', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR','POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%22---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x22 = [0.25,0.375,0.5,0.625,0.75];
simg22= [13809,12870,4241,688,41];
opt22= [18653,18556,12560,3461,445];
pre22= [9750,9746,6640,1700,215];
preg22= [17602,14697,4622,656,30];
opre22= [16837,13912,9591,2392,274];
mpdc5 = distinguishable_colors(5);
plot(x22, simg22, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, pre22, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x22, preg22, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, opre22, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, opt22, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x22 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x22);
%

xlabel('mean', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%23---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x23 = [0.25,0.375,0.5,0.625,0.75];
simg23= [1.323000,3.615000,4.864000,4.829000,4.712000];
opt23= [18.656000,12.532000,10.989000,7.775000,7.225000];
pre23= [0.023000,0.024000,0.024000,0.028000,0.024000];
preg23= [0.5164,0.8199,0.2723,0.2533,0.3032];
opre23= [0.064000,0.073000,0.041000,0.010000,0.006000];
mpdc5 = distinguishable_colors(5);
plot(x23, simg23, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, pre23, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x23, preg23, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, opre23, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, opt23, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x23 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x23);
%set(gca, 'XLim', [25, 125]);
xlabel('mean', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%24---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x24 = [0.25,0.375,0.5,0.625,0.75];
simg24= [4.628906,4.515625,4.523438,4.496094,4.734375];
opt24= [890.558594,566.992188,160.617188,22.921875,8.152344];
pre24= [6.593750,6.589844,6.601563,6.605469,6.589844];
preg24= [25,21,18,17,17];
opre24= [29.304688,29.277344,29.042969,28.664063,28.636719];
mpdc5 = distinguishable_colors(5);
plot(x24, simg24,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, pre24, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x24, preg24, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, opre24, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, opt24, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x24 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x24);
%set(gca, 'XLim', [25, 125]);
xlabel('mean', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%25---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x25 = [0.25,0.375,0.5,0.625,0.75];
simg25= [2961,3738,4241,4581,5004];
opt25= [11314,12120,12560,12603,12852];
pre25= [6252,6633,6640,6551,6606];
preg25= [3172,4076,4622,5026,5484];
opre25= [9141,9610,9591,9495,9420];
mpdc5 = distinguishable_colors(5);
plot(x25, simg25, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, pre25, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x25, preg25, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, opre25, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, opt25, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x25 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x25);
%

xlabel('cov', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%26---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x26 = [0.25,0.375,0.5,0.625,0.75];
simg26= [4.850000,4.764000,4.864000,4.666000,4.744000];
opt26= [8.947000,9.619000,10.989000,11.360000,12.288000];
pre26= [0.025000,0.033000,0.024000,0.024000,0.027000];
preg26= [0.3111,0.3185,0.3267,0.3086,0.3737];
opre26= [0.035000,0.042000,0.041000,0.040000,0.034000];
mpdc5 = distinguishable_colors(5);
plot(x26, simg26, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, pre26, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x26, preg26, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, opre26, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, opt26, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x26 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x26);
%set(gca, 'XLim', [25, 125]);
xlabel('cov', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%27---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x27 = [0.25,0.375,0.5,0.625,0.75];
simg27= [4.496094,4.644531,4.523438,4.511719,4.515625];
opt27= [138.816406,152.191406,160.617188,162.886719,170.078125];
pre27= [6.589844,6.597656,6.601563,6.601563,6.593750];
preg27= [17,17,18,18,18];
opre27= [28.988281,28.968750,29.042969,29.078125,29.105469];
mpdc5 = distinguishable_colors(5);
plot(x27, simg27,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, pre27, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x27, preg27, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, opre27, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, opt27, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x27 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x27);
%set(gca, 'XLim', [25, 125]);
xlabel('cov', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%28---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x28 = [0.28,0.375,0.5,0.628,0.75];
simg28= [3919,3976,3952,4091,4060];
opt28= [12676,12931,12858,13291,13113];
pre28= [7981,8359,8362,8731,8836];
preg28= [3825,3799,3784,3800,3704];
opre28= [11198,11632,11627,11947,11993];
mpdc5 = distinguishable_colors(5);
plot(x28, simg28, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, pre28, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x28, preg28, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, opre28, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, opt28, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x28 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x28);
%

xlabel('\alpha', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%29---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x29 = [0.25,0.375,0.5,0.625,0.75];
simg29= [3.980000,4.214000,4.405000,4.587000,4.536000];
opt29= [16.137000,16.816000,15.360000,15.157000,14.903000];
pre29= [0.031000,0.027000,0.024000,0.024000,0.023000];
preg29= [0.7207,0.6844,0.8080,0.7982,0.8472];
opre29= [0.040000,0.037000,0.030000,0.041000,0.041000];
mpdc5 = distinguishable_colors(5);
plot(x29, simg29, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, pre29, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x29, preg29, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, opre29, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, opt29, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x29 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x29);
%set(gca, 'XLim', [25, 125]);
xlabel('\alpha', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%30---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x30 = [0.25,0.375,0.5,0.625,0.75];
simg30= [4.628906,4.632813,4.730469,4.523438,4.738281];
opt30= [532.046875,564.750000,604.835938,672.402344,714.218750];
pre30= [6.593750,6.570313,6.589844,6.585938,6.593750];
preg30= [25,25,34,36,36];
opre30= [29.074219,29.121094,29.109375,29.097656,29.085938];
mpdc5 = distinguishable_colors(5);
plot(x30, simg30,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, pre30, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x30, preg30, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, opre30, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, opt30, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x30 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x30);
%set(gca, 'XLim', [25, 125]);
xlabel('\alpha', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%31---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x31 = [20*10^4,40*10^4,60*10^4,80*10^4,100*10^4];
simg31= [44096, 88527, 133020, 177495, 222645];
opt31= [129336,258567,387918,519798,651212];
pre31= [101944,217467,336010,457770,581408];
preg31= [50871, 102222, 153311, 205004, 257198];
opre31= [119503,246499,373992,504096,635285];
mpdc5 = distinguishable_colors(5);
plot(x31, simg31, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x31, pre31, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x31, preg31, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x31, opre31, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x31, opt31, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x31 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x31);
%

xlabel('|W|(|R|)', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%32---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x32 = x31;
simg32= [629.7497, 2529.1897, 6643.1653, 11192.4522, 15995.3228];
pre32= [0.291000,0.597000,0.889000,1.119000,1.425000];
preg32= [22.8989, 130.8578, 298.4217, 549.5707, 878.8211];
opt32=[22.0630,29.6937,34.5961,41.0764,42.5560];
opre32= [0.351000,0.475000,0.582,0.991000,0.885000];
mpdc5 = distinguishable_colors(5);
plot(x32, simg32, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x32, pre32, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x32, preg32, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x32, opre32, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x32, opt32, '*-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x32 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x32);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|(|R|)', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%33---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x33 = x31;
simg33= [25, 34, 52, 52, 52];
pre33= [17.296875,21.531250,26.109375,30.683594,35.246094];
preg33= [89, 305, 594, 1170, 2322];
opre33= [46.941406,59.351563,71.804688,84.617188,96.691406];
opt33=[311,599,599,599,599];
mpdc5 = distinguishable_colors(5);
plot(x33, simg33,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x33, pre33, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x33, preg33, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x33, opre33, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x33, opt33, '*-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x33 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x33);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|(|R|)', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

