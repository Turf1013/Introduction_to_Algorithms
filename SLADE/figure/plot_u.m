



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;


OPQ_Extended1  = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
Baseline1      = [4800.000, 3400.000, 3136.000, 2097.135, 1857.673, 1688.443, 864.679, 386.815];
OPQ1           = [4800.000, 3224.000, 2838.491, 1893.000, 1588.122, 948.299, 538.619, 323.189];
Greedy1        = [4800.000, 3312.000, 3086.057, 2147.250, 1773.642, 1150.514, 612.204, 378.257];
OPQ_Extended2  = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
Baseline2      = [5.708, 15.530, 165.176, 404.071, 499.149, 1068.298, 1950.496, 2553.047];
OPQ2           = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001];
Greedy2        = [3.631, 5.001, 4.539, 3.501, 1.339, 0.998, 0.715, 0.592];
OPQ_Extended3  = [4199.760, 3997.742, 3133.101, 2096.768, 1812.836, 1158.419, 727.614, 444.724];
Baseline3      = [3788.180, 3499.462, 2729.083, 2025.560, 5357.348, 3329.079, 2827.183, 1712.853];
OPQ3           = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
Greedy3        = [3788.180, 3288.565, 2542.481, 2349.493, 1748.458, 1145.060, 717.353, 424.645];
OPQ_Extended4  = [0.003, 0.003, 0.003, 0.003, 0.003, 0.004, 0.004, 0.006];
Baseline4      = [18.749, 26.486, 597.767, 933.001, 587.274, 3641.738, 4374.023, 5981.711];
OPQ4           = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
Greedy4        = [5.011, 7.569, 4.154, 4.275, 2.077, 1.500, 1.150, 0.953];
OPQ_Extended5  = [1876.779, 1980.311, 2222.874, 2429.964, 2334.669];
Baseline5      = [6227.641, 6714.814, 5339.876, 4882.976, 3548.407];
OPQ5           = [0.000, 0.000, 0.000, 0.000, 0.000];
Greedy5        = [1760.682, 1722.066, 1925.845, 2180.986, 2286.013];
OPQ_Extended6  = [0.006, 0.006, 0.006, 0.006, 0.006];
Baseline6      = [597.047, 581.690, 590.062, 597.761, 573.161];
OPQ6           = [0.000, 0.000, 0.000, 0.000, 0.000];
Greedy6        = [2.233, 2.278, 2.511, 2.906, 3.658];
OPQ_Extended7  = [2186.895, 2123.636, 2065.467, 2163.696, 2119.155];
Baseline7      = [3817.180, 3599.144, 3407.100, 3588.489, 3406.834];
OPQ7           = [0.000, 0.000, 0.000, 0.000, 0.000];
Greedy7        = [1997.593, 2117.965, 2001.273, 2152.589, 1888.781];
OPQ_Extended8  = [0.032, 0.029, 0.033, 0.029, 0.034];
Baseline8      = [542.693, 2273.934, 543.521, 537.398, 524.312];
OPQ8           = [0.000, 0.000, 0.000, 0.000, 0.000];
Greedy8        = [2.352, 2.649, 2.295, 2.470, 2.329];



%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [1,2,5,10,20,30,40,50];
% Baseline1      = [4800.000, 3400.000, 3136.000, 2097.135, 1857.673, 1688.443, 864.679, 386.815];
% OPQ1           = [4800.000, 3224.000, 2838.491, 1893.000, 1588.122, 948.299, 538.619, 323.189];
% Greedy1        = [4800.000, 3312.000, 3086.057, 2147.250, 1773.642, 1150.514, 612.204, 378.257];
mpdc5 = distinguishable_colors(5);
plot(x1, Greedy1, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, OPQ1, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, Baseline1, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% 1:blue, 2:red, 3:green
%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%
set(gca, 'XLim', [1, 50]);
xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [1,2,5,10,20,30,40,50];
% Baseline2      = [6.664, 24.289, 107.274, 280.507, 530.077, 713.011, 1294.510, 1585.741];
% OPQ2           = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001];
% Greedy2        = [3.631, 5.001, 4.539, 3.501, 1.339, 0.998, 0.715, 0.592];
mpdc5 = distinguishable_colors(5);

