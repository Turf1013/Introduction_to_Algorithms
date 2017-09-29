



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%1---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x1 = [500,1000,2500,5000,10000];
rrk1 = [3165.000, 4474.000, 6947.667, 12236.500, 21950.667];
mcf1 = [3068.000, 3662.000, 6249.000, 0.000, 0.000];
laf1 = [3159.167, 4158.500, 6793.000, 11902.500, 20552.167];
aam1 = [3159.167, 4126.000, 6488.500, 11521.833, 19410.833];
mpdc5 = distinguishable_colors(5);
plot(x1, rrk1, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, mcf1, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, laf1, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x1, aam1, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x1 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x1);
%
set(gca, 'XLim', [500, 10000]);
xlabel('|T|', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [500,1000,2500,5000,10000];
rrk2 = [0.086, 0.237, 1.220, 4.712, 17.695];
mcf2 = [117.146, 1586.683, 32895.157, 0.000, 0.000];
laf2 = [0.094, 0.258, 1.275, 4.916, 18.084];
aam2 = [0.095, 0.266, 1.451, 5.863, 22.136];
mpdc5 = distinguishable_colors(5);
plot(x2, rrk2, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, mcf2, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, laf2, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, aam2, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
set(gca, 'XLim', [500, 10000]);
xlabel('|T|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [500,1000,2500,5000,10000];
rrk3 = [18.949, 18.949, 18.949, 19.106, 19.258];
mcf3 = [38.086, 95.344, 496.281, 0.000, 0.000];
laf3 = [18.949, 18.949, 18.949, 19.106, 19.258];
aam3 = [18.953, 18.953, 18.953, 19.109, 19.262];
mpdc5 = distinguishable_colors(5);
plot(x3, rrk3, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, mcf3, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, laf3, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, aam3, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set( gca(), 'XTickLabel', x3 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x3);
set(gca, 'XLim', [500, 10000]);
xlabel('|T|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;


%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [2,4,6,8,10];
rrk4 = [17731.000, 10268.500, 6947.667, 6163.000, 5015.333];
mcf4 = [0.000, 0.000, 6249.000, 4815.000, 4918.500];
laf4 = [16528.667, 9579.833, 6793.000, 6161.667, 4924.500];
aam4 = [15630.000, 9010.333, 6488.500, 5954.333, 5014.333];
mpdc5 = distinguishable_colors(5);
plot(x4, rrk4, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, mcf4, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, laf4, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, aam4, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('|K|', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = [2,4,6,8,10];
rrk5 = [3.508, 1.789, 1.220, 0.919, 0.769];
mcf5 = [0.000, 0.000, 32895.157, 26529.013, 17393.253];
laf5 = [3.400, 1.850, 1.275, 1.023, 0.820];
aam5 = [4.200, 2.180, 1.451, 1.131, 0.913];
mpdc5 = distinguishable_colors(5);
plot(x5, rrk5, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, mcf5, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, laf5, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, aam5, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
%set(gca, 'XLim', [25, 125]);
xlabel('|K|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x6 = [2,4,6,8,10];
rrk6 = [18.949, 18.949, 18.949, 18.949, 18.949];
mcf6 = [0.000, 0.000, 496.281, 377.012, 305.453];
laf6 = [18.949, 18.949, 18.949, 18.949, 18.949];
aam6 = [18.953, 18.953, 18.953, 18.953, 18.953];
mpdc5 = distinguishable_colors(5);
plot(x6, rrk6, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, mcf6, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, laf6, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, aam6, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
%set(gca, 'XLim', [25, 125]);
xlabel('|K|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [0.01, 0.05, 0.1, 0.15, 0.2];
rrk7 = [14067.833, 9127.667, 6947.667, 6132.667, 5409.833];
mcf7 = [13315.0, 0.000, 6249.000, 5805.500, 4998.000];
laf7 = [13435.000, 8832.500, 6793.000, 5960.667, 5183.167];
aam7 = [13224.000, 8360.000, 6488.500, 5448.500, 5012.833];
mpdc5 = distinguishable_colors(5);
plot(x7, rrk7, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, mcf7, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, laf7, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, aam7, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%
set(gca, 'XLim', [0.01, 0.2]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = [0.01, 0.05, 0.1, 0.15, 0.2];
rrk8 = [2.452, 1.570, 1.220, 0.991, 0.823];
mcf8 = [0.000, 0.000, 32895.157, 21620.690, 19801.748];
laf8 = [2.569, 1.652, 1.275, 1.048, 0.881];
aam8 = [2.871, 1.883, 1.451, 1.205, 1.018];
mpdc5 = distinguishable_colors(5);
plot(x8, rrk8, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, mcf8, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, laf8, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, aam8, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
set(gca, 'XLim', [0.01, 0.2]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = [0.01, 0.05, 0.1, 0.15, 0.2];
rrk9 = [18.949, 18.949, 18.949, 18.949, 18.949];
mcf9 = [0.000, 0.000, 496.281, 400.914, 400.914];
laf9 = [18.949, 18.949, 18.949, 18.949, 18.949];
aam9 = [18.953, 18.953, 18.953, 18.953, 18.953];
mpdc5 = distinguishable_colors(5);
plot(x9, rrk9, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, mcf9, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, laf9, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, aam9, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
set(gca, 'XLim', [0.01, 0.2]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [0.75,0.8,0.85,0.9,0.95];
rrk10 = [13067.500, 9882.000, 6947.667, 6020.667, 4936.000];
mcf10 = [10412.000, 0.000, 6249.000, 6217.000, 0.000];
laf10 = [12726.667, 9156.000, 6793.000, 5749.667, 4955.167];
aam10 = [12323.000, 9015.333, 6488.500, 5550.333, 4712.667];
mpdc5 = distinguishable_colors(5);
plot(x10, rrk10, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, mcf10, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, laf10, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, aam10, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('\mu', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = [0.75,0.8,0.85,0.9,0.95];
rrk11 = [2.332, 1.642, 1.220, 0.923, 0.770];
mcf11 = [39398.169, 0.000, 32895.157, 31792.358, 0.000];
laf11 = [2.477, 1.729, 1.275, 0.967, 0.778];
aam11 = [2.752, 1.980, 1.451, 1.151, 0.912];
mpdc5 = distinguishable_colors(5);
plot(x11, rrk11, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, mcf11, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, laf11, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, aam11, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = [0.75,0.8,0.85,0.9,0.95];
rrk12 = [18.949, 18.949, 18.949, 18.949, 18.949];
mcf12 = [496.281, 0.000, 496.281, 496.281, 0.000];
laf12 = [18.949, 18.949, 18.949, 18.949, 18.949];
aam12 = [18.953, 18.953, 18.953, 18.953, 18.953];
mpdc5 = distinguishable_colors(5);
plot(x12, rrk12,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, mcf12, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, laf12, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, aam12, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x12 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x12);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%13---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x13 = [0.75,0.8,0.85,0.9,0.95];
rrk13 = [13240.167, 9268.667, 7376.833, 5834.000, 4640.000];
mcf13 = [0.000, 8324.000, 0.000, 4145.000, 4163.000];
laf13 = [12108.833, 8983.500, 7196.000, 5566.000, 4425.500];
aam13 = [12014.833, 8838.833, 6835.000, 5455.167, 4435.000];
mpdc5 = distinguishable_colors(5);
plot(x13, rrk13, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, mcf13, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, laf13, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, aam13, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x13 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x13);
%

xlabel('mean', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%14---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x14 =  [0.75,0.8,0.85,0.9,0.95];
rrk14 = [2.421, 1.628, 1.128, 0.908, 0.748];
mcf14 = [0.000, 39719.082, 0.000, 35988.334, 32416.289];
laf14 = [2.550, 1.707, 1.376, 0.970, 0.779];
aam14 = [2.833, 1.933, 1.424, 1.120, 0.894];
mpdc5 = distinguishable_colors(5);
plot(x14, rrk14, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, mcf14, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, laf14, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, aam14, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x14 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x14);
%set(gca, 'XLim', [25, 125]);
xlabel('mean', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%15---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x15 =  [0.75,0.8,0.85,0.9,0.95];
rrk15 = [18.949, 18.949, 18.949, 18.949, 18.949];
mcf15 = [0.000, 496.281, 0.000, 496.281, 496.281];
laf15 = [18.949, 18.949, 18.949, 18.949, 18.949];
aam15 = [18.953, 18.953, 18.953, 18.953, 18.953];
mpdc5 = distinguishable_colors(5);
plot(x15, rrk15,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, mcf15, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, laf15, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, aam15, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x15 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x15);
% set(gca, 'XLim', [10000, 100000]);
xlabel('mean', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%16---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x16 = [10000,20000,30000,40000,50000,100000];
rrk16 = [22588.667, 41706.833, 61293.000, 78884.000, 98777.167, 192637.000];
% mcf16 = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
laf16 = [20891.667, 38432.500, 56170.500, 72584.167, 89188.000, 173425.000];
aam16 = [19278.000, 36250.667, 52721.833, 68068.667, 84786.833, 167430.000];
mpdc5 = distinguishable_colors(5);
plot(x16, rrk16, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x16, mcf16, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, laf16, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, aam16, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x16 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x16);
%
set(gca, 'XLim', [10000, 100000]);
xlabel('|T|', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM',  'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%17---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x17 = [10000,20000,30000,40000,50000,100000];
rrk17 = [16.800, 67.479, 150.654, 266.098, 417.133, 1642.870];
% mcf17 = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
laf17 = [17.257, 68.374, 153.550, 275.393, 419.384, 1636.908];
aam17 = [21.853, 86.515, 194.986, 344.678, 531.715, 1992.199];
mpdc5 = distinguishable_colors(5);
plot(x17, rrk17, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x17, mcf17, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, laf17, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, aam17, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x17 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x17);
set(gca, 'XLim', [10000, 100000]);
xlabel('|T|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%18---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x18 = [10000,20000,30000,40000,50000,100000];
rrk18 = [35.738, 36.207, 36.586, 36.965, 37.340, 39.250];
% mcf18 = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
laf18 = [35.738, 36.043, 36.348, 36.809, 37.148, 38.867];
aam18 = [35.742, 36.211, 36.590, 36.969, 37.344, 39.254];
mpdc5 = distinguishable_colors(5);
plot(x18, rrk18,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x18, mcf18, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, laf18, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, aam18, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x18 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x18);
set(gca, 'XLim', [10000, 100000]);
xlabel('|T|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%19---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x19 = [0.12,0.14,0.16,0.18,0.20];
rrk19 = [127569, 124121, 111431, 111431, 108742];
laf19 = [93118, 92117, 90781, 90781, 88772];
aam19 = [92099, 90781, 89895, 89895, 87784];
mpdc5 = distinguishable_colors(5);
plot(x19, rrk19, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x19, mcf19, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, laf19, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, aam19, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x19 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x19);
%
set(gca, 'XLim', [0.12, 0.20]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%20---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x20 = [0.12,0.14,0.16,0.18,0.20];
rrk20 = [14.9784, 14.2351, 13.5433, 13.3006, 13.4925];
laf20 = [8.9474, 8.2708, 7.8317, 7.6094, 7.0848];
aam20 = [15.1098, 13.4696, 12.6956, 12.7458, 11.5837];
mpdc5 = distinguishable_colors(5);
plot(x20, rrk20, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x20, mcf20, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, laf20, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, aam20, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x20 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x20);
set(gca, 'XLim', [0.12, 0.20]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%21---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x21 = [0.12,0.14,0.16,0.18,0.20];
rrk21 = [9.5243, 9.0103, 8.5402, 8.1308, 7.7197];
laf21 = 8.9474, 8.2708, 7.8317, 7.6094, 7.0848];
aam21 = [20.7422, 20.7422, 20.7422, 20.7422, 20.7422];
mpdc5 = distinguishable_colors(5);
plot(x21, rrk21,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, laf21, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, aam21, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x21, mcf21, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x21 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x21);
set(gca, 'XLim', [0.12, 0.20]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%22---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x22 = [0.12,0.14,0.16,0.18,0.20];
rrk22 = [202401, 168522, 176007, 163947, 151567];
laf22 = [120202, 114809, 110418, 101042, 96168];
aam22 = [114227, 107848, 100292, 89352, 85343];
mpdc5 = distinguishable_colors(5);
plot(x22, rrk22, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, laf22, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, aam22, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x22, mcf22, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x22 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x22);
%
set(gca, 'XLim', [0.12, 0.20]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%23---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x23 = [0.12,0.14,0.16,0.18,0.20];
rrk23 = [27.0479, 24.6873, 23.3684, 21.9398, 20.4451];
laf23 = [21.7010, 20.2787, 19.0702, 17.8684, 16.8973];
aam23 = [40.9283, 35.6704, 34.6860, 31.2722, 30.6794];
mpdc5 = distinguishable_colors(5);
plot(x23, rrk23, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, laf23, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, aam23, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x23, mcf23, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x23 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x23);
set(gca, 'XLim', [0.12, 0.20]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%24---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x24 = [0.12,0.14,0.16,0.18,0.20];
rrk24 = [29.5586, 29.5586, 29.5586, 29.5586, 29.5586];
laf24 = [29.5586, 29.5586, 29.5586, 29.5586, 29.5586];
aam24 = [29.5625, 29.5625, 29.5625, 29.5625, 29.5625];
mpdc5 = distinguishable_colors(5);
plot(x24, rrk24,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, laf24, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, aam24, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
% plot(x24, mcf24, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x24 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x24);
set(gca, 'XLim', [0.12, 0.20]);
xlabel('\epsilon', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
return ;
%25---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x25 = [0.25,0.375,0.5,0.625,0.75];
rrk25= [2961,3738,4241,4581,5004];
laf25= [11314,12120,12560,12603,12852];
aam25= [6252,6633,6640,6551,6606];
aamg25= [3172,4076,4622,5026,5484];
mcf25= [9141,9610,9591,9495,9420];
mpdc5 = distinguishable_colors(5);
plot(x25, rrk25, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, aam25, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x25, aamg25, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, mcf25, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, laf25, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x25 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x25);
%

xlabel('cov', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%26---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x26 = [0.25,0.375,0.5,0.625,0.75];
rrk26= [4.850000,4.764000,4.864000,4.666000,4.744000];
laf26= [8.947000,9.619000,10.989000,11.360000,12.288000];
aam26= [0.025000,0.033000,0.024000,0.024000,0.027000];
aamg26= [0.3111,0.3185,0.3267,0.3086,0.3737];
mcf26= [0.035000,0.042000,0.041000,0.040000,0.034000];
mpdc5 = distinguishable_colors(5);
plot(x26, rrk26, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, aam26, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x26, aamg26, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, mcf26, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, laf26, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x26 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x26);
%set(gca, 'XLim', [25, 125]);
xlabel('cov', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%27---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x27 = [0.25,0.375,0.5,0.625,0.75];
rrk27= [4.496094,4.644531,4.523438,4.511719,4.515625];
laf27= [138.816406,152.191406,160.617188,162.886719,170.078125];
aam27= [6.589844,6.597656,6.601563,6.601563,6.593750];
aamg27= [17,17,18,18,18];
mcf27= [28.988281,28.968750,29.042969,29.078125,29.105469];
mpdc5 = distinguishable_colors(5);
plot(x27, rrk27,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, aam27, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x27, aamg27, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, mcf27, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, laf27, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x27 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x27);
%set(gca, 'XLim', [25, 125]);
xlabel('cov', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%28---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x28 = [0.28,0.375,0.5,0.628,0.75];
rrk28= [3919,3976,3952,4091,4060];
laf28= [12676,12931,12858,13291,13113];
aam28= [7981,8359,8362,8731,8836];
aamg28= [3825,3799,3784,3800,3704];
mcf28= [11198,11632,11627,11947,11993];
mpdc5 = distinguishable_colors(5);
plot(x28, rrk28, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, aam28, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x28, aamg28, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, mcf28, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, laf28, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x28 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x28);
%

xlabel('\alpha', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%29---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x29 = [0.25,0.375,0.5,0.625,0.75];
rrk29= [3.980000,4.214000,4.405000,4.587000,4.536000];
laf29= [16.137000,16.816000,15.360000,15.157000,14.903000];
aam29= [0.031000,0.027000,0.024000,0.024000,0.023000];
aamg29= [0.7207,0.6844,0.8080,0.7982,0.8472];
mcf29= [0.040000,0.037000,0.030000,0.041000,0.041000];
mpdc5 = distinguishable_colors(5);
plot(x29, rrk29, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, aam29, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x29, aamg29, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, mcf29, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, laf29, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x29 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x29);
%set(gca, 'XLim', [25, 125]);
xlabel('\alpha', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%30---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x30 = [0.25,0.375,0.5,0.625,0.75];
rrk30= [4.628906,4.632813,4.730469,4.523438,4.738281];
laf30= [532.046875,564.750000,604.835938,672.402344,714.218750];
aam30= [6.593750,6.570313,6.589844,6.585938,6.593750];
aamg30= [25,25,34,36,36];
mcf30= [29.074219,29.121094,29.109375,29.097656,29.085938];
mpdc5 = distinguishable_colors(5);
plot(x30, rrk30,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, aam30, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x30, aamg30, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, mcf30, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, laf30, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x30 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x30);
%set(gca, 'XLim', [25, 125]);
xlabel('\alpha', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%31---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x31 = [20*10^4,40*10^4,60*10^4,80*10^4,100*10^4];
rrk31= [44096, 88527, 133020, 177495, 222645];
laf31= [129336,258567,387918,519798,651212];
aam31= [101944,217467,336010,457770,581408];
aamg31= [50871, 102222, 153311, 205004, 257198];
mcf31= [119503,246499,373992,504096,635285];
mpdc5 = distinguishable_colors(5);
plot(x31, rrk31, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x31, aam31, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x31, aamg31, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x31, mcf31, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x31, laf31, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x31 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x31);
%

xlabel('|W|(|R|)', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%32---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x32 = x31;
rrk32= [629.7497, 2529.1897, 6643.1653, 11192.4522, 15995.3228];
aam32= [0.291000,0.597000,0.889000,1.119000,1.425000];
aamg32= [22.8989, 130.8578, 298.4217, 549.5707, 878.8211];
laf32=[22.0630,29.6937,34.5961,41.0764,42.5560];
mcf32= [0.351000,0.475000,0.582,0.991000,0.885000];
mpdc5 = distinguishable_colors(5);
plot(x32, rrk32, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x32, aam32, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x32, aamg32, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x32, mcf32, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x32, laf32, '*-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x32 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x32);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|(|R|)', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%33---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x33 = x31;
rrk33= [25, 34, 52, 52, 52];
aam33= [17.296875,21.531250,26.109375,30.683594,35.246094];
aamg33= [89, 305, 594, 1170, 2322];
mcf33= [46.941406,59.351563,71.804688,84.617188,96.691406];
laf33=[311,599,599,599,599];
mpdc5 = distinguishable_colors(5);
plot(x33, rrk33,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x33, aam33, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x33, aamg33, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x33, mcf33, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x33, laf33, '*-', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x33 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x33);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|(|R|)', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Random', 'MCF-LTC',  'LAF', 'AAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

