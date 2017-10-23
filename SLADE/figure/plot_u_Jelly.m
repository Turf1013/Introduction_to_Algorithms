



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;


Baseline1      = [2000.000, 3132.000, 3798.000, 3998.000, 3998.000];
OPQ1           = [1902.500, 2767.900, 3144.200, 3279.900, 3287.963];
Greedy1        = [1952.500, 2981.200, 3471.100, 3638.950, 3638.950];
Baseline2      = 5 * [6.916, 7.020, 7.193, 6.981, 7.008];
OPQ2           = [0.001, 0.001, 0.001, 0.001, 0.001];
Greedy2        = [4.241, 3.676, 3.383, 3.447, 3.471];
Baseline3      = [3198.000, 3198.000, 3178.000, 3178.000, 3158.000, 3148.000, 3132.000, 3118.000, 3108.000, 3089.386, 2823.086];
OPQ3           = [3185.500, 3136.500, 3082.522, 3034.000, 2980.300, 2867.546, 2767.900, 2685.780, 2594.220, 2507.290, 2419.550];
Greedy3        = [3190.001, 3165.500, 3138.511, 3114.250, 3087.400, 3031.023, 2981.200, 2940.140, 2894.360, 2796.587, 2673.035];
Baseline4      = 5 * [0.706, 1.279, 1.933, 2.649, 3.409, 5.151, 7.020, 9.478, 11.972, 15.082, 17.864];
OPQ4           = [0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001];
Greedy4        = [2.803, 5.711, 4.794, 4.389, 4.136, 3.805, 3.676, 3.761, 3.529, 3.381, 2.213];
Baseline5      = [3132.000, 6724.296, 10085.865, 16809.821, 25214.707, 33619.565];
OPQ5           = [2767.900, 5962.400, 8943.600, 14906.000, 22359.000, 29812.000];
Greedy5        = [2981.200, 6343.174, 9514.660, 15857.796, 23786.683, 31715.566];
Baseline6      = 5 * [7.020, 32.023, 73.820, 320.736, 1020.570, 1842.421];
OPQ6           = [0.001, 0.003, 0.005, 0.007, 0.012, 0.020];
Greedy6        = [3.676, 10.111, 22.148, 65.218, 153.305, 275.998];



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
