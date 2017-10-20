



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

tspSJF1        = log([128727776.552, 66983319.765, 46437291.049, 36832655.915, 30756908.755]);
hstSJF1        = log([111401622.813, 73558041.206, 43452152.484, 32567660.865, 30477912.044]);
hstFIFO1       = log([111382427.939, 73566308.979, 43508433.945, 32593667.430, 30491186.751]);
newFIFO1       = log([2135343.053, 1079008.108, 725316.936, 547853.931, 447979.145]);
Hybrid1        = log([2141978.163, 1083796.898, 721823.809, 549633.766, 447021.108]);
MFT1           = log([2118448.839, 1073657.194, 720380.536, 551134.678, 447760.127]);
newSJF1        = log([2142470.335, 1084236.013, 730991.567, 553966.061, 448060.223]);
tspFIFO1       = log([128758050.561, 67001021.197, 46433804.347, 36867413.927, 30754144.909]);
GreedyInsert1  = log([539798.125, 195660.972, 113457.957, 77393.529, 60582.137]);
tspSJF2        = log([0.074, 0.079, 0.082, 0.084, 0.088]);
hstSJF2        = log([0.254, 0.256, 0.256, 0.257, 0.259]);
hstFIFO2       = log([0.253, 0.255, 0.258, 0.257, 0.259]);
newFIFO2       = log([10.546, 10.560, 10.614, 10.584, 10.627]);
Hybrid2        = log([10.626, 10.622, 10.670, 10.675, 10.672]);
MFT2           = log([10.674, 10.661, 10.675, 10.688, 10.723]);
newSJF2        = log([10.649, 10.617, 10.641, 10.658, 10.640]);
tspFIFO2       = log([0.075, 0.079, 0.082, 0.084, 0.088]);
GreedyInsert2  = log([127.206, 13.964, 3.394, 1.097, 0.495]);
tspSJF3        = log([336224694.503, 170789272.767, 115499975.463, 87848057.353, 71292369.159, 60163694.848, 52640907.005, 46437291.049, 41810399.789, 38565867.158, 35975830.431, 33718116.042, 31485711.500, 29427549.845, 27476974.032]);
hstSJF3        = log([312834024.489, 158051247.496, 106927914.886, 81188965.896, 66021770.493, 56053053.757, 48728198.873, 43452152.484, 39284572.771, 35981087.517, 33190117.245, 30948002.204, 29096059.342, 27494934.671, 26076454.721]);
hstFIFO3       = log([313328178.143, 158273531.619, 107094143.846, 81327374.574, 66135862.426, 56132499.213, 48801312.777, 43508433.945, 39349954.309, 36071412.827, 33254565.308, 30986965.737, 29146301.762, 27543580.065, 26091373.578]);
newFIFO3       = log([899457.092, 800195.955, 723431.743, 665342.505, 620550.841, 667744.510, 695391.421, 725316.936, 747821.541, 786358.053, 790647.973, 788090.422, 788885.066, 787079.764, 787098.192]);
Hybrid3        = log([907961.145, 804939.144, 727129.245, 669854.668, 624089.992, 668624.826, 698795.699, 721823.809, 754064.360, 790415.308, 788252.238, 786133.670, 791464.579, 790658.203, 786925.195]);
MFT3           = log([899235.487, 797715.078, 722945.054, 668235.792, 622029.226, 667923.921, 699127.826, 720380.536, 753091.816, 793879.107, 784163.883, 786214.832, 788007.326, 787096.591, 790520.755]);
newSJF3        = log([907961.145, 805117.409, 733872.370, 673752.180, 626590.818, 672134.532, 703252.601, 730991.567, 758263.706, 792796.847, 790547.908, 796231.254, 792320.128, 793662.265, 793256.508]);
tspFIFO3       = log([335940756.881, 170594131.169, 115515108.852, 87862649.237, 71383813.147, 60175407.049, 52674372.344, 46433804.347, 41801944.067, 38613775.231, 36000156.077, 33705462.500, 31508981.485, 29446472.307, 27498420.070]);
GreedyInsert3  = log([195386.953, 151428.400, 128069.128, 120327.496, 113700.750, 113396.297, 113602.987, 113457.957, 113175.746, 113246.929, 113237.208, 113247.536, 113247.536, 113247.536, 113247.536]);
tspSJF4        = log([0.181, 0.126, 0.104, 0.096, 0.090, 0.086, 0.083, 0.082, 0.080, 0.078, 0.077, 0.076, 0.077, 0.076, 0.076]);
hstSJF4        = log([0.287, 0.270, 0.264, 0.260, 0.259, 0.259, 0.258, 0.256, 0.256, 0.257, 0.256, 0.256, 0.255, 0.255, 0.255]);
hstFIFO4       = log([0.285, 0.269, 0.263, 0.261, 0.259, 0.257, 0.257, 0.258, 0.256, 0.256, 0.255, 0.254, 0.255, 0.256, 0.254]);
newFIFO4       = log([12.286, 9.834, 8.953, 8.317, 7.807, 9.154, 10.019, 10.614, 10.908, 11.147, 13.013, 14.468, 15.745, 16.719, 17.530]);
Hybrid4        = log([12.326, 9.883, 8.987, 8.328, 7.868, 9.252, 10.163, 10.670, 10.999, 11.194, 13.064, 14.539, 15.799, 16.766, 17.538]);
MFT4           = log([12.234, 9.912, 9.063, 8.331, 7.836, 9.225, 10.113, 10.675, 11.102, 11.214, 13.116, 14.505, 15.783, 16.802, 17.623]);
newSJF4        = log([12.258, 9.902, 8.958, 8.355, 7.848, 9.182, 10.102, 10.641, 10.964, 11.176, 13.054, 14.510, 15.805, 16.813, 17.635]);
tspFIFO4       = log([0.184, 0.128, 0.105, 0.097, 0.091, 0.087, 0.084, 0.082, 0.080, 0.078, 0.077, 0.077, 0.077, 0.076, 0.076]);
GreedyInsert4  = log([9.041, 4.854, 3.480, 3.393, 3.197, 3.338, 3.388, 3.394, 3.400, 3.401, 3.401, 3.401, 3.403, 3.404, 3.403]);
tspSJF5        = log([4046652.485, 13111569.401, 46437291.049, 175021153.329, 384725868.216]);
hstSJF5        = log([2673331.442, 12522749.908, 43452152.484, 160664812.739, 346195401.224]);
hstFIFO5       = log([2677038.855, 12519722.196, 43508433.945, 160656829.361, 345920396.897]);
newFIFO5       = log([39193.782, 189431.362, 725316.936, 2857335.159, 6419697.286]);
Hybrid5        = log([39491.229, 189931.109, 721823.809, 2872386.135, 6441909.355]);
MFT5           = log([39374.223, 187822.729, 720380.536, 2858041.517, 6423550.924]);
newSJF5        = log([39350.965, 188260.047, 730991.567, 2860974.718, 6420509.850]);
tspFIFO5       = log([4046652.485, 13105194.271, 46433804.347, 174835207.267, 384641416.035]);
GreedyInsert5  = log([8754.984, 32654.336, 113457.957, 478632.794, 1169839.383]);
tspSJF6        = log([0.060, 0.070, 0.082, 0.108, 0.134]);
hstSJF6        = log([0.248, 0.253, 0.256, 0.267, 0.276]);
hstFIFO6       = log([0.249, 0.252, 0.258, 0.265, 0.273]);
newFIFO6       = log([2.144, 5.315, 10.614, 21.083, 31.695]);
Hybrid6        = log([2.158, 5.347, 10.670, 21.242, 31.833]);
MFT6           = log([2.153, 5.361, 10.675, 21.370, 31.929]);
newSJF6        = log([2.151, 5.328, 10.641, 21.174, 31.749]);
tspFIFO6       = log([0.060, 0.070, 0.082, 0.108, 0.134]);
GreedyInsert6  = log([0.008, 0.146, 3.394, 93.280, 594.728]);














