



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;


Baseline1      = 1.265 * [2504.945, 3104.945, 3704.945, 3904.945, 3904.945];
OPQ1           = 1.152 * [2475.234, 2880.400, 3246.400, 3376.450, 3376.450];
Greedy1        = 1.167 * [2608.521, 2992.533, 3475.526, 3631.510, 3631.510];
Baseline2      = 5 * [7.817, 8.061, 7.879, 7.615, 7.511];
OPQ2           = [0.001, 0.001, 0.001, 0.001, 0.001];
Greedy2        = [3.595, 2.359, 2.566, 2.660, 2.443];
Baseline3      = 1.265 * [3396.000, 3396.000, 3396.000, 3368.000, 3362.400, 3363.325, 3104.945, 3019.447, 2975.777, 2794.987, 2819.865];
OPQ3           = 1.152 * [3374.000, 3299.500, 3251.353, 3192.750, 3126.800, 2979.214, 2880.400, 2754.720, 2643.684, 2540.309, 2457.150];
Greedy3        = 1.167 * [3385.000, 3347.750, 3323.676, 3280.375, 3244.600, 3091.902, 2992.533, 2886.882, 2892.433, 2743.086, 2736.365];
Baseline4      = 5 * [0.722, 1.331, 2.008, 2.722, 3.454, 5.532, 8.061, 9.748, 12.974, 15.100, 18.984];
OPQ4           = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.001, 0.001, 0.001];
Greedy4        = [2.766, 5.610, 4.934, 3.818, 3.238, 2.511, 2.359, 1.957, 1.754, 1.513, 1.289];
Baseline5      = 1.265 * [3104.945, 6036.144, 9054.489, 15090.021, 22634.763, 30179.439];
OPQ5           = 1.152 * [2880.400, 5719.400, 8579.100, 14298.500, 21447.750, 28597.000];
Greedy5        = 1.167 * [2992.533, 5877.696, 8816.444, 14694.066, 22041.070, 29388.117];
Baseline6      = 5 * [8.061, 31.077, 74.372, 308.880, 926.016, 1933.565];
OPQ6           = [0.001, 0.003, 0.005, 0.008, 0.011, 0.022];
Greedy6        = [2.359, 8.693, 19.303, 55.941, 134.027, 237.947];




%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [0.88, 0.90, 0.92, 0.94, 0.96];
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
set(gca, 'XLim', [min(x1), max(x1)]);
xlabel('reliability threshold', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location','SouthEast');
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
plot(x2, OPQ2, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, Baseline2, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 );
% set(gca, 'YScale', 'log');
rotateXLabels( gca(), 60 );
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [min(x2), max(x2)]);
xlabel('reliability threshold', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [2,4,6,8,10,15,20,25,30,35,40];
mpdc5 = distinguishable_colors(5);
x4_ = 1 : size(x4, 2);
plot(x4_, Greedy3, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4_, OPQ3, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4_, Baseline3, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x4_), max(x4_)]);
set(gca, 'FontSize', fontsize, 'Xtick', x4_);
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
x5 = x4_;
mpdc5 = distinguishable_colors(5);

plot(x5, Greedy4, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, OPQ4, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, Baseline4, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x4 );
% set(gca, 'YScale', 'log');
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
set(gca, 'XLim', [min(x5), max(x5)]);
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
x7 = [10, 20, 30, 50, 75, 100];
x7_ = x7;%1:size(x7, 2);

mpdc5 = distinguishable_colors(5);

plot(x7_, Greedy5, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7_, OPQ5, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7_, Baseline5, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 );
% set(gca, 'YScale', 'log');
rotateXLabels( gca(), 60 );
set(gca, 'FontSize', fontsize, 'Xtick', x7_);
%
set(gca, 'XLim', [min(x7_), max(x7_)]);
% set(gca, 'ylim', [2500, 33619]);
xlabel('number of atomic tasks(Scalability \times 10^3)', 'FontSize', 14);
ylabel('Cost(USD)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = x7_;
mpdc5 = distinguishable_colors(5);

plot(x8, Greedy6, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, OPQ6, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, Baseline6, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x7 )
set(gca, 'YScale', 'log')
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [min(x8), max(x8)]);
xlabel('number of atomic tasks(Scalability \times 10^3)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Greedy',  'OPQ', 'Baseline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
