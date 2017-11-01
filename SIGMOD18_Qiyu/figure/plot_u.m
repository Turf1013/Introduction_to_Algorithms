



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

base1      = [0.9280600000000003, 1.9032684999999998, 2.878477, 3.8536855, 4.8288935, 5.804102, 6.7793105, 7.754519, 8.7297275, 9.704935500000001, 10.680144];
bao1       = [1.5040865, 4.646162, 5.5967395, 6.547317, 7.497895, 8.4484725, 9.399049999999999, 10.3496275, 11.3002055, 12.603439999999999, 13.5931355];
sbao1      = [4.2553785, 4.8137145, 5.37205, 5.930386, 6.488722, 7.047058, 7.6053935, 8.1637295, 9.243829999999999, 11.057247499999999, 14.334807];
base2      = [83.635, 83.735, 83.625, 83.715, 83.555, 83.565, 83.55, 83.555, 83.225, 83.54, 83.555];
bao2       = [90.95, 90.68, 90.605, 90.605, 91.315, 90.84, 90.775, 90.22, 90.19, 89.89, 90.34];
sbao2      = [86.065, 85.99, 85.915, 86.04, 85.84, 85.91, 85.885, 85.91, 85.965, 85.845, 85.72];
base3      = [7.840002500000001, 7.431290499999999, 7.0244935, 6.6176965, 6.2108989999999995, 5.804102, 5.397305, 4.990508, 4.583711, 4.176914, 3.7701165000000003];
bao3       = [9.2965675, 8.9702385, 8.839797, 8.709355500000001, 8.578914000000001, 8.4484725, 8.318031, 8.1875895, 8.0571475, 7.926705999999999, 7.7962644999999995];
sbao3      = [9.667403499999999, 8.027257, 7.268345, 7.1945825, 7.12082, 7.047058, 6.9732955, 6.899533, 6.8257705, 6.7520085000000005, 6.678246];
base4      = [83.83, 83.585, 83.665, 83.58, 83.615, 83.565, 83.55, 83.585, 83.51, 83.535, 83.685];
bao4       = [91.045, 90.605, 90.135, 90.085, 90.985, 89.84, 89.68, 90.655, 90.82, 89.84, 89.7];
sbao4      = [85.585, 85.87, 86.03, 85.91, 85.89, 85.91, 85.925, 85.995, 85.97, 86.03, 85.91];
base5      = [4.6878375, 5.473734, 5.804102, 6.1236175, 6.198371];
bao5       = [5.7421595, 6.911341, 8.4484725, 10.547245499999999, 11.596356];
sbao5      = [5.599858, 6.3385455, 7.047058, 7.725642000000001, 8.169617];
base6      = [83.59, 83.775, 83.565, 83.58, 83.57];
bao6       = [89.765, 91.27, 89.84, 90.13, 89.925];
sbao6      = [85.965, 85.945, 85.91, 86.02, 86.0];
base7      = [4.798292, 5.327992, 5.804102, 6.433743, 7.3048665];
bao7       = [7.3017970000000005, 7.837793, 8.4484725, 9.038959, 9.545856];
sbao7      = [6.6176365, 6.7798065, 7.047058, 7.41747, 8.380651];
base8      = [83.59, 83.565, 83.565, 83.575, 83.625];
bao8       = [87.39, 88.955, 89.84, 91.325, 92.565];
sbao8      = [85.695, 85.88, 85.91, 86.22, 86.215];
base9      = [7.6087245, 6.433322, 5.804102, 5.3305885, 4.895161];
bao9       = [8.432943999999999, 8.4484725, 8.4484725, 8.4484725, 8.464545000000001];
sbao9      = [8.2667575, 7.4174690000000005, 7.047058, 6.7798345, 6.6176379999999995];
base10     = [83.785, 83.555, 83.565, 83.805, 83.585];
bao10      = [90.13, 89.72, 89.84, 90.705, 89.85];
sbao10     = [85.725, 85.835, 85.91, 86.145, 86.305];
base11     = [5.804102, 5.5755855, 5.3303815, 5.33034, 5.063385];
bao11      = [8.4484725, 8.016169999999999, 7.9751294999999995, 7.509672999999999, 7.31146];
sbao11     = [7.047058, 6.9586405, 6.7798345, 6.7798335000000005, 6.617637];
base12     = [83.55, 83.555, 83.525, 83.525, 83.44];
bao12      = [90.25, 89.3, 87.95, 87.535, 87.185];
sbao12     = [85.94, 86.33, 85.855, 85.825, 85.725];



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
