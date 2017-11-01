



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

base1      = [1.5748164999999998, 2.51887, 3.462924, 4.4069775, 5.351031, 6.2950845, 7.2391380000000005, 8.1831915, 9.1272455, 10.071299, 11.015352499999999];
bao1       = [0.9153805000000004, 4.7119615, 5.722411, 6.7328605, 7.74331, 8.753759, 9.764208499999999, 10.774657999999999, 11.701196, 12.701404499999999, 13.7016125];
sbao1      = [4.2665825, 4.83676, 5.406938, 5.9771155, 6.5472935, 7.117471500000001, 7.687649, 8.257826999999999, 9.387867499999999, 10.855677, 14.2466295];
base2      = [0.99, 1.08, 1.08, 1.055, 0.95, 1.04, 1.045, 1.03, 1.05, 1.025, 1.025];
bao2       = [10.43, 8.015, 8.43, 7.32, 7.885, 8.15, 8.01, 8.01, 8.24, 7.985, 7.86];
sbao2      = [3.26, 3.345, 3.255, 3.395, 3.38, 3.33, 3.2, 3.35, 3.195, 3.3, 3.065];
base3      = [8.0076065, 7.6635875, 7.3214615, 6.979336, 6.63721, 6.2950845, 5.952959, 5.6108329999999995, 5.2687075, 4.9265815, 4.584456];
bao3       = [9.350806500000001, 9.220759000000001, 9.1433055, 9.013456999999999, 8.883608, 8.753759, 8.623910500000001, 8.4940615, 8.364213, 8.234364, 8.104515];
sbao3      = [9.6461765, 7.879834499999999, 7.3354165, 7.2627679999999994, 7.1901195, 7.117471500000001, 7.044823, 6.9721744999999995, 6.899526, 6.8268775, 6.7542290000000005];
base4      = [0.955, 1.05, 1.04, 1.045, 1.04, 1.04, 1.035, 1.04, 1.02, 0.93, 1.05];
bao4       = [7.33, 8.075, 7.825, 7.425, 8.165, 8.15, 7.885, 8.24, 7.915, 7.975, 8.0];
sbao4      = [3.05, 3.34, 3.24, 3.345, 3.325, 3.33, 3.19, 3.34, 3.3, 3.49, 3.305];
base5      = [5.0896305, 5.9100505, 6.2950845, 6.6623235, 6.7461965];
bao5       = [5.7647425, 7.05613, 8.753759, 10.608236, 11.5528885];
sbao5      = [5.6856985, 6.4927575, 7.117471500000001, 7.8128405, 8.2802355];
base6      = [1.06, 1.035, 1.04, 1.06, 1.01];
bao6       = [7.63, 8.95, 8.15, 7.88, 8.44];
sbao6      = [3.315, 3.325, 3.33, 3.33, 3.3];
base7      = [4.798292, 5.330373, 6.2950845, 6.433903, 7.1950185];
bao7       = [7.6046595, 8.1986655, 8.753759, 9.0830065, 9.644574];
sbao7      = [6.6176355000000004, 6.779834, 7.117471500000001, 7.624796, 8.094165];
base8      = [1.04, 1.045, 1.04, 1.055, 1.04];
bao8       = [5.965, 6.825, 8.15, 9.3, 11.07];
sbao8      = [3.14, 3.275, 3.33, 3.445, 3.675];
base9      = [7.4108015, 7.104188000000001, 6.2950845, 5.330612, 4.895162];
bao9       = [8.452517499999999, 8.7550085, 8.753759, 8.55799, 8.55799];
sbao9      = [8.0108965, 7.466022000000001, 7.117471500000001, 6.779835, 6.6176379999999995];
base10     = [0.96, 1.06, 1.04, 1.045, 1.06];
bao10      = [7.57, 7.905, 8.15, 7.6, 7.935];
sbao10     = [3.19, 3.245, 3.33, 3.485, 3.625];
base11     = [6.2950845, 5.8041305, 5.3303815, 5.063633, 5.0635915];
bao11      = [8.753759, 7.851604, 7.817633, 7.5453475, 7.0236145];
sbao11     = [7.117471500000001, 6.868996, 6.7798345, 6.871473, 6.6176375];
base12     = [0.95, 1.035, 1.04, 1.035, 1.04]


