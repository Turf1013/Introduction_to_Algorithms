
fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [1,3,5,7,9];
extended1=[179.650000,646.835000,803.676000,1104.770000,1057.100000];
fgoag1 =[458.273000,1173.810000,1417.180000,1725.920000,1735.010000];
fgoa1 = [472.049,1232.33,1469.26,1838.47,1804.28];%%%%%%%%%%%%%%%%%%%%%
simg1=[501.396000,1291.420000,1544.770000,1916.720000,1880.440000];
opt1 =[568.034400,1499.245500,1765.530900,2197.152900,2165.485700];
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

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [2,5,10,20,50];
extended2 =[224.402000,637.678000,803.676000,1067.530000,1289.810000];
fgoag2 =[416.172000,903.265000,1417.180000,1901.330000,2219.230000];
fgoa2 = [432.684,951.006,1469.26,1995.46,2244.51];%%%%%%%%%%%%
simg2=[448.804000,1002.040000,1544.770000,2062.520000,2372.330000];
opt2=[508.042400,1157.315300,1765.530900,2403.455800,2770.181500];
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

%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [2.5,3.75,5,6.25,7.5];
extended3=[1107.180000,1559.420000,1938.450000,2507.940000,2979.580000];
fgoag3=[2021.140000,2526.580000,2992.740000,3595.950000,4208.320000];
fgoa3 = [2132.73,2667.16,3122.44,3797.64,4393.05];%%%%%%%%%%%%%%%%%%%%%
simg3=[2219.940000,2787.990000,3238.850000,3966.370000,4594.350000];
opt3 =[2442.542100,3035.853000,3546.077500,4265.989500,4974.915700];
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

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [2.5,3.75,5,6.25,7.5];
extended4 =[321.110000,1014.570000,1938.450000,3867.510000,13775.000000];
fgoag4 =[585.465000,1553.120000,2992.740000,5720.680000,14345.700000];
fgoa4 = [604.884,1644.48,3122.44,6067.89,15437.8];
simg4=[642.221000,1711.950000,3238.850000,6311.880000,16268.100000];
opt4 =[688.203400,1857.085500,3546.077500,6906.668400,17703.789100];
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
extended5 =[0.080000,0.083000,0.088000,0.086000,0.081000];
fgoa5=[44.343000,44.692000,43.753000,44.668000,43.930000];
fgoag5 = [4.2244	,4.059	,4.3536	,4.5088	,4.101];%%%%%%%%%%%%%%%%%
simg5=[0.030000,0.024000,0.024000,0.025000,0.027000];
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
extended6 =[0.066000,0.070000,0.088000,0.104000,0.126000];
fgoa6 =[42.855000,43.935000,43.753000,44.715000,44.064000];
fgoag6 = [4.3152	,4.1808	,4.536	,5.5416	,4.314
];%%%%%%%%%%%%%%%%%%%%
simg6=[0.047000,0.027000,0.024000,0.024000,0.028000];
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
extended7 =[0.091000,0.083000,0.091000,0.081000,0.087000];
fgoa7=[45.099000,44.632000,43.671000,43.122000,44.221000];
fgoag7 = [5.0934	,4.6244	,4.6212,	4.688	,4.342];%%%%%%%%%%%%%%%%%%%%%%
simg7=[0.027000,0.026000,0.023000,0.047000,0.025000];
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
extended8 = [0.066000,0.057000,0.091000,0.101000,0.102000];
fgoa8=[44.237000,44.650000,43.671000,44.332000,43.599000];
fgoag8 = [4.64033333	,4.18866667,	4.6212,	4.776	,4.356];
simg8=[0.027000,0.028000,0.023000,0.027000,0.026000];
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
extended9 =[5.312500,4.781250,4.789060,4.796880,4.796880];
fgoag9 =[4.292970,4.304690,4.269530,4.382810,4.265630];
fgoa9 = [4.60938,4.53906,4.5,4.50781,4.50391];%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
simg9=[3.527340,3.519530,3.359380,3.347660,3.519530];
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
 fgoa10= [4.14844,4.08594,4.5,4.95703,5];
extended10 =[4.343750,4.523440,4.789060,5.445310,5.242190];
fgoag10=[4.250000,4.394530,4.269530,4.195310,4.304690];
simg10=[3.535160,3.523440,3.359380,3.660160,3.527340];
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
extended11 =[5.136720,4.804690,4.792970,5.125000,5.003910];
fgoag11 =[4.257810,4.230470,4.277340,4.160160,4.234380];
fgoa11 = [4.54297,4.54297,4.55859,4.59766,4.51563];%%%%%%%%%%%%%%%%%%%%%%%%%%%%
simg11=[3.523440,3.367190,3.355470,3.351560,3.355470];
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
extended12=[4.539060,4.332030,4.792970,5.246090,5.253910];
 fgoag12=[4.207030,4.300780,4.277340,4.296880,4.277340];
fgoa12 = [4.05078,4.04297,4.55859,4.99219,5.05078];
simg12=[3.343750,3.648440,3.355470,3.359380,3.355470];
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
