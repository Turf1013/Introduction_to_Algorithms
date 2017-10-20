



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

tspSJF3        = log([56476944.221, 28359744.875, 19051654.384, 14332832.219, 11526692.564, 9664308.344, 8337875.187, 7357932.319, 6587456.350, 5962846.738, 5471067.282, 5048323.258, 4700728.279, 4399187.449, 4138441.519]);
tspFIFO3       = log([56383643.699, 28290783.661, 19026157.961, 14360989.248, 11545795.935, 9683912.047, 8349855.197, 7370468.376, 6591892.514, 5972454.535, 5480086.158, 5055923.877, 4709265.118, 4403686.345, 4147532.858]);
hstSJF3        = log([419593362.502, 207923842.276, 138447636.938, 103795718.625, 83265667.509, 69611788.904, 59816484.188, 52593227.343, 47183111.787, 42932059.158, 39218196.207, 36226086.082, 33804406.166, 31705286.856, 29889826.749]);
hstFIFO3       = log([420755195.387, 208193912.975, 138887655.847, 104387834.146, 83633118.717, 69878491.529, 60157918.999, 52844287.994, 47363752.026, 43051906.547, 39345868.039, 36327751.240, 33837326.873, 31783989.444, 29927448.204]);
newFIFO3       = log([1037744.537, 917879.397, 840824.607, 768366.361, 715314.328, 759258.294, 819190.738, 867693.363, 881651.478, 923442.116, 951838.773, 948494.349, 951180.343, 936657.037, 954859.707]);
Hybrid3        = log([1080142.676, 920527.836, 849576.965, 768132.933, 717012.417, 759144.360, 811099.495, 841967.421, 884257.658, 946035.326, 938148.781, 953061.786, 950521.656, 946792.839, 972326.493]);
MFT3           = log([1050578.044, 931126.547, 837188.263, 762863.879, 715041.908, 778745.886, 804867.762, 859938.323, 905311.928, 983899.598, 944979.885, 944196.497, 947701.509, 962003.004, 957047.181]);
newSJF3        = log([1080142.676, 955598.070, 861635.375, 785689.050, 720260.386, 779589.784, 818446.330, 867089.738, 890367.647, 949444.245, 953113.387, 961727.986, 953826.260, 956819.121, 963874.473]);
tspDD3         = log([0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000]);
GreedyInsert3  = log([327463.484, 323282.762, 324320.280, 322334.053, 322174.533, 324457.040, 323667.599, 322554.067, 322042.980, 320357.001, 320712.631, 321116.204, 321073.401, 321037.609, 321114.544]);
tspSJF4        = log([0.057, 0.053, 0.053, 0.052, 0.053, 0.052, 0.053, 0.052, 0.053, 0.051, 0.053, 0.053, 0.052, 0.052, 0.052]);
tspFIFO4       = log([0.056, 0.053, 0.053, 0.052, 0.052, 0.051, 0.051, 0.050, 0.050, 0.050, 0.051, 0.052, 0.052, 0.051, 0.050]);
hstSJF4        = log([0.179, 0.175, 0.173, 0.170, 0.169, 0.172, 0.170, 0.167, 0.167, 0.167, 0.168, 0.167, 0.171, 0.170, 0.167]);
hstFIFO4       = log([0.176, 0.170, 0.169, 0.169, 0.169, 0.168, 0.166, 0.168, 0.168, 0.168, 0.170, 0.171, 0.168, 0.171, 0.167]);
newFIFO4       = log([2.396, 1.919, 1.733, 1.619, 1.513, 1.734, 1.902, 2.066, 2.111, 2.160, 2.516, 2.825, 3.078, 3.275, 3.383]);
Hybrid4        = log([2.454, 1.958, 1.722, 1.551, 1.525, 1.777, 1.944, 2.111, 2.159, 2.161, 2.558, 2.878, 3.081, 3.361, 3.452]);
MFT4           = log([2.408, 1.928, 1.757, 1.597, 1.509, 1.765, 1.965, 2.034, 2.119, 2.162, 2.537, 2.851, 3.145, 3.342, 3.523]);
newSJF4        = log([2.397, 1.926, 1.751, 1.611, 1.519, 1.744, 1.927, 2.095, 2.138, 2.167, 2.576, 2.861, 3.072, 3.328, 3.483]);
tspDD4         = log([0.049, 0.049, 0.049, 0.049, 0.049, 0.049, 0.050, 0.049, 0.049, 0.050, 0.049, 0.050, 0.049, 0.050, 0.049]);
GreedyInsert4  = log([32.187, 32.905, 32.141, 32.583, 33.277, 35.270, 37.660, 39.375, 40.175, 41.816, 42.348, 43.916, 45.434, 45.403, 46.276]);
tspSJF5        = log([604213.196, 1842936.424, 7357932.319, 15506204.157, 42958608.883]);
tspFIFO5       = log([604718.340, 1845454.018, 7370468.376, 15549552.613, 43051593.041]);
hstSJF5        = log([4376499.112, 14314560.764, 52593227.343, 115098062.393, 319186841.806]);
hstFIFO5       = log([4380334.274, 14318167.376, 52844287.994, 115473249.175, 319673277.715]);
newFIFO5       = log([52302.935, 213736.298, 867693.363, 1925071.102, 5292092.127]);
Hybrid5        = log([54347.943, 219475.065, 841967.421, 1917223.287, 5301948.677]);
MFT5           = log([55559.527, 207263.930, 859938.323, 1888683.883, 5354956.011]);
newSJF5        = log([52840.500, 220463.015, 867089.738, 1903602.006, 5227044.496]);
tspDD5         = log([0.000, 0.000, 0.000, 0.000, 0.000]);
GreedyInsert5  = log([24916.173, 86361.219, 322554.067, 667262.253, 1830789.757]);
tspSJF6        = log([0.051, 0.051, 0.052, 0.052, 0.056]);
tspFIFO6       = log([0.051, 0.049, 0.050, 0.052, 0.055]);
hstSJF6        = log([0.167, 0.170, 0.167, 0.174, 0.172]);
hstFIFO6       = log([0.167, 0.166, 0.168, 0.167, 0.171]);
newFIFO6       = log([0.504, 1.016, 2.066, 3.075, 5.103]);
Hybrid6        = log([0.509, 1.031, 2.111, 3.106, 5.159]);
MFT6           = log([0.521, 1.040, 2.034, 3.052, 5.168]);
newSJF6        = log([0.506, 1.043, 2.095, 3.077, 5.209]);
tspDD6         = log([0.049, 0.048, 0.049, 0.051, 0.049]);
GreedyInsert6  = log([0.132, 2.408, 39.375, 175.305, 1344.709]);









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
x7 = [50, 100, 200, 300, 500];
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
set(gca, 'XLim', [min(x7), max(x7)+200]);
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
set(gca, 'XLim', [min(x8), max(x8)+200]);
xlabel('varying of |orderN|', 'FontSize', 14);
ylabel('Time(seconds)', 'FontSize', 14);
h_legend = legend('GreedyInsert', 'SJF', 'FIFO', 'MinFlowFirst', 'tspFIFO', 'tspSJF', 'hstFIFO', 'hstSJF', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

