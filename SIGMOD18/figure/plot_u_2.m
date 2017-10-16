



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

newFIFO3       = [475379.415, 385321.014, 487077.580, 628905.069, 649273.119];
Hybrid3        = [459865.327, 370973.086, 480393.766, 595081.903, 643691.765];
staticSJF3 = [979304.052, 976989.051, 1026043.696, 1021380.956, 1142629.298];
newSJF3        = [421120.550, 349758.744, 424670.928, 531253.174, 542765.386];
staticFIFO3 = [979304.052, 976895.444, 1026387.066, 1023351.195, 1143813.586];
GreedyInsert3  = [954249.925, 935651.204, 935608.753, 911887.789, 908655.304];
newFIFO4       = [1.162, 0.728, 1.372, 1.744, 1.835];
Hybrid4        = [1.083, 0.660, 1.378, 1.800, 1.817];
staticSJF4 = [0.001, 0.038, 0.037, 0.046, 0.050];
newSJF4        = [1.073, 0.757, 1.393, 1.711, 1.870];
staticFIFO4 = [0.002, 0.038, 0.037, 0.048, 0.052];
GreedyInsert4  = [25.340, 21.980, 25.846, 27.802, 34.004];
newFIFO5       = [31092.263, 125063.938, 487077.580, 1081364.058, 3010984.610];
Hybrid5        = [31274.039, 123221.136, 480393.766, 1081276.417, 3022703.060];
staticSJF5 = [72219.059, 259859.087, 1026043.696, 2243048.757, 6189648.466];
newSJF5        = [27067.030, 108087.115, 424670.928, 938390.625, 2503758.406];
staticFIFO5 = [72407.539, 260132.254, 1026387.066, 2243142.218, 6190476.822];
GreedyInsert5  = [61334.395, 233345.554, 935608.753, 2070157.560, 6056917.075];
newFIFO6       = [0.332, 0.665, 1.372, 1.933, 3.420];
Hybrid6        = [0.335, 0.735, 1.378, 1.952, 3.201];
staticSJF6 = [0.010, 0.020, 0.037, 0.064, 0.083];
newSJF6        = [0.325, 0.649, 1.393, 1.993, 3.265];
staticFIFO6 = [0.017, 0.018, 0.037, 0.058, 0.119];
GreedyInsert6  = [0.126, 1.398, 25.846, 154.712, 1158.089];
newFIFO7       = [489936.150, 487079.484, 487077.580, 473739.874, 457799.839];
Hybrid7        = [478730.843, 477304.488, 480393.766, 454630.485, 456339.583];
staticSJF7 = [1034631.417, 1031741.417, 1026043.696, 1020128.083, 1014157.583];
newSJF7        = [423998.072, 407129.481, 424670.928, 400181.480, 399626.310];
staticFIFO7 = [1034875.813, 1031985.813, 1026387.066, 1020372.479, 1014401.979];
GreedyInsert7  = [937931.929, 919399.712, 935608.753, 959711.804, 949168.862];
newFIFO8       = [1.276, 1.268, 1.372, 1.357, 1.254];
Hybrid8        = [1.420, 1.374, 1.378, 1.341, 1.393];
staticSJF8 = [0.038, 0.044, 0.037, 0.044, 0.040];
newSJF8        = [1.320, 1.328, 1.393, 1.336, 1.366];
staticFIFO8 = [0.036, 0.047, 0.037, 0.046, 0.039];
GreedyInsert8  = [23.335, 25.455, 25.846, 23.639, 22.943];




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

