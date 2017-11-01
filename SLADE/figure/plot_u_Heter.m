



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;


OPQ_Extended1  = [615.370, 626.155, 633.109, 642.340, 645.597];
Baseline1      = [1374.251, 1358.148, 1340.383, 1253.533, 1245.684];
Greedy1        = [722.736, 698.881, 684.045, 675.408, 695.105];
OPQ_Extended2  = [0.109, 0.109, 0.106, 0.108, 0.107];
Baseline2      = [6.508, 6.074, 6.107, 6.325, 5.800];
Greedy2        = [1.441, 1.800, 2.145, 2.681, 3.058];
OPQ_Extended3  = [631.848, 635.026, 635.117, 635.754, 637.269];
Baseline3      = [958.977, 964.359, 974.747, 985.303, 993.276];
Greedy3        = [661.607, 680.935, 687.551, 692.072, 696.202];
OPQ_Extended4  = [0.107, 0.107, 0.110, 0.108, 0.109];
Baseline4      = [6.608, 6.011, 5.985, 5.998, 6.168];
Greedy4        = [2.209, 2.375, 2.285, 2.331, 2.231];
OPQ_Extended5  = [294.6159332,382.5022428,405.3722927,459.5502181,498.190267];
Baseline5      = [1001.075082,1059.478529,1099.078083,1178.895879,1326.332139];
Greedy5        = [511.6740154,551.6026879,584.3613249,598.1613115,724.6549707];
OPQ_Extended6  = [0.509, 0.530, 0.535, 0.550, 0.561];
Baseline6      = [5.616, 5.986, 6.505, 7.075, 8.619];
Greedy6        = [2.184, 2.383, 3.136, 3.744, 3.736];
OPQ_Extended7  = [517.1537015,666.8472767,686.9451033,774.3173322,843.0408257];
Greedy7         = [900.2951341,958.2407887,985.8375854,993.5963395,1098.972247];
Baseline7        = [1209.747198,1274.021475,1299.913809,1413.103226,1566.12375];
OPQ_Extended8  = [0.510, 0.651, 0.810, 0.920, 1.200];
Baseline8      = [5.087, 5.756, 6.380, 6.764, 7.247];
Greedy8        = [1.883, 2.042, 2.328, 2.517, 2.963];






%1---------------------------------------------------------
% varying of distribution of threshold(normal)
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [0.87, 0.90, 0.92, 0.95, 0.97];
mpdc5 = distinguishable_colors(5);
plot(x1, Greedy1, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, OPQ_Extended1, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, Baseline1, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% 1:blue, 2:red, 3:green
%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%
set(gca, 'XLim', [min(x1), max(x1)]);
xlabel('\mu of reliability threshold(normal)', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = x1;
mpdc5 = distinguishable_colors(5);
plot(x2, Greedy2, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, OPQ_Extended2, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, Baseline2, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [min(x2), max(x2)]);
xlabel('\mu of reliability threshold(normal)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [0.01, 0.02, 0.03, 0.04, 0.05];
mpdc5 = distinguishable_colors(5);

plot(x4, Greedy3, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, OPQ_Extended3, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, Baseline3, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x4), max(x4)]);
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('\sigma of reliability threshold(normal)', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = x4;
mpdc5 = distinguishable_colors(5);

plot(x5, Greedy4, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, OPQ_Extended4, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, Baseline4, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
set(gca, 'XLim', [min(x5), max(x5)]);
xlabel('\sigma of reliability threshold(normal)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [0.87, 0.90, 0.92, 0.95, 0.97];
mpdc5 = distinguishable_colors(5);

plot(x7, Greedy5, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, OPQ_Extended5, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, Baseline5, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%
set(gca, 'XLim', [min(x7), max(x7)]);
xlabel('mean of reliability threshold(uniform)', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = x7;
mpdc5 = distinguishable_colors(5);

plot(x8, Greedy6, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, OPQ_Extended6, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, Baseline6, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [min(x8), max(x8)]);
xlabel('mean of reliability threshold(uniform)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [0.87, 0.90, 0.92, 0.95, 0.97];
mpdc5 = distinguishable_colors(5);

plot(x10, Greedy7, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, OPQ_Extended7, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, Baseline7, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x10), max(x10)]);
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('\lambda^{-1} of reliability threshold(exponential)', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = x10;
mpdc5 = distinguishable_colors(5);

plot(x11, Greedy8, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, OPQ_Extended8, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, Baseline8, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
set(gca, 'XLim', [min(x11), max(x11)]);
xlabel('\lambda^{-1} of reliability threshold(exponential)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

