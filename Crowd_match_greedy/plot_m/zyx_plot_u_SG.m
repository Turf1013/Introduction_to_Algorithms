



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [100, 200, 500, 1000, 5000];
extended1 = [197.611805, 318.891679, 768.529872, 1209.223733, 2405.859094];
fgoag1 = [240.322888, 420.047921, 1101.181068, 1676.176073, 3524.169013];
fgoa1 = [286.515031, 467.158433, 1161.680062, 1823.118194, 3492.941151];
simg1 = [291.602875, 516.826657, 1212.567266, 1880.164884, 3590.946777];
opt1 = [295.80842, 522.055124, 1231.899607, 1924.885903, 3900.689295];
mpdc5 = distinguishable_colors(5);
plot(x1, extended1, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, fgoa1, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, fgoag1, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, simg1, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, opt1, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%

xlabel('|W|', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [500, 1000, 2500, 5000, 10000];
extended2 = [356.596809, 531.838832, 768.529872, 668.267312, 936.835299];
fgoag2 = [526.411413, 754.758214, 1101.181068, 921.819641, 1357.057858];
fgoa2 = [540.638652, 813.266678, 1161.680062, 1054.844769, 1322.781906];
simg2 = [560.304065, 841.934985, 1212.567266, 1102.09641, 1438.455322];
opt2 = [592.685407, 877.581914, 1231.899607, 1110.326028, 1448.000611];
%旋转
set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
%
mpdc5 = distinguishable_colors(5);
plot(x2, extended2, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, fgoa2, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, fgoag2, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, simg2, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, opt2, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);




%调字体
xlabel('|T|', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [1, 2, 5, 10, 20];
extended3 = [520.466098, 636.4648, 768.529872, 664.783536, 664.783536];
fgoag3 = [792.343818, 895.770951, 1101.181068, 925.392755, 1022.215866];
fgoa3 = [792.730311, 957.828458, 1161.680062, 1004.414351, 1004.414351];
simg3 = [796.812213, 999.920702, 1212.567266, 1060.805079, 1060.805079];
opt3 = [869.511414, 1049.064063, 1231.899607, 1089.821661, 1089.821661];
set(gca, 'FontSize', fontsize, 'Xtick', x3);
%
mpdc5 = distinguishable_colors(5);
plot(x3, extended3, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, fgoa3, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, fgoag3, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, simg3, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, opt3, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

xlabel('c_w', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [10, 15, 20, 25, 30];
extended4 = [186.809256, 502.295194, 768.529872, 1137.270106, 1498.371359];
fgoag4 = [284.638968, 749.982787, 1101.181068, 1512.499289, 1895.753627];
fgoa4 = [288.184519, 769.61938, 1161.680062, 1668.896586, 2145.092048];
simg4 = [299.414647, 787.331526, 1212.567266, 1788.990036, 2328.294074];
opt4 = [299.414647, 791.901165, 1231.899607, 1828.724349, 2421.134532];
mpdc5 = distinguishable_colors(5);
plot(x4, extended4, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, fgoa4, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, fgoag4, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, simg4, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, opt4, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x4);
%set(gca, 'XLim', [25, 125]);
xlabel('r_w', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = [100,200,500,1000,5000];
extended5 = [0.014926, 0.020062, 0.043964, 0.07137, 0.249374];
fgoag5 = [0.014222, 0.012105, 0.031983, 0.063281, 0.508116];
fgoa5 = [0.268007, 1.342087, 28.790276, 33.248518, 227.014344];
simg5 = [0.019434, 0.03114, 0.066435, 0.120622, 0.431863];
mpdc4 = distinguishable_colors(4);
plot(x5, extended5, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, fgoa5, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, fgoag5, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, simg5, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x6 = [500, 1000, 2500, 5000, 10000];
extended6 = [0.011913, 0.023575, 0.043964, 0.071615, 0.132697];
fgoag6 = [0.007578, 0.012595, 0.031983, 0.058414, 0.108687];
fgoa6 = [0.485085, 1.55269, 28.790276, 24.361878, 31.077266];
simg6 = [0.015996, 0.030567, 0.066435, 0.11182, 0.183086];
mpdc4 = distinguishable_colors(4);
plot(x6, extended6, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, fgoa6, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, fgoag6, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, simg6, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [1, 2, 5, 10, 20];
extended7 = [0.016693, 0.023659, 0.043964, 0.069038, 0.114435];
fgoag7 = [0.008688, 0.019986, 0.031983, 0.067017, 0.172604];
fgoa7 = [0.277915, 1.74986, 28.790276, 37.461178, 57.336594];
simg7 = [0.020895, 0.030821, 0.066435, 0.108786, 0.170823];
mpdc4 = distinguishable_colors(4);
plot(x7, extended7, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, fgoa7, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, fgoag7, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, simg7, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x7);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = [10, 15, 20, 25, 30];
extended8 = [0.041663, 0.042715, 0.043964, 0.042785, 0.043923];
fgoag8 = [0.022801, 0.036564, 0.031983, 0.038269, 0.052576];
fgoa8 = [19.017261, 22.691727, 28.790276, 34.26606, 35.6512];
simg8 = [0.058312, 0.056853, 0.066435, 0.048571, 0.066014];
mpdc4 = distinguishable_colors(4);
plot(x8, extended8, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, fgoa8, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, fgoag8, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, simg8, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x8);
%set(gca, 'XLim', [25, 125]);
xlabel('r_w', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = [100, 200, 500, 1000, 5000];
extended9 = [17.09375, 17.09375, 17.2421875, 17.6796875, 20.15625];
fgoag9 = [17.09765625, 17.09765625, 17.46484375, 17.59765625, 19.48046875];
fgoa9 = [17.10546875, 17.10546875, 17.47265625, 17.57421875, 19.48828125];
simg9 = [17.08984375, 17.08984375, 17.23828125, 17.53125, 19.5];
mpdc4 = distinguishable_colors(4);
plot(x9, extended9, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, fgoa9, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, fgoag9, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, simg9, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [500, 1000, 2500, 5000, 10000];
extended10 = [17.09375, 17.09375, 17.2421875, 17.5625, 18.41015625];
fgoag10 = [17.09765625, 17.09765625, 17.46484375, 17.625, 18.390625];
fgoa10 = [17.10546875, 17.10546875, 17.47265625, 17.6328125, 18.3984375];
simg10 = [17.08984375, 17.08984375, 17.23828125, 17.4765625, 18.40625];
mpdc4 = distinguishable_colors(4);
plot(x10, extended10, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, fgoa10, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, fgoag10, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, simg10, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = [1, 2, 5, 10, 20];
extended11 = [17.09375, 17.09375, 17.2421875, 17.55078125, 18.40625];
fgoag11 = [17.09765625, 17.09765625, 17.46484375, 17.50390625, 18.2109375];
fgoa11 = [17.10546875, 17.10546875, 17.47265625, 17.51171875, 18.21875];
simg11 = [17.08984375, 17.08984375, 17.23828125, 17.50390625, 18.1875];
mpdc4 = distinguishable_colors(4);
plot(x11, extended11, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, fgoa11, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, fgoag11, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, simg11, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x11);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = [10, 15, 20, 25, 30];
extended12 = [17.40234375, 17.2421875, 17.2421875, 17.2421875, 17.2421875];
fgoag12 = [17.23828125, 17.46484375, 17.46484375, 17.46484375, 17.46484375];
fgoa12 = [17.24609375, 17.47265625, 17.47265625, 17.47265625, 17.47265625];
simg12 = [17.203125, 17.23828125, 17.23828125, 17.23828125, 17.23828125];
mpdc4 = distinguishable_colors(4);
plot(x12, extended12, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, fgoa12, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, fgoag12, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, simg12, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x12);
%set(gca, 'XLim', [25, 125]);
xlabel('r_w', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%13---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x13 = [0.1,0.3,0.5,0.7,0.9];
extended13 = [80.837819, 374.532644, 768.529872, 1112.087476, 1584.583827];
fgoag13 = [220.236211, 660.70859, 1101.181068, 1477.722218, 1854.263467];
fgoa13 = [232.33601, 697.007977, 1161.680062, 1560.913051, 1960.146158];
simg13 = [242.513457, 727.540298, 1212.567266, 1630.152729, 2047.738319];
opt13 = [246.379934, 739.139714, 1231.899607, 1641.752145, 2051.604796];
mpdc5 = distinguishable_colors(5);
plot(x13, extended13, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, fgoa13, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, fgoag13, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, simg13, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, opt13, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x13);
%set(gca, 'XLim', [25, 125]);
xlabel('\delta_w', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%14---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x14 = [2,4,6,8,10];

extended14 = [144.419569, 465.898814, 768.529872, 1127.783093, 1417.089782];
fgoag14 = [228.88921, 705.109628, 1101.181068, 1468.980398, 1777.644772];
fgoa14 = [231.47133, 738.871626, 1161.680062, 1626.766139, 2047.151946];
simg14 = [231.47133, 757.865173, 1212.567266, 1734.84476, 2196.131483];
opt14 = [231.597771, 764.015691, 1231.899607, 1781.843583, 2252.268203];
mpdc5 = distinguishable_colors(5);
plot(x14, extended14, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, fgoa14, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, fgoag14, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, simg14, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, opt14, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x14);
%set(gca, 'XLim', [25, 125]);
xlabel('d', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%15---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x15 = [2,5,10,20,50];
set(gca, 'FontSize', fontsize, 'Xtick', x15);
%set(gca, 'XLim', [25, 125]);

extended15 = [165.074363, 463.1978, 768.529872, 1494.766308, 4944.192721];
fgoag15 = [296.235177, 598.089886, 1101.181068, 2107.363435, 5125.910531];
fgoa15 = [312.543976, 630.97001, 1161.680062, 2223.100169, 5407.360488];
simg15 = [330.148725, 661.055679, 1212.567266, 2315.590445, 5624.659976];
opt15 = [335.482676, 671.639026, 1231.899607, 2352.420773, 5713.984267];
mpdc5 = distinguishable_colors(5);
plot(x15, extended15, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, fgoa15, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, fgoag15, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, simg15, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, opt15, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
xlabel('Pt', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%16---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x16 = [0.1,0.3,0.5,0.7,0.9];
extended16 = [0.039492, 0.041254, 0.043964, 0.047009, 0.046569];
fgoag16 = [0.034272, 0.033262, 0.031983, 0.028017, 0.02872];
fgoa16 = [29.162053, 28.799041, 28.790276, 27.200532, 26.598999];
simg16 = [0.056271, 0.066132, 0.066435, 0.034448, 0.065469];
mpdc4 = distinguishable_colors(4);
plot(x16, extended16, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, fgoa16, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, fgoag16, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, simg16, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x16);
%set(gca, 'XLim', [25, 125]);
xlabel('\delta_w', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%17---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x17 = [2,4,6,8,10];

extended17 = [0.041555, 0.040912, 0.043964, 0.043075, 0.044347];
fgoag17 = [0.021199, 0.037604, 0.031983, 0.042011, 0.045342];
fgoa17 = [16.3634, 25.746858, 28.790276, 30.712738, 32.09587];
simg17 = [0.058366, 0.060144, 0.066435, 0.064113, 0.069411];
mpdc4 = distinguishable_colors(4);
plot(x17, extended17, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, fgoa17, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, fgoag17, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, simg17, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x17);
%set(gca, 'XLim', [25, 125]);
xlabel('d', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%18---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x18 = [2,5,10,20,50];
extended18 = [0.042503, 0.052541, 0.043964, 0.040635, 0.04741];
fgoag18 = [0.037186, 0.027863, 0.031983, 0.032623, 0.036221];
fgoa18 = [28.98072, 28.903795, 28.790276, 26.612004, 26.608329];
simg18 = [0.061564, 0.064991, 0.066435, 0.066152, 0.066064];
mpdc4 = distinguishable_colors(4);
plot(x18, extended18, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, fgoa18, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, fgoag18, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, simg18, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x18);
%set(gca, 'XLim', [25, 125]);
xlabel('Pt', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%19---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x19 = [0.1,0.3,0.5,0.7,0.9];

extended19 = [17.2421875, 17.2421875, 17.2421875, 17.2421875, 17.2421875];
fgoag19 = [17.46484375, 17.46484375, 17.46484375, 17.46484375, 17.46484375];
fgoa19 = [17.47265625, 17.47265625, 17.47265625, 17.47265625, 17.47265625];
simg19 = [17.23828125, 17.23828125, 17.23828125, 17.23828125, 17.23828125];
mpdc4 = distinguishable_colors(4);
plot(x19, extended19, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, fgoa19, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, fgoag19, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, simg19, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x19);
%set(gca, 'XLim', [25, 125]);
xlabel('\delta_w', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%20---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x20 = [2,4,6,8,10];
extended20 = [17.2421875, 17.2421875, 17.2421875, 17.2421875, 17.2421875];
fgoag20 = [17.46484375, 17.46484375, 17.46484375, 17.46484375, 17.46484375];
fgoa20 = [17.47265625, 17.47265625, 17.47265625, 17.47265625, 17.47265625];
simg20 = [17.23828125, 17.23828125, 17.23828125, 17.23828125, 17.23828125];
mpdc4 = distinguishable_colors(4);
plot(x20, extended20, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, fgoa20, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, fgoag20, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, simg20, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x20);
%set(gca, 'XLim', [25, 125]);
xlabel('d', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%21---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x21 = [2,5,10,20,50];
extended21 = [17.2421875, 17.2421875, 17.2421875, 17.2421875, 17.2421875];
fgoag21 = [17.46484375, 17.46484375, 17.46484375, 17.46484375, 17.46484375];
fgoa21 = [17.47265625, 17.47265625, 17.47265625, 17.47265625, 17.47265625];
simg21 = [17.23828125, 17.23828125, 17.23828125, 17.23828125, 17.23828125];
mpdc4 = distinguishable_colors(4);
plot(x21, extended21, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, fgoa21, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, fgoag21, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, simg21, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x21);
%set(gca, 'XLim', [25, 125]);
xlabel('Pt', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%22-----------scalability1---------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x22 = [10000, 20000, 30000, 40000, 50000, 100000];
mpdc4 = distinguishable_colors(4);

extended22 = [1006.639300, 1062.041500, 1116.528900, 986.223600, 1056.261900, 1062.601000];
fgoa22 = [1875.889600, 1870.235500, 2088.724300, 2020.003900, 2249.617300, 2216.588400];
fgoag22 = [4100.950200, 4651.375300, 4953.189600, 4816.767900, 5254.662300, 5401.334700];

plot(x22, extended22, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize',markersize);
plot(x22, fgoa22, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, fgoag22, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x22);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('|W|=0.5K', '|W|=1K', '|W|=2.5K', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%23---------------------scalability2------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x23 = [10000, 20000, 30000, 40000, 50000, 100000];
mpdc4 = distinguishable_colors(4);

extended23 = [0.128009, 0.230577, 0.353824, 0.485098, 0.639291, 1.463814];
fgoa23 = [0.213996, 0.399899, 0.495085, 0.826921, 1.030697, 2.114989];
fgoag23 = [0.465601, 0.941681, 1.303246, 1.577799, 2.065808, 4.095333];

plot(x23, extended23, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, fgoa23, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, fgoag23, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x23);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('|W|=0.5K', '|W|=1K', '|W|=2.5K', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%24----------------------scalability3-----------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x24 = [10000, 20000, 30000, 40000, 50000, 100000];
mpdc4 = distinguishable_colors(4);

extended24 = [18.4140625, 19.58203125, 19.484375, 22.27734375, 22.2578125, 27.6640625];
fgoa24 = [18.44921875, 19.7890625, 19.79296875, 22.4453125, 22.45703125, 27.796875];
fgoag24 = [18.984375, 20.41015625, 20.1640625, 23.66796875, 22.78125, 28.375];

plot(x24, extended24, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, fgoa24, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, fgoag24, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x24);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('|W|=0.5K', '|W|=1K', '|W|=2.5K', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%%
%25---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x25 = [1.25,2.5,3.75,5,6.25];


opt25 = [2002.302900, 2116.823600, 1980.451400, 2038.908500, 2031.055100];
simg25 = [1975.822500, 2087.162100, 1947.245900, 1999.767400, 1994.354700];
extended25 = [1136.323100, 1245.610300, 1181.696933, 1221.418300, 1251.889633];
fgoa25 = [1872.616200, 1975.462700, 1833.891700, 1895.337800, 1875.089900];
fgoag25 = [1683.146100, 1785.686300, 1585.161700, 1707.061700, 1687.628700];

mpdc5 = distinguishable_colors(5);
plot(x25, extended25, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, fgoa25, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, fgoag25, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, simg25, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, opt25, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x25);
%set(gca, 'XLim', [25, 125]);
xlabel('\sigma', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%26---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x26 = x25;
%%opt = [40.248984, 45.957999, 37.050014, 45.569811, 43.989202];
simg26 = [0.183232, 0.1845, 0.191104, 0.186402, 0.160385];
extended26 = [0.107377, 0.123711, 0.102744, 0.101789, 0.104901];
fgoa26 = [302.011961, 385.136538, 414.322935, 207.599079, 245.727704];
fgoag26 = [0.082258, 0.138518, 0.093105, 0.093426, 0.083935];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mpdc4 = distinguishable_colors(4);
plot(x26, extended26, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, fgoa26, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, fgoag26, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, simg26, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x26);
%set(gca, 'XLim', [25, 125]);
xlabel('\sigma', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%27---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x27 =x25;
				
			
			
%%opt = [18.32421875, 18.33203125, 18.16796875, 18.171875, 18.171875];
simg27 = [17.75390625, 17.75390625, 17.75390625, 17.75390625, 17.75390625];
extended27 = [18.11328125, 18.11328125, 17.8203125, 17.82421875, 17.84375];
fgoa27 = [17.79296875, 17.8984375, 17.8984375, 17.8984375, 17.91796875];
fgoag27 = [17.78515625, 17.890625, 17.890625, 17.890625, 17.91015625];

mpdc4 = distinguishable_colors(4);
plot(x27, extended27, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, fgoa27, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, fgoag27, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, simg27, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x27);
%set(gca, 'XLim', [25, 125]);
xlabel('\sigma', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