%1---------------------------------------------------------
% varying of distribution of threshold(normal)
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0];
mpdc5 = distinguishable_colors(5);
plot(x1, base1, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, bao1, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, sbao1, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% 1:blue, 2:red, 3:green
%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%
set(gca, 'XLim', [min(x1), max(x1)]);
xlabel('\lambda', 'FontSize', 14);
ylabel('Social', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = x1;
mpdc5 = distinguishable_colors(5);
plot(x2, base2, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, bao2, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, sbao2, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [min(x2), max(x2)]);
xlabel('\lambda', 'FontSize', 14);
ylabel('Time', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0];
mpdc5 = distinguishable_colors(5);

plot(x3, base3, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, bao3, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, sbao3, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x3 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x3), max(x3)]);
set(gca, 'FontSize', fontsize, 'Xtick', x3);
%

xlabel('\alpha', 'FontSize', 14);
ylabel('Social', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = x3;
mpdc5 = distinguishable_colors(5);

plot(x4, base4, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, bao4, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, sbao4, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x4);
set(gca, 'XLim', [min(x4), max(x4)]);
xlabel('\alpha', 'FontSize', 14);
ylabel('Time', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = [500, 1000, 1500, 2000, 2500];
mpdc5 = distinguishable_colors(5);

plot(x5, base5, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, bao5, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, sbao5, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
%
set(gca, 'XLim', [min(x5), max(x5)]);
xlabel('r_{max}', 'FontSize', 14);
ylabel('Social', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x6 = x5;
mpdc5 = distinguishable_colors(5);

plot(x6, base6, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, bao6, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, sbao6, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
set(gca, 'XLim', [min(x6), max(x6)]);
xlabel('r_{max}', 'FontSize', 14);
ylabel('Time', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [3000, 3500, 4000, 4500, 5000];
mpdc5 = distinguishable_colors(5);

plot(x7, base7, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, bao7, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, sbao7, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x7), max(x7)]);
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%

xlabel('Budget(\times 10^4)', 'FontSize', 14);
ylabel('Social', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = x7;
mpdc5 = distinguishable_colors(5);

plot(x8, base8, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, bao8, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, sbao8, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [min(x8), max(x8)]);
xlabel('Budget(\times 10^4)', 'FontSize', 14);
ylabel('Time', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = [2, 4, 6, 8, 10];
mpdc5 = distinguishable_colors(5);

plot(x9, base9, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, bao9, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, sbao9, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
%
set(gca, 'XLim', [min(x9), max(x9)]);
xlabel('K', 'FontSize', 14);
ylabel('Social', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = x9;
mpdc5 = distinguishable_colors(5);

plot(x10, base10, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, bao10, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, sbao10, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
set(gca, 'XLim', [min(x10), max(x10)]);
xlabel('K', 'FontSize', 14);
ylabel('Time', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = [120, 130, 140, 150, 160];
mpdc5 = distinguishable_colors(5);

plot(x11, base11, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, bao11, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, sbao11, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x11), max(x11)]);
set(gca, 'FontSize', fontsize, 'Xtick', x11);
%

xlabel('\mu of estate\_price(\times 10^4)', 'FontSize', 14);
ylabel('Social', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = x11;
mpdc5 = distinguishable_colors(5);

plot(x12, base12, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, bao12, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, sbao12, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x12 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x12);
set(gca, 'XLim', [min(x12), max(x12)]);
xlabel('\mu of estate\_price(\times 10^4)', 'FontSize', 14);
ylabel('Time', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