%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [10, 20, 30, 40, 50];
% GreedyInsert1      = [4800.000, 3400.000, 3136.000, 2097.135, 1857.673, 1688.443, 864.679, 386.815];
% FirstInFirstServe1           = [4800.000, 3224.000, 2838.491, 1893.000, 1588.122, 948.299, 538.619, 323.189];
% ShortestJobFirst1        = [4800.000, 3312.000, 3086.057, 2147.250, 1773.642, 1150.514, 612.204, 378.257];
mpdc5 = distinguishable_colors(10);
plot(x1, GreedyInsert1, 'p-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, newSJF1, '^-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, newFIFO1, 's-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, MFT1, 'h-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, tspFIFO1, 'd-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, tspSJF1, 'x-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, hstFIFO1, '<-', 'Color', mpdc5(7, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, hstSJF1, '>-', 'Color', mpdc5(8, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% 1:blue, 2:red, 3:green
%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%
set(gca, 'XLim', [min(x1), max(x1)+20]);
xlabel('varying of |worker|', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('GreedyInsert', 'SJF', 'FIFO', 'MinFlowFirst', 'tspFIFO', 'tspSJF', 'hstFIFO', 'hstSJF', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');
x2 = x1;
box on;
mpdc5 = distinguishable_colors(10);
plot(x2, GreedyInsert2, 'p-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, newSJF2, '^-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, newFIFO2, 's-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, MFT2, 'h-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, tspFIFO2, 'd-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, tspSJF2, 'x-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, hstFIFO2, '<-', 'Color', mpdc5(7, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, hstSJF2, '>-', 'Color', mpdc5(8, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [min(x2), max(x2)+20]);
xlabel('varying of |worker|', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('GreedyInsert', 'SJF', 'FIFO', 'MinFlowFirst', 'tspFIFO', 'tspSJF', 'hstFIFO', 'hstSJF', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15];
mpdc5 = distinguishable_colors(10);
plot(x4, GreedyInsert3, 'p-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, newSJF3, '^-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, newFIFO3, 's-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, MFT3, 'h-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, tspFIFO3, 'd-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, tspSJF3, 'x-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, hstFIFO3, '<-', 'Color', mpdc5(7, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, hstSJF3, '>-', 'Color', mpdc5(8, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'XLim', [min(x4), max(x4)+6]);
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('Varying of Capacity', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('GreedyInsert', 'SJF', 'FIFO', 'MinFlowFirst', 'tspFIFO', 'tspSJF', 'hstFIFO', 'hstSJF', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = x4;
mpdc5 = distinguishable_colors(10);
plot(x5, GreedyInsert4, 'p-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, newSJF4, '^-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, newFIFO4, 's-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, MFT4, 'h-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, tspFIFO4, 'd-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, tspSJF4, 'x-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, hstFIFO4, '<-', 'Color', mpdc5(7, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, hstSJF4, '>-', 'Color', mpdc5(8, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
set(gca, 'XLim', [min(x5), max(x5)+6]);
xlabel('Varying of Capacity', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('GreedyInsert', 'SJF', 'FIFO', 'MinFlowFirst', 'tspFIFO', 'tspSJF', 'hstFIFO', 'hstSJF', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [200, 500, 1000, 2000, 3000];
mpdc5 = distinguishable_colors(10);
plot(x7, GreedyInsert5, 'p-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, newSJF5, '^-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, newFIFO5, 's-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, MFT5, 'h-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, tspFIFO5, 'd-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, tspSJF5, 'x-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, hstFIFO5, '<-', 'Color', mpdc5(7, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, hstSJF5, '>-', 'Color', mpdc5(8, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%
set(gca, 'XLim', [min(x7), max(x7)+1300]);
xlabel('varying of |order|', 'FontSize', 14);
ylabel('Sum Flow Time', 'FontSize', 14);
h_legend = legend('GreedyInsert', 'SJF', 'FIFO', 'MinFlowFirst', 'tspFIFO', 'tspSJF', 'hstFIFO', 'hstSJF', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = x7;
mpdc5 = distinguishable_colors(10);
plot(x8, GreedyInsert6, 'p-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, newSJF6, '^-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, newFIFO6, 's-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, MFT6, 'h-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, tspFIFO6, 'd-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, tspSJF6, 'x-', 'Color', mpdc5(6, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, hstFIFO6, '<-', 'Color', mpdc5(7, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, hstSJF6, '>-', 'Color', mpdc5(8, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [min(x8), max(x8)+1300]);
xlabel('varying of |orderN|', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('GreedyInsert', 'SJF', 'FIFO', 'MinFlowFirst', 'tspFIFO', 'tspSJF', 'hstFIFO', 'hstSJF', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

