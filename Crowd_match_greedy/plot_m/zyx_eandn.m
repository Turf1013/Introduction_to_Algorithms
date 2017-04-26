
fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [1,3,5,7,9];
opt1 = [568.034400, 1499.245500, 1765.530900, 2197.152900, 2165.485700];
simg1 = [501.000600, 1294.421300, 1546.969400, 1923.108300, 1884.120100];
extended1 = [179.518167, 647.835500, 804.407333, 1106.900967, 1058.322200];
fgoa1 = [443.328500, 1164.686200, 1379.449400, 1739.302400, 1714.382100];
fgoag1 = [345.132200, 945.351600, 1106.179200, 1356.656300, 1398.519100];
mpdc5 = distinguishable_colors(5);
plot(x1, extended1, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, fgoa1, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, fgoag1, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, simg1, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, opt1, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%

xlabel('1/\lambda', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [2,5,10,20,50];
opt2 = [508.042400, 1157.315300, 1765.530900, 2403.455800, 2770.181500];
simg2 = [451.245200, 1007.017800, 1546.969400, 2067.971600, 2384.190300];
extended2 = [225.622600, 640.167350, 804.407333, 1068.891500, 1292.777650];
fgoa2 = [412.580200, 891.092900, 1379.449400, 1939.476700, 2169.331300];
fgoag2 = [325.858900, 707.713400, 1106.179200, 1588.794300, 1847.863900];
%旋转
set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
%
mpdc5 = distinguishable_colors(5);
plot(x2, extended2, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, fgoa2, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, fgoag2, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, simg2, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, opt2, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);




%调字体
xlabel('p_t', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [2.5,3.75,5,6.25,7.5];
opt3 = [2442.542100, 3035.853000, 3546.077500, 4265.989500, 4974.915700];
simg3 = [2221.604500, 2787.986700, 3238.847400, 3966.371900, 4594.346700];
extended3 = [1107.738733, 1559.417867, 1938.452267, 2507.935467, 2979.584500];
fgoa3 = [1988.993700, 2515.325500, 2942.461300, 3550.782000, 4119.636900];
fgoag3 = [1571.114200, 1948.555800, 2289.165100, 2773.377700, 3229.479100];
%旋转
set(gca, 'FontSize', fontsize, 'Xtick', x3);
%
mpdc5 = distinguishable_colors(5);
plot(x3, extended3, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, fgoa3, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, fgoag3, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, simg3, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, opt3, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

xlabel('\mu', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [2.5,3.75,5,6.25,7.5];
opt4 = [688.203400, 1857.085500, 3546.077500, 6906.668400, 17703.789100];
simg4 = [642.602800, 1711.951200, 3238.847400, 6311.882900, 16299.620500];
extended4 = [321.301400, 1014.573900, 1938.452267, 3867.515000, 13782.869750];
fgoa4 = [568.682500, 1522.146800, 2942.461300, 5704.927700, 14324.323800];
fgoag4 = [436.088400, 1208.948100, 2289.165100, 4427.008600, 11192.406300];
mpdc5 = distinguishable_colors(5);
plot(x4, extended4, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, fgoa4, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, fgoag4, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, simg4, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, opt4, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x4);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = x1;
%%opt5 = [18.038295, 19.833016, 22.472543, 25.407027, 27.507256];
simg5 = [0.091794, 0.074003, 0.066391, 0.072534, 0.077378];
extended5 = [0.049529, 0.050893, 0.039061, 0.044892, 0.043823];
fgoa5 = [37.490087, 47.033891, 34.649089, 38.963362, 14.207536];
fgoag5 = [0.053316, 0.06438, 0.064113, 0.066192, 0.066793];
mpdc4 = distinguishable_colors(4);
plot(x5, extended5, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, fgoa5, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, fgoag5, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, simg5, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
%set(gca, 'XLim', [25, 125]);
xlabel('1/\lambda', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x6 = x2;
%%opt6 = [12.283837, 22.318861, 22.472543, 24.284763, 23.085961];
simg6 = [0.066806, 0.090261, 0.066391, 0.049033, 0.077839];
extended6 = [0.059782, 0.027452, 0.039061, 0.034079, 0.033649];
fgoa6 = [26.842072, 45.013443, 34.649089, 45.839235, 43.735012];
fgoag6 = [0.063062, 0.065462, 0.064113, 0.066429, 0.06658];
mpdc4 = distinguishable_colors(4);
plot(x6, extended6, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, fgoa6, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, fgoag6, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, simg6, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = x3;
%%opt7 = [17.469837, 25.045681, 21.717297, 17.732461, 16.544985];
simg7 = [0.089557, 0.074866, 0.036807, 0.062923, 0.087731];
extended7 = [0.039527, 0.055888, 0.044674, 0.0459, 0.043649];
fgoa7 = [33.804575, 54.540837, 39.505566, 17.325587, 46.299534];
fgoag7 = [0.068209, 0.06645, 0.067494, 0.04836, 0.062852];
mpdc4 = distinguishable_colors(4);
plot(x7, extended7, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, fgoa7, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, fgoag7, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, simg7, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x7);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 =x4;
%%opt8 = [23.736456, 23.328947, 21.717297, 23.533237, 12.992262];
simg8 = [0.067069, 0.036771, 0.036807, 0.087578, 0.07107];
extended8 = [0.023835, 0.029951, 0.044674, 0.05246, 0.061907];
fgoa8 = [36.607446, 28.672225, 39.505566, 57.018652, 32.795437];
fgoag8 = [0.06503, 0.064945, 0.067494, 0.06751, 0.068085];
mpdc4 = distinguishable_colors(4);
plot(x8, extended8, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, fgoa8, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, fgoag8, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, simg8, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x8);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = x1;
%opt = [17.82421875, 17.8203125, 17.72265625, 17.72265625, 17.7734375];
simg9 = [17.2734375, 17.2734375, 17.24609375, 17.25, 17.203125];
extended9 = [17.3828125, 17.27734375, 17.25, 17.25390625, 17.390625];
fgoa9 = [17.29296875, 17.4765625, 17.484375, 17.484375, 17.2421875];
fgoag9 = [17.2890625, 17.46875, 17.4765625, 17.4765625, 17.28125];
mpdc4 = distinguishable_colors(4);
plot(x9, extended9, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, fgoa9, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, fgoag9, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, simg9, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
%set(gca, 'XLim', [25, 125]);
xlabel('1/\lamda', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = x2;
%opt10 = [17.71484375, 17.71484375, 17.72265625, 17.7734375, 17.828125];
simg10 = [17.23828125, 17.23828125, 17.24609375, 17.203125, 17.28125];
extended10 = [17.2421875, 17.2421875, 17.25, 17.38671875, 17.390625];
fgoa10 = [17.47265625, 17.484375, 17.484375, 17.2421875, 17.296875];
fgoag10 = [17.46484375, 17.4765625, 17.4765625, 17.2890625, 17.29296875];
mpdc4 = distinguishable_colors(4);
plot(x10, extended10, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, fgoa10, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, fgoag10, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, simg10, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = x3;
%%opt11 = [17.7734375, 17.7734375, 17.7734375, 17.82421875, 17.828125];
simg11 = [17.203125, 17.203125, 17.203125, 17.2734375, 17.28125];
extended11 = [17.390625, 17.38671875, 17.3828125, 17.3828125, 17.390625];
fgoa11 = [17.2421875, 17.4765625, 17.47265625, 17.2890625, 17.296875];
fgoag11 = [17.29296875, 17.46875, 17.46484375, 17.28515625, 17.29296875];
mpdc4 = distinguishable_colors(4);
plot(x11, extended11, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, fgoa11, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, fgoag11, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, simg11, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x11);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = x4;
%opt12 = [17.7734375, 17.7734375, 17.7734375, 17.7734375, 17.87890625];
simg12 = [17.203125, 17.203125, 17.203125, 17.203125, 17.3515625];
extended12 = [17.4140625, 17.3828125, 17.3828125, 17.38671875, 17.4609375];
fgoa12 = [17.25, 17.2421875, 17.47265625, 17.2421875, 17.296875];
fgoag12 = [17.28125, 17.2734375, 17.46484375, 17.2890625, 17.29296875];
mpdc4 = distinguishable_colors(4);
plot(x12, extended12, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, fgoa12, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, fgoag12, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, simg12, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x12);
%set(gca, 'XLim', [25, 125]);
xlabel('p_t', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