plot(x2, Greedy2, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, OPQ2, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, Baseline2, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [1, 50]);
xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [1,2,5,10,20,30,40,50];
% OPQ3		   = [4199.760, 3997.742, 3133.101, 2096.768, 1812.836, 1158.419, 727.614, 444.724];
% Baseline3      = [3788.180, 0.000, 2729.083, 2025.560, 0.000, 3329.079, 2827.183, 1712.853];
% Greedy3        = [3788.180, 3288.565, 2542.481, 2349.493, 1748.458, 1145.060, 717.353, 424.645];
mpdc5 = distinguishable_colors(5);

plot(x4, Greedy3, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, OPQ_Extended3, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, Baseline3, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [1, 50]);
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = [1,2,5,10,20,30,40,50];
% OPQ4 		   = [0.003, 0.003, 0.003, 0.003, 0.003, 0.004, 0.004, 0.006];
% Baseline4      = [6.594, 0.000, 126.724, 337.602, 0.000, 863.752, 1334.177, 1952.697];
% Greedy4        = [5.011, 7.569, 4.154, 4.275, 2.077, 1.500, 1.150, 0.953];
mpdc5 = distinguishable_colors(5);

plot(x5, Greedy4, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, OPQ_Extended4, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, Baseline4, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
set(gca, 'XLim', [1, 50]);
xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [0.87, 0.9, 0.92, 0.95, 0.97];
% OPQ_Extended5  = [2334.669, 2429.964, 2222.874, 1980.311, 1876.779];
% Baseline5      = [0.000, 0.000, 0.000, 0.000, 0.000];
% Greedy5        = [2286.013, 2180.986, 1925.845, 1722.066, 1760.682];
mpdc5 = distinguishable_colors(5);

plot(x7, Greedy5, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, OPQ_Extended5, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, Baseline5, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%
set(gca, 'XLim', [0.87, 0.97]);
xlabel('mean of elilability Threshold t_i', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ\_Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = [0.87, 0.9, 0.92, 0.95, 0.97];
% OPQ_Extended6  = [0.006, 0.006, 0.006, 0.006, 0.006];
% Baseline6      = [0.000, 0.000, 0.000, 0.000, 0.000];
% Greedy6        = [3.658, 2.906, 2.511, 2.278, 2.233];
mpdc5 = distinguishable_colors(5);

plot(x8, Greedy6, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, OPQ_Extended6, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, Baseline6, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [0.87, 0.97]);
xlabel('mean of elilability Threshold t_i', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ\_Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [0.87, 0.9, 0.92, 0.95, 0.97];
% OPQ_Extended7  = [2119.155, 2163.696, 2065.467, 2123.636, 2186.895];
% Baseline7      = [0.000, 0.000, 0.000, 3599.144, 0.000];
% Greedy7        = [1888.781, 2152.589, 2001.273, 2117.965, 1997.593];
mpdc5 = distinguishable_colors(5);

plot(x10, Greedy7, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, OPQ_Extended7, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, Baseline7, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [0.87, 0.97]);
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('\mu of elilability Threshold t_i', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ\_Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = [0.87, 0.9, 0.92, 0.95, 0.97];
% OPQ_Extended8  = [0.034, 0.029, 0.033, 0.029, 0.032];
% Baseline8      = [0.000, 0.000, 0.000, 488.534, 0.000];
% Greedy8        = [2.329, 2.470, 2.295, 2.649, 2.352];
mpdc5 = distinguishable_colors(5);

plot(x11, Greedy8, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, OPQ_Extended8, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, Baseline8, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
set(gca, 'XLim', [0.87, 0.97]);
xlabel('\mu of elilability Threshold t_i', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ\_Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
