



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
x1 = [100, 200, 500, 1000, 5000];
extended1 = [197.611805, 318.891679, 768.529872, 1209.223733, 2405.859094];
fgoag1 = [273.783765, 468.877123, 1182.152256, 1794.07334, 3524.169013];
fgoa1 = [248.471074, 425.882148, 1109.432071, 1702.962379, 3400.929076];
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
fgoag2 = [554.014381, 813.669566, 1182.152256, 1026.015039, 1357.057858];
fgoa2 = [533.637122, 760.840275, 1109.432071, 947.190089, 1212.173855];
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
fgoag3 = [792.343818, 950.525737, 1182.152256, 1034.452218, 1022.215866];
fgoa3 = [792.343818, 913.86063, 1109.432071, 939.694909, 939.694909];
simg3 = [796.812213, 999.920702, 1212.567266, 1060.805079, 1060.805079];
opt3 = [869.511414, 1049.064063, 1231.899607, 1089.821661, 1089.821661];%旋转
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
fgoag4 = [298.267394, 779.636228, 1182.152256, 1678.977277, 2185.758735];
fgoa4 = [285.78622, 749.540405, 1109.432071, 1550.517243, 1956.353834];
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
fgoag5 = [0.92942, 1.767989, 6.099613, 17.7916, 294.549605];
fgoa5 = [5.210805, 17.372205, 587.333805, 1004.039344, 4000.377273];
simg5 = [0.019434, 0.03114, 0.066435, 0.120622, 0.431863];mpdc4 = distinguishable_colors(4);
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
fgoag6 = [0.828731, 1.796137, 6.099613, 16.635408, 59.492509];
fgoa6 = [3.479875, 46.303124, 587.333805, 471.30723, 819.091746];
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
fgoag7 = [0.982601, 1.764573, 6.099613, 15.83553, 49.5231];
fgoa7 = [6.069974, 33.198866, 587.333805, 875.287595, 1542.014538];
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
fgoag8 = [4.445205, 5.363715, 6.099613, 6.496306, 7.50253];
fgoa8 = [380.944828, 456.510868, 587.333805, 698.779603, 837.932773];
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
fgoag9 = [17.09765625, 17.09765625, 17.46484375, 17.6328125, 19.48046875];
fgoa9 = [17.10546875, 17.10546875, 17.47265625, 17.61328125, 19.62109375];
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
fgoa10 = [17.10546875, 17.10546875, 17.47265625, 17.6484375, 18.5078125];
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
fgoag11 = [17.09765625, 17.09765625, 17.46484375, 17.53515625, 18.2109375];
fgoa11 = [17.10546875, 17.10546875, 17.47265625, 17.54296875, 18.21875];
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
fgoag12 = [17.2421875, 17.46484375, 17.46484375, 17.46484375, 17.46484375];
fgoa12 = [17.27734375, 17.47265625, 17.47265625, 17.47265625, 17.47265625];
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
fgoag13 = [236.430459, 709.291291, 1182.152256, 1580.922837, 1942.76345];
fgoa13 = [221.886413, 665.65919, 1109.432071, 1487.96375, 1866.495534];
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
fgoag14 = [231.47133, 745.334258, 1182.152256, 1626.71588, 2039.720551];
fgoa14 = [228.88921, 708.321679, 1109.432071, 1507.26308, 1838.107947];
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
fgoag15 = [317.269985, 639.105535, 1182.152256, 2216.922149, 5506.919258];
fgoa15 = [297.995106, 602.283968, 1109.432071, 2123.72828, 5166.616903];
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
fgoag16 = [5.769783, 6.019055, 6.099613, 5.844987, 5.858628];
fgoa16 = [586.928448, 587.142874, 587.333805, 589.027226, 588.719537];
simg16 = [0.056271, 0.066132, 0.066435, 0.034448, 0.065469];
%%opt16 = [4.769516, 8.082016, 17.0977, 20.4961,
%%50.1211];%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
fgoag17 = [6.01983, 5.863925, 6.099613, 6.188724, 6.502201];
fgoa17 = [350.765404, 507.214002, 587.333805, 718.366226, 758.001634];
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
fgoag18 = [5.760417, 5.899624, 6.099613, 5.651027, 6.009758];
fgoa18 = [587.795078, 587.574025, 587.333805, 587.228098, 587.768225];
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

extended22 = [1283.050099,1332.783389,1392.963727,1478.374891,1521.8491,1600.4184];
fgoa22 = [2613.742742,2644.31542,2656.13934,2671.8731,2692.3163,2710.2783];

fgoag22 = [4911.562601,5530.31478,6208.31508,6630.321,7103.756,7603.2341];

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

extended23 = [304.103,979.251,1864.13,2714.32,3541.555,4307.979];
fgoag23 = [838.343,2613.986,4777.207,7103.439,10142.649,13564.964];
fgoa23 = [764.108,2421.569,4278.989,6543.875,9132.763,11210.031];
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

 fgoag24= [4.25,5.12,5.95,6.13,6.94,7.01];
 extended24= [3.80078,4.57382,5.19922,5.7391,6.0134,6.3422];
 fgoa24= [4.57813,5.39815,	6.0718,6.3456,6.7134,6.9833];
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
				

extended25 = [2132.24,1938.45,2142.35,2422.45,2417.58];
fgoag25 = [3147.98,2992.74,3044.32,3258.75,3281.63];
fgoa25 = [3383.61,3122.44,3245.37,3462.78,3498.05];
simg25=[3531.21,3238.85,3345.49,3614.07,3603.99];
opt25 =  [3814.5586,3546.0775,3684.3702,4001.5998,3979.096,];
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
extended26 = [0.099,0.091,0.1,0.102,0.098];
fgoag26 = [0.025,0.086,0.026,0.029,0.021];
fgoa26 = [45.244,43.671,45.315,45.048,44.937];
simg26=[0.026,0.023,0.023,0.031,0.03];
%%opt16 = [4.769516, 8.082016, 17.0977, 20.4961,
%%50.1211];%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
				
			
			
simg27=[3.55078,3.35547,3.54297,3.55078,3.53906];
extended27 = [5.01953,4.79297,4.80469,4.97656,4.78906];
fgoag27 = [4.16797,4.27734,4.34766,4.30859,4.30078];
fgoa27 = [4.63672,4.55859,4.61719,4.59766,4.52344];
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


