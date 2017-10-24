



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;


OPQ_Extended1  = [1916.566, 1951.562, 1967.492, 1973.037, 1975.300];
Baseline1      = [2600.711, 2786.841, 2777.124, 2817.858, 2771.484];
Greedy1        = [2250.389, 2211.641, 2157.327, 2099.575, 2047.879];
OPQ_Extended2  = 5 * [0.010, 0.007, 0.009, 0.010, 0.010];
Baseline2      = 5 * [6.887, 7.201, 7.214, 7.238, 7.164];
Greedy2        = 5 * [1.755, 2.207, 2.642, 3.113, 3.283];
OPQ_Extended3  = [1976.967, 1988.202, 1990.431, 1997.560, 2007.642];
Baseline3      = [2540.023, 2742.303, 2701.460, 2659.503, 2589.051];
Greedy3        = [2149.842, 2146.973, 2155.284, 2168.017, 2184.522];
OPQ_Extended4  = 5 * [0.006, 0.008, 0.009, 0.010, 0.009];
Baseline4      = 5 * [7.375, 7.222, 7.204, 7.149, 7.055];
Greedy4        = 5 * [3.109, 3.337, 3.131, 3.185, 2.930];
OPQ_Extended5  = [1907.417, 1927.541, 1957.903, 1983.790, 1984.076];
Baseline5      = [2758.981, 2910.866, 2902.195, 3099.018, 3177.206];
Greedy5        = [2289.244, 2227.957, 2139.365, 2115.832, 2046.222];
OPQ_Extended6  = 5 * [0.010, 0.009, 0.010, 0.010, 0.010];
Baseline6      = 5 * [6.535, 6.780, 7.169, 7.193, 7.304];
Greedy6        = 5 * [2.550, 2.600, 2.972, 3.317, 4.063];
OPQ_Extended7  = [3143.654, 3179.544, 3194.404, 3227.606, 3271.232];
Baseline7      = [3346.695, 3343.218, 3378.734, 3413.442, 3491.985];
Greedy7        = [3981.436, 4008.763, 4019.356, 4048.000, 4073.279];
OPQ_Extended8  = 5 * [0.010, 0.010, 0.011, 0.011, 0.009];
Baseline8      = 5 * [6.878, 6.903, 6.930, 6.899, 6.952];
Greedy8        = 5 * [3.860, 3.745, 3.820, 3.763, 4.041];



%1---------------------------------------------------------
% varying of distribution of threshold(normal)
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [0.88, 0.90, 0.92, 0.94, 0.96];
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
xlabel('\mu of reliability threshold(Normal)', 'FontSize', 14);
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
xlabel('\mu of reliability threshold(Normal)', 'FontSize', 14);
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

xlabel('\sigma of reliability threshold(Normal)', 'FontSize', 14);
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
xlabel('\sigma of reliability threshold(Normal)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [0.88, 0.90, 0.92, 0.94, 0.96];
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
xlabel('mean of reliability threshold(Uniform)', 'FontSize', 14);
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
xlabel('mean of reliability threshold(Uniform)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [0.88, 0.90, 0.92, 0.94, 0.96];
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

xlabel('\lambda^{-1} of reliability threshold(Exponential)', 'FontSize', 14);
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
xlabel('\lambda^{-1} of reliability threshold(Exponential)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ-Extended', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

