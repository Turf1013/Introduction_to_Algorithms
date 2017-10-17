



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

staticSJF3     = [577502.631, 296916.927, 157298.963, 87489.605, 54039.744];
staticFIFO3    = [551430.476, 283740.130, 150447.119, 84676.750, 53148.096];
newFIFO3       = [188235.368, 155872.347, 187888.365, 240029.272, 263273.930];
Hybrid3        = [178849.446, 146645.030, 186095.367, 228604.785, 245512.121];
newSJF3        = [155062.792, 129877.622, 152796.155, 180108.182, 195491.837];
GreedyInsert3  = [370455.225, 366678.531, 369081.150, 350022.527, 334512.532];
staticSJF4     = [0.001, 0.001, 0.001, 0.001, 0.001];
staticFIFO4    = [0.001, 0.001, 0.001, 0.001, 0.001];
newFIFO4       = [1.008, 0.684, 1.275, 1.668, 1.807];
Hybrid4        = [1.059, 0.787, 1.221, 1.809, 1.947];
newSJF4        = [1.068, 0.847, 1.306, 1.683, 1.800];
GreedyInsert4  = [21.446, 23.668, 22.854, 32.747, 31.795];
staticSJF5     = [13213.946, 42430.951, 157298.963, 337297.167, 903086.420];
staticFIFO5    = [12957.767, 41743.329, 150447.119, 324324.024, 864919.258];
newFIFO5       = [12760.586, 45837.341, 187888.365, 411178.497, 1129772.342];
Hybrid5        = [13065.509, 47968.509, 186095.367, 404248.080, 1112784.611];
newSJF5        = [11104.956, 40341.198, 152796.155, 311622.513, 776489.484];
GreedyInsert5  = [23759.517, 87763.527, 369081.150, 812791.265, 2332118.856];
staticSJF6     = [0.000, 0.000, 0.001, 0.001, 0.003];
staticFIFO6    = [0.000, 0.000, 0.001, 0.001, 0.004];
newFIFO6       = [0.349, 0.751, 1.275, 1.914, 3.187];
Hybrid6        = [0.316, 0.648, 1.221, 1.754, 3.354];
newSJF6        = [0.369, 0.598, 1.306, 2.165, 3.208];
GreedyInsert6  = [0.115, 1.847, 22.854, 140.324, 959.731];
staticSJF7     = [145441.006, 142924.658, 157298.963, 132561.458, 127885.587];
staticFIFO7    = [138333.786, 136325.035, 150447.119, 127016.247, 122236.026];
newFIFO7       = [178153.026, 175222.427, 187888.365, 164844.905, 158781.114];
Hybrid7        = [176342.370, 170533.040, 186095.367, 162834.922, 148573.769];
newSJF7        = [137558.453, 135382.466, 152796.155, 125727.383, 119955.034];
GreedyInsert7  = [356497.560, 365131.131, 369081.150, 358081.466, 355411.614];
staticSJF8     = [0.000, 0.001, 0.001, 0.001, 0.001];
staticFIFO8    = [0.001, 0.001, 0.001, 0.001, 0.001];
newFIFO8       = [1.442, 1.281, 1.275, 1.333, 1.281];
Hybrid8        = [1.390, 1.390, 1.221, 1.339, 1.384];
newSJF8        = [1.336, 1.344, 1.306, 1.274, 1.279];
GreedyInsert8  = [31.698, 26.624, 22.854, 21.581, 16.962];






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

