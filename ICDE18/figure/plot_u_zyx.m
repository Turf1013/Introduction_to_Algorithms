



fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%1---------------------------------------------------------
figure;
hold on;

%figuresize(5, 4, 'inches');

box on;
x1 = [500,1000,2500,5000,10000];
rrk1 = [3416.38, 4414.20, 7106.12, 12131.88, 22091.32];
laf1 = [3351.00, 4233.02, 6811.70, 11419.12, 20606.94];
aam1 = [3398.14, 4240.74, 6604.18, 10843.36, 19420.52];
mcf1 = [3068.00, 3662.00, 0.00, 0.00, 0.00];
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

xlabel('|W|', 'FontSize', 14);
ylabel('Max Index of Worker', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%2---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x2 = [500,1000,2500,5000,10000];
rrk2 = [0.08, 0.23, 1.24, 4.33, 15.31];
laf2 = [0.09, 0.24, 1.27, 4.47, 15.95];
aam2 = [0.09, 0.26, 1.46, 5.17, 19.49];
mcf2 = [117.15, 1586.68, 0.00, 0.00, 0.00];
mpdc5 = distinguishable_colors(5);
plot(x2, rrk2, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, aam2, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, mcf2, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, laf2, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x2 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x2);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%3---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x3 = [500,1000,2500,5000,10000];
rrk3 = [18.95, 18.95, 18.95, 19.11, 19.26];
laf3 = [18.95, 18.95, 18.95, 19.11, 19.26];
aam3 = [18.95, 18.95, 18.95, 19.11, 19.26];
mcf3 = [38.09, 95.34, 0.00, 0.00, 0.00];
mpdc5 = distinguishable_colors(5);
plot(x3, rrk3, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, aam3, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, mcf3, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x3, laf3, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x3 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x3);
%set(gca, 'XLim', [25, 125]);
xlabel('|W|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
return ;

%4---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x4 = [5000,10000,20000,30000,40000];
rrk4= [1808,2956,4241,5220,5918];
laf4= [4412,8057,12560,15084,16260];
aam4= [2030,3902,6640,8215,9152];
aamg4= [1901,3224,4622,5757,6581];
mcf4= [3027,5771,9591,11858,13127];
mpdc5 = distinguishable_colors(5);
plot(x4, rrk4, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, aam4, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x4, aamg4, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, mcf4, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x4, laf4, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x4 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x4);
%

xlabel('|R|', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%5---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x5 = [5000,10000,20000,30000,40000];
rrk5= [1.081000,2.133000,4.864000,7.468000,9.888000];
laf5= [3.370000,8.039000,10.989000,13.971000,17.111000];
aam5= [0.015000,0.018000,0.024000,0.031000,0.037000];
aamg5= [0.0775,0.1673,0.3199,0.4597,0.5880];
mcf5= [0.012000,0.020000,0.041000,0.053000,0.056000];
mpdc5 = distinguishable_colors(5);
plot(x5, rrk5, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, aam5, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x5, aamg5, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, mcf5, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x5, laf5, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x5 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x5);
%set(gca, 'XLim', [25, 125]);
xlabel('|R|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%6---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x6 = [5000,10000,20000,30000,40000];
rrk6= [4.332031,4.503906,4.523438,4.753906,4.882813];
laf6= [43.390625,85.285156,160.617188,233.699219,304.035156];
aam6= [6.417969,6.480469,6.601563,6.703125,6.820313];
aamg6= [17,17,18,18,19];
mcf6= [28.472656,28.640625,29.042969,29.242188,29.585938];
mpdc5 = distinguishable_colors(5);
plot(x6, rrk6, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, aam6, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x6, aamg6, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, mcf6, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x6, laf6, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x6 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x6);
%set(gca, 'XLim', [25, 125]);
xlabel('|R|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM', 'Location','SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [1.0,1.5,2.0,2.5,3.0];
rrk7= [2348,3296,4241,5595,7134];
laf7= [8142,10579,12560,15128,17195];
aam7= [4143,5539,6640,8017,9169];
aamg7= [2331,3487,4622,6306,8097];
mcf7= [6029,8026,9591,11431,13025];
mpdc5 = distinguishable_colors(5);
plot(x7, rrk7, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, aam7, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x7, aamg7, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, mcf7, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, laf7, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%

xlabel('Dr', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR','POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = [1.0,1.5,2.0,2.5,3.0];
rrk8= [4.813000,4.686000,4.864000,4.705000,4.812000];
laf8= [8.978000,10.013000,10.989000,12.316000,11.831000];
aam8= [0.031000,0.024000,0.024000,0.025000,0.024000];
aamg8= [0.3359,0.3393,0.3431,0.3835,0.4563];
mcf8= [0.019000,0.029000,0.041000,0.044000,0.078000];
mpdc5 = distinguishable_colors(5);
plot(x8, rrk8, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, aam8, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x8, aamg8, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, mcf8, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, laf8, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = [1.0,1.5,2.0,2.5,3.0];
rrk9= [4.644531,4.640625,4.523438,4.625000,4.519531];
laf9= [66.554688,107.191406,160.617188,229.566406,327.441406];
aam9= [6.589844,6.593750,6.601563,6.589844,6.585938];
aamg9= [17,17,18,19,19];
mcf9= [28.812500,28.937500,29.042969,29.253906,29.347656];
mpdc5 = distinguishable_colors(5);
plot(x9, rrk9, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, aam9, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x9, aamg9, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, mcf9, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, laf9, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [20,30,50,100,200];
rrk10= [7723,6211,4241,2348,405];
laf10= [14110,13334,12560,12767,8149];
aam10= [8775,7692,6640,6071,3586];
aamg10= [8161,6673,4622,2572,380];
mcf10= [12769,11084,9591,8332,4704];
mpdc5 = distinguishable_colors(5);
plot(x10, rrk10, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, aam10, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x10, aamg10, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, mcf10, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, laf10, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('Grid', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = [20,30,50,100,200];
rrk11= [4.956000,4.860000,4.864000,4.944000,4.862000];
laf11= [11.047000,9.657000,10.989000,10.752000,8.785000];
aam11= [0.024000,0.028000,0.024000,0.026000,0.023000];
aamg11= [0.3816,0.2813,0.2956,0.2959,0.2431];
mcf11= [0.038000,0.040000,0.041000,0.036000,0.044000];
mpdc5 = distinguishable_colors(5);
plot(x11, rrk11, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, aam11, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x11, aamg11, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, mcf11, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, laf11, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
%set(gca, 'XLim', [25, 125]);
xlabel('Grid', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = [20,30,50,100,200];
rrk12= [4.492188,4.644531,4.523438,4.496094,4.726563];
laf12= [195.074219,170.277344,160.617188,149.824219,65.492188];
aam12= [5.046875,5.406250,6.601563,12.070313,34.054688];
aamg12= [18,18,18,17,17];
mcf12= [9.980469,14.750000,29.042969,33.582031,40.386719];
mpdc5 = distinguishable_colors(5);
plot(x12, rrk12,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, aam12, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x12, aamg12, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, mcf12, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, laf12, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x12 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x12);
%set(gca, 'XLim', [25, 125]);
xlabel('Grid', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%13---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x13 = [12,24,48,96,144];
rrk13= [4273,4420,4241,4238,4029];
laf13= [11987,12655,12560,12364,11886];
aam13= [7846,7421,6640,5965,5512];
aamg13= [4904,4980,4622,4470,4149];
mcf13= [11191,10951,9591,8256,7375];
mpdc5 = distinguishable_colors(5);
plot(x13, rrk13, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, aam13, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x13, aamg13, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, mcf13, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x13, laf13, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x13 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x13);
%

xlabel('Time Slot', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%14---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x14 =  [12,24,48,96,144];
rrk14= [5.085000,5.072000,4.864000,4.725000,4.654000];
laf14= [13.552000,11.251000,10.989000,9.492000,8.745000];
aam14= [0.025000,0.025000,0.024000,0.040000,0.024000];
aamg14= [1.1450,0.6130,0.2615,0.1618,0.1193];
mcf14= [0.029000,0.049000,0.041000,0.037000,0.031000];
mpdc5 = distinguishable_colors(5);
plot(x14, rrk14, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, aam14, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x14, aamg14, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, mcf14, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x14, laf14, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x14 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x14);
%set(gca, 'XLim', [25, 125]);
xlabel('Time Slot', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR','POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%15---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x15 =  [12,24,48,96,144];
rrk15= [4.742188,4.484375,4.523438,4.515625,4.507813];
laf15= [524.535156,301.890625,160.617188,86.195313,59.578125];
aam15= [5.210938,5.675781,6.601563,8.425781,10.261719];
aamg15= [25,21,18,17,17];
mcf15= [12.171875,17.304688,29.042969,53.890625,77.957031];
mpdc5 = distinguishable_colors(5);
plot(x15, rrk15,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, aam15, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x15, aamg15, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, mcf15, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x15, laf15, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x15 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x15);
%set(gca, 'XLim', [25, 125]);
xlabel('Time Slot', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%16---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x16 = [0.25,0.375,0.5,0.625,0.75];
rrk16= [4289,4226,4241,4264,4127];
laf16= [12413,12370,12560,12251,12007];
aam16= [6515,6579,6640,6530,6239];
aamg16= [4699,4666,4622,4674,4493];
mcf16= [9462,9522,9591,9360,9086];
mpdc5 = distinguishable_colors(5);
plot(x16, rrk16, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, aam16, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x16, aamg16, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, mcf16, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x16, laf16, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x16 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x16);
%

xlabel('\mu', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%17---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x17 = [0.25,0.375,0.5,0.625,0.75];
rrk17= [5.264000,5.097000,4.864000,4.503000,4.398000];
laf17= [10.266000,10.303000,10.989000,10.215000,10.771000];
aam17= [0.025000,0.024000,0.024000,0.025000,0.024000];
aamg17= [0.3644,0.2535,0.2902,0.2310,0.2884];
mcf17= [0.045000,0.042000,0.041000,0.039000,0.040000];
mpdc5 = distinguishable_colors(5);
plot(x17, rrk17, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, aam17, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x17, aamg17, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, mcf17, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x17, laf17, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x17 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x17);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%18---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x18 = [0.25,0.375,0.5,0.625,0.75];
rrk18= [4.640625,4.636719,4.523438,4.640625,4.640625];
laf18= [163.128906,160.582031,160.617188,156.457031,150.785156];
aam18= [6.593750,6.582031,6.601563,6.601563,6.597656];
aamg18= [19,18,18,17,17];
mcf18= [29.054688,29.011719,29.042969,28.996094,29.062500];
mpdc5 = distinguishable_colors(5);
plot(x18, rrk18,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, aam18, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x18, aamg18, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, mcf18, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x18, laf18, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x18 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x18);
%set(gca, 'XLim', [25, 125]);
xlabel('\mu', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%19---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x19 = [0.25,0.375,0.5,0.625,0.75];
rrk19= [4058,4112,4241,4315,4341];
laf19= [12290,12284,12560,12442,12479];
aam19= [6610,6512,6640,6516,6497];
aamg19= [4472,4513,4622,4726,4799];
mcf19= [9416,9360,9591,9418,9420];
mpdc5 = distinguishable_colors(5);
plot(x19, rrk19, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, aam19, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x19, aamg19, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, mcf19, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x19, laf19, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x19 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x19);
%

xlabel('\sigma', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%20---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x20 = [0.25,0.375,0.5,0.625,0.75];
rrk20= [4.488000,4.728000,4.864000,4.883000,4.846000];
laf20= [9.991000,10.695000,10.989000,10.195000,10.005000];
aam20= [0.024000,0.025000,0.024000,0.032000,0.024000];
aamg20= [0.3157,0.3432,0.3607,0.3194,0.3477];
mcf20= [0.049000,0.051000,0.041000,0.054000,0.045000];
mpdc5 = distinguishable_colors(5);
plot(x20, rrk20, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, aam20, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x20, aamg20, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, mcf20, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x20, laf20, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x20 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x20);
%set(gca, 'XLim', [25, 125]);
xlabel('\sigma', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%21---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x21 = [0.25,0.375,0.5,0.625,0.75];
rrk21= [4.722656,4.636719,4.523438,4.503906,4.507813];
laf21= [162.394531,156.738281,160.617188,158.968750,158.949219];
aam21= [6.585938,6.589844,6.601563,6.589844,6.585938];
aamg21= [17,17,18,18,18];
mcf21= [28.996094,29.046875,29.042969,29.050781,29.031250];
mpdc5 = distinguishable_colors(5);
plot(x21, rrk21,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, aam21, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x21, aamg21, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, mcf21, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x21, laf21, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x21 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x21);
%set(gca, 'XLim', [25, 125]);
xlabel('\sigma', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR','POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%22---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x22 = [0.25,0.375,0.5,0.625,0.75];
rrk22= [13809,12870,4241,688,41];
laf22= [18653,18556,12560,3461,445];
aam22= [9750,9746,6640,1700,215];
aamg22= [17602,14697,4622,656,30];
mcf22= [16837,13912,9591,2392,274];
mpdc5 = distinguishable_colors(5);
plot(x22, rrk22, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, aam22, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x22, aamg22, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, mcf22, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, laf22, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x22 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x22);
%

xlabel('mean', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%23---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x23 = [0.25,0.375,0.5,0.625,0.75];
rrk23= [1.323000,3.615000,4.864000,4.829000,4.712000];
laf23= [18.656000,12.532000,10.989000,7.775000,7.225000];
aam23= [0.023000,0.024000,0.024000,0.028000,0.024000];
aamg23= [0.5164,0.8199,0.2723,0.2533,0.3032];
mcf23= [0.064000,0.073000,0.041000,0.010000,0.006000];
mpdc5 = distinguishable_colors(5);
plot(x23, rrk23, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, aam23, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x23, aamg23, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, mcf23, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, laf23, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x23 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x23);
%set(gca, 'XLim', [25, 125]);
xlabel('mean', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%24---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x24 = [0.25,0.375,0.5,0.625,0.75];
rrk24= [4.628906,4.515625,4.523438,4.496094,4.734375];
laf24= [890.558594,566.992188,160.617188,22.921875,8.152344];
aam24= [6.593750,6.589844,6.601563,6.605469,6.589844];
aamg24= [25,21,18,17,17];
mcf24= [29.304688,29.277344,29.042969,28.664063,28.636719];
mpdc5 = distinguishable_colors(5);
plot(x24, rrk24,'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, aam24, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x24, aamg24, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, mcf24, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, laf24, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x24 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x24);
%set(gca, 'XLim', [25, 125]);
xlabel('mean', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
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
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
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
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
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
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'laf','Location', 'SouthEast');
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
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
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
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
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
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
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
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
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
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
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
h_legend = legend('RandomK', 'MCF',  'LAF', 'LAM','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

