



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

staticSJF3     = [2091905.222, 1058099.055, 546119.353, 290962.239, 167556.692];
staticFIFO3    = [2077057.488, 1053099.233, 542447.175, 289938.660, 167561.612];
newSJF3        = [426206.604, 353259.721, 423983.124, 528618.683, 555654.974];
Hybrid3        = [460463.565, 373828.591, 483339.950, 595062.973, 639553.479];
newFIFO3       = [473003.756, 386554.615, 493089.184, 639582.380, 667669.398];
GreedyInsert3  = [957823.418, 943762.531, 947168.197, 919773.561, 912389.879];
staticSJF4     = [0.001, 0.001, 0.001, 0.001, 0.001];
staticFIFO4    = [0.001, 0.001, 0.001, 0.001, 0.001];
newSJF4        = [1.038, 0.749, 1.364, 1.736, 1.851];
Hybrid4        = [1.020, 0.622, 1.332, 1.772, 1.867];
newFIFO4       = [1.109, 0.742, 1.322, 1.761, 1.847];
GreedyInsert4  = [25.299, 22.681, 23.853, 25.293, 36.941];
staticSJF5     = [41417.480, 143632.979, 546119.353, 1194322.617, 3219113.579];
staticFIFO5    = [40862.081, 144634.769, 542447.175, 1185799.359, 3190457.846];
newSJF5        = [27404.065, 108850.306, 423983.124, 945829.438, 2514479.140];
Hybrid5        = [30803.671, 121716.556, 483339.950, 1074104.900, 2995310.372];
newFIFO5       = [30786.819, 124670.377, 493089.184, 1100498.593, 3056143.415];
GreedyInsert5  = [60213.779, 235120.663, 947168.197, 2084066.115, 5988025.298];
staticSJF6     = [0.001, 0.001, 0.001, 0.002, 0.005];
staticFIFO6    = [0.001, 0.001, 0.001, 0.002, 0.004];
newSJF6        = [0.312, 0.647, 1.364, 1.978, 3.322];
Hybrid6        = [0.331, 0.715, 1.332, 1.923, 3.203];
newFIFO6       = [0.320, 0.657, 1.322, 1.952, 3.338];
GreedyInsert6  = [0.112, 1.425, 23.853, 131.315, 1140.707];
staticSJF7     = [534221.570, 530287.030, 546119.353, 521381.374, 518035.786];
staticFIFO7    = [529386.349, 526784.135, 542447.175, 517755.082, 514547.605];
newSJF7        = [429625.193, 410530.707, 423983.124, 403061.524, 403952.959];
Hybrid7        = [482388.369, 482313.198, 483339.950, 460545.290, 465070.986];
newFIFO7       = [484267.991, 481401.891, 493089.184, 470528.888, 456807.104];
GreedyInsert7  = [956309.968, 932936.745, 947168.197, 965952.261, 959475.076];
staticSJF8     = [0.001, 0.001, 0.001, 0.001, 0.001];
staticFIFO8    = [0.001, 0.001, 0.001, 0.001, 0.001];
newSJF8        = [1.319, 1.338, 1.364, 1.317, 1.337];
Hybrid8        = [1.396, 1.357, 1.332, 1.301, 1.364];
newFIFO8       = [1.318, 1.302, 1.322, 1.303, 1.287];
GreedyInsert8  = [26.410, 23.528, 23.853, 23.643, 23.529];



%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [2, 4, 8, 16, 32];
% staticSJF3		   = [4199.760, 3997.742, 3133.101, 2096.768, 1812.836, 1158.419, 727.614, 444.724];
% GreedyInsert3      = [3788.180, 0.000, 2729.083, 2025.560, 0.000, 3329.079, 2827.183, 1712.853];
% staticFIFO3        = [3788.180, 3288.565, 2542.481, 2349.493, 1748.458, 1145.060, 717.353, 424.645];
mpdc5 = distinguishable_colors(8);

