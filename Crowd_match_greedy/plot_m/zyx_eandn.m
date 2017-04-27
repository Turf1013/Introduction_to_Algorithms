
fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%1---------------------------------------------------------Exp
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [1,3,5,7,9];
opt1 = [379.003400, 1044.511300, 1453.904100, 1422.543300, 1661.407300];
simg1 = [371.215500, 1029.237000, 1415.760300, 1386.214500, 1628.491800];
extended1 = [134.278733, 509.933433, 812.205767, 797.832800, 976.398700];
fgoa1 = [357.850000, 986.234200, 1353.887500, 1329.699600, 1554.118500];
fgoag1 = [332.695300, 908.320500, 1226.813700, 1213.730300, 1417.249500];

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

xlabel('1/\lambda', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------Exp
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [2,5,10,20,50];
opt2 = [292.153900, 751.866400, 1453.904100, 2675.633900, 7099.604700];
simg2 = [285.435800, 739.500100, 1415.760300, 2630.851600, 6900.342100];
extended2 = [142.717900, 480.825400, 812.205767, 1497.969550, 5551.791025];
fgoa2 = [274.183700, 704.564000, 1353.887500, 2515.583000, 6678.349000];
fgoag2 = [248.596000, 637.454600, 1226.813700, 2287.362800, 6113.693000];

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
xlabel('p_t', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%3---------------------------------------------------------Normal
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [1,3,5,7,9];
opt3 = [990.185100, 1418.124400, 2116.823600, 2925.592700, 3214.977100];
simg3 = [973.431300, 1404.609800, 2087.162100, 2859.331800, 3141.797000];
extended3 = [441.754800, 722.355700, 1245.610300, 1896.840733, 2194.198333];
fgoa3 = [890.326600, 1304.433500, 1975.462700, 2705.062600, 2937.162500];
fgoag3 = [806.557300, 1163.884200, 1785.686300, 2428.102000, 2649.410400];

%旋转
set(gca, 'FontSize', fontsize, 'Xtick', x3);
%
mpdc5 = distinguishable_colors(5);
plot(x3, extended3, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, fgoa3, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, fgoag3, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, simg3, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, opt3, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

xlabel('\mu', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------Normal
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [2,5,10,20,50];
opt4 = [424.136000, 1042.618900, 2116.823600, 4163.880000, 9929.023300];
simg4 = [417.374300, 1017.963400, 2087.162100, 4079.388400, 9741.603300];
extended4 = [208.687150, 639.117050, 1245.610300, 2546.542175, 8266.499775];
fgoa4 = [400.601200, 972.156500, 1975.462700, 3882.545900, 9302.470100];
fgoag4 = [353.681700, 887.945400, 1785.686300, 3523.624500, 8466.598600];

mpdc5 = distinguishable_colors(5);
plot(x4, extended4, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, fgoa4, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, fgoag4, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, simg4, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, opt4, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x4);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = x1;
%%opt5 = [38.06915, 40.919085, 45.66226, 38.848289, 48.265305];
simg5 = [0.183327, 0.183426, 0.195067, 0.18441, 0.199795];
extended5 = [0.092887, 0.108784, 0.140959, 0.118698, 0.12343];
fgoa5 = [377.189094, 447.345741, 405.803841, 222.177828, 274.553812];
fgoag5 = [0.090153, 0.08996, 0.104167, 0.088177, 0.086082];

mpdc4 = distinguishable_colors(4);
plot(x5, extended5, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, fgoa5, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, fgoag5, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, simg5, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
%set(gca, 'XLim', [25, 125]);
xlabel('1/\lambda', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x6 = x2;
%%opt = [42.787809, 39.28372, 45.66226, 41.976923, 52.809973];
simg6 = [0.202994, 0.129689, 0.195067, 0.202117, 0.216967];
extended6 = [0.11586, 0.125368, 0.140959, 0.119124, 0.175187];
fgoa6 = [269.418961, 248.53338, 405.803841, 392.750434, 355.059265];
fgoag6 = [0.10109, 0.122711, 0.104167, 0.096059, 0.102623];

mpdc4 = distinguishable_colors(4);
plot(x6, extended6, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, fgoa6, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, fgoag6, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, simg6, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = x3;
%%opt = [43.327164, 44.473401, 47.137604, 44.299014, 39.522618];
simg7 = [0.205311, 0.182393, 0.187353, 0.190516, 0.21157];
extended7 = [0.083626, 0.114552, 0.123054, 0.144969, 0.131222];
fgoa7 = [406.958078, 359.906875, 361.03626, 408.708971, 183.165304];
fgoag7 = [0.085482, 0.115348, 0.093771, 0.085336, 0.08602];

mpdc4 = distinguishable_colors(4);
plot(x7, extended7, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, fgoa7, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, fgoag7, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, simg7, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x7);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 =x4;
%%opt = [48.506534, 36.531059, 47.137604, 44.751429, 38.609985];
simg8 = [0.187131, 0.185029, 0.187353, 0.219373, 0.185125];
extended8 = [0.122844, 0.117754, 0.123054, 0.131383, 0.150849];
fgoa8 = [302.665349, 286.063071, 361.03626, 460.579617, 260.839796];
fgoag8 = [0.094146, 0.130738, 0.093771, 0.10261, 0.090824];

mpdc4 = distinguishable_colors(4);
plot(x8, extended8, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, fgoa8, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, fgoag8, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, simg8, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x8);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = x1;
%%opt = [18.171875, 18.17578125, 18.17578125, 18.328125, 18.17578125];
simg9 = [17.75390625, 17.75390625, 17.75390625, 17.75390625, 17.75390625];
extended9 = [17.8203125, 17.84375, 17.8515625, 18.11328125, 18.38671875];
fgoa9 = [17.79296875, 17.90625, 17.80078125, 17.80078125, 17.9453125];
fgoag9 = [17.78515625, 17.8984375, 17.79296875, 17.78515625, 17.9375];

mpdc4 = distinguishable_colors(4);
plot(x9, extended9, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, fgoa9, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, fgoag9, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, simg9, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
%set(gca, 'XLim', [25, 125]);
xlabel('1/\lamda', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = x2;
%opt = [18.171875, 18.328125, 18.17578125, 18.33203125, 18.171875];
simg10 = [17.75390625, 17.75390625, 17.75390625, 17.75390625, 17.75390625];
extended10 = [17.8984375, 18.11328125, 17.8515625, 18.171875, 17.84375];
fgoa10 = [17.80859375, 17.8984375, 17.80078125, 17.94921875, 17.8984375];
fgoag10 = [17.80078125, 17.890625, 17.79296875, 17.94140625, 17.890625];

mpdc4 = distinguishable_colors(4);
plot(x10, extended10, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, fgoa10, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, fgoag10, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, simg10, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = x3;
%%opt = [18.16796875, 18.17578125, 18.33203125, 18.16796875, 18.171875];
simg11 = [17.75390625, 17.75390625, 17.75390625, 17.75390625, 17.75390625];
extended11 = [18.34375, 17.9296875, 18.11328125, 18.125, 18.26171875];
fgoa11 = [17.80859375, 17.8125, 17.8984375, 18.01171875, 17.8984375];
fgoag11 = [17.80078125, 17.8046875, 17.890625, 18.00390625, 17.890625];

mpdc4 = distinguishable_colors(4);
plot(x11, extended11, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, fgoa11, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, fgoag11, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, simg11, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x11);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = x4;
%%opt = [18.32421875, 18.328125, 18.33203125, 18.33203125, 18.171875];
simg12 = [17.75390625, 17.75390625, 17.75390625, 17.75390625, 17.75390625];
extended12 = [18.11328125, 18.11328125, 18.11328125, 18.1171875, 18.11328125];
fgoa12 = [17.8984375, 17.8984375, 17.8984375, 17.79296875, 17.8984375];
fgoag12 = [17.890625, 17.890625, 17.890625, 17.78515625, 17.890625];

mpdc4 = distinguishable_colors(4);
plot(x12, extended12, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, fgoa12, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, fgoag12, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, simg12, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x12);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
