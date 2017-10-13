



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

ShortestJobFirst1 = [3486756.807, 2068951.070, 1605500.225, 1407171.551, 1070856.857];
FirstInFirstServe1 = [3496044.768, 2058576.166, 1595630.811, 1382438.306, 1092324.409];
GreedyInsert1  = [2096177.745, 938234.741, 597514.899, 409159.492, 306966.350];
ShortestJobFirst2 = [0.275, 0.267, 0.246, 0.244, 0.223];
FirstInFirstServe2 = [0.215, 0.219, 0.214, 0.263, 0.268];
GreedyInsert2  = [176.615, 33.942, 13.174, 6.007, 3.000];
ShortestJobFirst3 = [1384828.846, 1455240.404, 1605500.225, 2181928.697, 3675379.755];
FirstInFirstServe3 = [1328677.092, 1431505.786, 1595630.811, 2139591.492, 3646936.001];
GreedyInsert3  = [676232.567, 646532.990, 597514.899, 572638.098, 572393.765];
ShortestJobFirst4 = [0.001, 0.216, 0.246, 0.255, 0.385];
FirstInFirstServe4 = [0.001, 0.213, 0.214, 0.254, 0.394];
GreedyInsert4  = [13.045, 12.839, 13.174, 13.330, 10.587];
ShortestJobFirst5 = [83376.413, 594526.826, 1605500.225, 5387042.994, 10892536.037];
FirstInFirstServe5 = [80746.103, 593482.526, 1595630.811, 5475219.376, 11050136.818];
GreedyInsert5  = [19040.247, 130272.087, 597514.899, 2597154.791, 6174552.725];
ShortestJobFirst6 = [0.049, 0.156, 0.246, 0.439, 0.678];
FirstInFirstServe6 = [0.044, 0.126, 0.214, 0.482, 0.738];
GreedyInsert6  = [0.010, 0.643, 13.174, 225.780, 776.470];
ShortestJobFirst7 = [1572412.105, 1568221.694, 1605500.225, 1179693.065, 1082879.291];
FirstInFirstServe7 = [1552425.756, 1537863.923, 1595630.811, 1159037.497, 1068056.252];
GreedyInsert7  = [695932.853, 677332.038, 597514.899, 633994.789, 614916.521];
ShortestJobFirst8 = [0.282, 0.271, 0.246, 0.226, 0.212];
FirstInFirstServe8 = [0.286, 0.285, 0.214, 0.233, 0.195];
GreedyInsert8  = [27.724, 29.500, 13.174, 13.716, 14.416];









%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [10, 20, 30, 40, 50];
% GreedyInsert1      = [4800.000, 3400.000, 3136.000, 2097.135, 1857.673, 1688.443, 864.679, 386.815];
% FirstInFirstServe1           = [4800.000, 3224.000, 2838.491, 1893.000, 1588.122, 948.299, 538.619, 323.189];
% ShortestJobFirst1        = [4800.000, 3312.000, 3086.057, 2147.250, 1773.642, 1150.514, 612.204, 378.257];
mpdc5 = distinguishable_colors(5);
plot(x1, ShortestJobFirst1, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, FirstInFirstServe1, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, GreedyInsert1, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% 1:blue, 2:red, 3:green
%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%
set(gca, 'XLim', [10, 50]);
xlabel('varying of |worker|', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');
x2 = x1;
box on;
% GreedyInsert2      = [6.664, 24.289, 107.274, 280.507, 530.077, 713.011, 1294.510, 1585.741];
% FirstInFirstServe2           = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001];
% ShortestJobFirst2        = [3.631, 5.001, 4.539, 3.501, 1.339, 0.998, 0.715, 0.592];
mpdc5 = distinguishable_colors(5);

plot(x2, ShortestJobFirst2, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, FirstInFirstServe2, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, GreedyInsert2, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [10, 50]);
xlabel('varying of |worker|', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [2, 4, 8, 16, 32];
% FirstInFirstServe3		   = [4199.760, 3997.742, 3133.101, 2096.768, 1812.836, 1158.419, 727.614, 444.724];
% GreedyInsert3      = [3788.180, 0.000, 2729.083, 2025.560, 0.000, 3329.079, 2827.183, 1712.853];
% ShortestJobFirst3        = [3788.180, 3288.565, 2542.481, 2349.493, 1748.458, 1145.060, 717.353, 424.645];
mpdc5 = distinguishable_colors(5);

plot(x4, ShortestJobFirst3, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, FirstInFirstServe3, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, GreedyInsert3, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [2, 32]);
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('Varying of Capacity', 'FontSize', 14);
ylabel('Sum Flow Time)', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = x4;
% FirstInFirstServe4 		   = [0.003, 0.003, 0.003, 0.003, 0.003, 0.004, 0.004, 0.006];
% GreedyInsert4      = [6.594, 0.000, 126.724, 337.602, 0.000, 863.752, 1334.177, 1952.697];
% ShortestJobFirst4        = [5.011, 7.569, 4.154, 4.275, 2.077, 1.500, 1.150, 0.953];
mpdc5 = distinguishable_colors(5);

plot(x5, ShortestJobFirst4, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, FirstInFirstServe4, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, GreedyInsert4, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
set(gca, 'XLim', [2, 32]);
xlabel('Varying of Capacity', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [200, 500, 1000, 2000, 3000];
% FirstInFirstServe5  = [2334.669, 2429.964, 2222.874, 1980.311, 1876.779];
% GreedyInsert5      = [0.000, 0.000, 0.000, 0.000, 0.000];
% ShortestJobFirst5        = [2286.013, 2180.986, 1925.845, 1722.066, 1760.682];
mpdc5 = distinguishable_colors(5);

plot(x7, ShortestJobFirst5, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, FirstInFirstServe5, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, GreedyInsert5, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%
set(gca, 'XLim', [200, 3000]);
xlabel('varying of |order|', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = x7;
% FirstInFirstServe6  = [0.006, 0.006, 0.006, 0.006, 0.006];
% GreedyInsert6      = [0.000, 0.000, 0.000, 0.000, 0.000];
% ShortestJobFirst6        = [3.658, 2.906, 2.511, 2.278, 2.233];
mpdc5 = distinguishable_colors(5);

plot(x8, ShortestJobFirst6, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, FirstInFirstServe6, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, GreedyInsert6, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [200, 3000]);
xlabel('varying of |orderN|', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [30, 60, 120, 180, 240];
% FirstInFirstServe7  = [2119.155, 2163.696, 2065.467, 2123.636, 2186.895];
% GreedyInsert7      = [0.000, 0.000, 0.000, 3599.144, 0.000];
% ShortestJobFirst7        = [1888.781, 2152.589, 2001.273, 2117.965, 1997.593];
mpdc5 = distinguishable_colors(5);

plot(x10, ShortestJobFirst7, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, FirstInFirstServe7, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, GreedyInsert7, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [30, 240]);
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('varying of Time Range', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = x10;
% FirstInFirstServe8  = [0.034, 0.029, 0.033, 0.029, 0.032];
% GreedyInsert8      = [0.000, 0.000, 0.000, 488.534, 0.000];
% ShortestJobFirst8        = [2.329, 2.470, 2.295, 2.649, 2.352];
mpdc5 = distinguishable_colors(5);

plot(x11, ShortestJobFirst8, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, FirstInFirstServe8, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, GreedyInsert8, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
set(gca, 'XLim', [30, 240]);
xlabel('varying of Time Range', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('ShortestJobFirst',  'FirstInFirstServe', 'GreedyInsert', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