plot(x4, staticFIFO3, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, staticSJF3, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, GreedyInsert3, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, newSJF3, '^--', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, newFIFO3, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, Hybrid3, 'd-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [2, 32]);
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('Varying of Capacity', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('staticFIFO',  'staticSJF', 'GreedyInsert', 'newSJF', 'newFIFO', 'Hybrid', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = x4;
% staticSJF4 		   = [0.003, 0.003, 0.003, 0.003, 0.003, 0.004, 0.004, 0.006];
% GreedyInsert4      = [6.594, 0.000, 126.724, 337.602, 0.000, 863.752, 1334.177, 1952.697];
% staticFIFO4        = [5.011, 7.569, 4.154, 4.275, 2.077, 1.500, 1.150, 0.953];
mpdc5 = distinguishable_colors(8);

plot(x5, staticFIFO4, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, staticSJF4, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, GreedyInsert4, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, newSJF4, '^--', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, newFIFO4, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, Hybrid4, 'd-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
set(gca, 'XLim', [2, 32]);
xlabel('Varying of Capacity', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('staticFIFO',  'staticSJF', 'GreedyInsert', 'newSJF', 'newFIFO', 'Hybrid', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [50, 100, 200, 300, 500];
% staticSJF5  = [2334.669, 2429.964, 2222.874, 1980.311, 1876.779];
% GreedyInsert5      = [0.000, 0.000, 0.000, 0.000, 0.000];
% staticFIFO5        = [2286.013, 2180.986, 1925.845, 1722.066, 1760.682];
mpdc5 = distinguishable_colors(8);

plot(x7, staticFIFO5, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, staticSJF5, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, GreedyInsert5, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, newSJF5, '^--', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, newFIFO5, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, Hybrid5, 'd-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%
set(gca, 'XLim', [50, 500]);
xlabel('varying of |order|', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('staticFIFO',  'staticSJF', 'GreedyInsert', 'newSJF', 'newFIFO', 'Hybrid', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = x7;
% staticSJF6  = [0.006, 0.006, 0.006, 0.006, 0.006];
% GreedyInsert6      = [0.000, 0.000, 0.000, 0.000, 0.000];
% staticFIFO6        = [3.658, 2.906, 2.511, 2.278, 2.233];
mpdc5 = distinguishable_colors(8);

plot(x8, staticFIFO6, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, staticSJF6, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, GreedyInsert6, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, newSJF6, '^--', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, newFIFO6, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, Hybrid6, 'd-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [50, 500]);
xlabel('varying of |orderN|', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('staticFIFO',  'staticSJF', 'GreedyInsert', 'newSJF', 'newFIFO', 'Hybrid', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [30, 60, 120, 180, 240];
% staticSJF7  = [2119.155, 2163.696, 2065.467, 2123.636, 2186.895];
% GreedyInsert7      = [0.000, 0.000, 0.000, 3599.144, 0.000];
% staticFIFO7        = [1888.781, 2152.589, 2001.273, 2117.965, 1997.593];
mpdc5 = distinguishable_colors(8);

plot(x10, staticFIFO7, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, staticSJF7, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, GreedyInsert7, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, newSJF7, '^--', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, newFIFO7, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, Hybrid7, 'd-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [30, 240]);
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('varying of Time Range', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('staticFIFO',  'staticSJF', 'GreedyInsert', 'newSJF', 'newFIFO', 'Hybrid', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = x10;
% staticSJF8  = [0.034, 0.029, 0.033, 0.029, 0.032];
% GreedyInsert8      = [0.000, 0.000, 0.000, 488.534, 0.000];
% staticFIFO8        = [2.329, 2.470, 2.295, 2.649, 2.352];
mpdc5 = distinguishable_colors(8);

plot(x11, staticFIFO8, '^-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, staticSJF8, 's-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, GreedyInsert8, 'p-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, newSJF8, '^--', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, newFIFO8, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, Hybrid8, 'd-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
set(gca, 'XLim', [30, 240]);
xlabel('varying of Time Range', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('staticFIFO',  'staticSJF', 'GreedyInsert', 'newSJF', 'newFIFO', 'Hybrid', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

