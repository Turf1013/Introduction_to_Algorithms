



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

ibase1     = [1.9670264999999998, 2.9245685, 3.8821105, 4.8396525, 5.7971945, 6.7547365, 7.7122785, 8.6698205, 9.6273625, 10.5849045, 11.5424465];
ibao1      = [2.039072, 4.813835, 5.849711, 6.885587, 7.921463, 8.957339000000001, 9.9932145, 11.029090499999999, 12.0649665, 13.4534415, 14.5284935];
isbao1     = [4.25609, 4.876805, 5.49752, 6.1182345, 6.7389495, 7.3596645, 7.9803795, 8.6010945, 9.743573999999999, 11.619371000000001, 14.959309];
ibase2     = [1.08, 1.085, 1.09, 1.025, 1.02, 1.0, 1.03, 1.0, 1.0, 0.985, 0.98];
ibao2      = [10.155, 7.44, 8.24, 7.875, 7.52, 7.245, 7.13, 7.17, 7.165, 7.35, 7.345];
isbao2     = [3.4, 3.4, 3.465, 3.415, 3.345, 3.33, 3.385, 3.345, 3.345, 3.3, 3.07];
ibase3     = [8.2711535, 7.9663645, 7.6634575, 7.3605505, 7.0576435, 6.7547365, 6.451829, 6.148922, 5.8460149999999995, 5.543108, 5.240201];
ibao3      = [9.764246499999999, 9.446155000000001, 9.323951000000001, 9.201747000000001, 9.079543000000001, 8.957339000000001, 8.8351345, 8.7129305, 8.5907265, 8.4685225, 8.3463185];
isbao3     = [9.979654499999999, 8.3395795, 7.580738, 7.507047, 7.433356, 7.3596645, 7.2859735, 7.212282, 7.138591, 7.0648995, 6.9912085];
ibase4     = [1.005, 1.02, 1.015, 0.99, 1.005, 1.0, 1.005, 1.0, 1.015, 1.005, 1.01];
ibao4      = [7.81, 7.505, 7.08, 7.72, 7.38, 7.245, 7.07, 7.275, 7.05, 7.28, 7.58];
isbao4     = [3.085, 3.33, 3.35, 3.35, 3.405, 3.33, 3.325, 3.345, 3.39, 3.34, 3.335];
ibase5     = [5.445871, 6.2741355, 6.7547365, 7.1766915000000004, 7.3057455000000004];
ibao5      = [5.9305155, 7.1015175, 8.957339000000001, 11.0289445, 12.303153];
isbao5     = [5.7102265, 6.4489145, 7.3596645, 8.1239585, 8.7022185];
ibase6     = [1.01, 0.985, 1.0, 1.095, 1.035];
ibao6      = [7.005, 7.97, 7.245, 7.215, 7.445];
isbao6     = [3.35, 3.34, 3.33, 3.305, 3.29];
ibase7     = [5.776802, 6.2794785, 6.7547365, 7.3841920000000005, 8.124114];
ibao7      = [7.8113425, 8.3469105, 8.957339000000001, 9.5473505, 10.054237];
isbao7     = [6.930243, 7.0924135, 7.3596645, 7.7300775, 8.693258];
ibase8     = [0.97, 1.0, 1.0, 1.02, 1.03];
ibao8      = [5.175, 5.855, 7.245, 8.59, 10.565];
isbao8     = [3.1, 3.245, 3.33, 3.535, 3.765];
ibase9     = [8.542556, 7.3837795, 6.7547365, 6.2812285, 5.8735735];
ibao9      = [8.9416595, 8.957339000000001, 8.957339000000001, 8.957339000000001, 8.9733845];
isbao9     = [8.579200499999999, 7.7300765, 7.3596645, 7.0924415, 6.9302445];
ibase10    = [1.045, 1.02, 1.0, 1.025, 0.995];
ibao10     = [7.105, 7.11, 7.245, 7.12, 7.6];
isbao10    = [3.135, 3.22, 3.33, 3.525, 3.685];
ibase11    = [6.7547365, 6.9678575, 5.3303815, 5.33034, 5.063385];
ibao11     = [8.957339000000001, 8.5429805, 7.9751294999999995, 7.509672999999999, 7.31146];
isbao11    = [7.3596645, 7.4561355, 6.7798345, 6.7798335000000005, 6.617637];
ibase12    = [1.0, 1.0, 0.965, 0.97, 0.97];
ibao12     = [7.26, 6.46, 5.51, 5.275, 5.24];
isbao12    = [3.31, 3.245, 3.155, 3.185, 3.09];



%1---------------------------------------------------------
% varying of distribution of threshold(normal)
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0];
mpdc5 = distinguishable_colors(5);
plot(x1, ibase1, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, ibao1, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, isbao1, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
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
plot(x2, ibase2, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, ibao2, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, isbao2, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [min(x2), max(x2)]);
xlabel('\lambda', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
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

plot(x3, ibase3, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, ibao3, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, isbao3, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
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

plot(x4, ibase4, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, ibao4, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, isbao4, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x4);
set(gca, 'XLim', [min(x4), max(x4)]);
xlabel('\alpha', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
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

plot(x5, ibase5, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, ibao5, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, isbao5, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
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

plot(x6, ibase6, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, ibao6, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, isbao6, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
set(gca, 'XLim', [min(x6), max(x6)]);
xlabel('r_{max}', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
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

plot(x7, ibase7, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, ibao7, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, isbao7, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x7), max(x7)]);
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%

xlabel('B(\times 10^4)', 'FontSize', 14);
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

plot(x8, ibase8, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, ibao8, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, isbao8, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [min(x8), max(x8)]);
xlabel('B(\times 10^4)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
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

plot(x9, ibase9, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, ibao9, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, isbao9, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
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

plot(x10, ibase10, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, ibao10, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, isbao10, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
set(gca, 'XLim', [min(x10), max(x10)]);
xlabel('K', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
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

plot(x11, ibase11, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, ibao11, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, isbao11, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

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

plot(x12, ibase12, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, ibao12, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, isbao12, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x12 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x12);
set(gca, 'XLim', [min(x12), max(x12)]);
xlabel('\mu of estate\_price(\times 10^4)', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('Baseline',  'B&O', 'RP', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
