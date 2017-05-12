fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%7---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x7 = [0.5,0.75,1.0,1.25,1.5];
simg7= [37361,37361,47303,47303,48349];
opt7= [46682,46682,50619,50631,50634];
pre7= [37499,37499,40975,41230,41233];
preg7= [35845, 35845, 48459, 48459, 49740];
opre7= [44303,44303,49074,49287,49416];
mpdc5 = distinguishable_colors(5);
plot(x7, simg7, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, pre7, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x7, preg7, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, opre7, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x7, opt7, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%Ðý×ª
set( gca(), 'XTickLabel', x7 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x7);
%

xlabel('Dr', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%%
%8---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x8 = x7;
simg8= [24.534,25.004,13.694,12.789,11.321];
opt8= [77.43,70.556,73.339,66.438,69.703];
pre8= [0.144,0.152,0.143,0.135,0.141];
preg8= [6.9243, 7.0065, 9.0876, 9.4297, 11.1581];
opre8= [0.052,0.035,0.044,0.024,0.021];
mpdc5 = distinguishable_colors(5);
plot(x8, simg8, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, pre8, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x8, preg8, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, opre8, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x8, opt8, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x8 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x8);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%9---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x9 = x8;
simg9= [5.628906,5.628906,5.945313,5.625,5.636719];
opt9= [1077.945313,1078.429688,1627.757813,2042.429688,2234.320313];
pre9= [4.984375,4.984375,4.984375,4.988281,5];
%preg9= [37, 37, 89, 89, 161];
opre9= [9.519531,9.519531,9.707031,9.628906,9.691406];
mpdc5 = distinguishable_colors(5);
plot(x9, simg9, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, pre9, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x9, preg9, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, opre9, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x9, opt9, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x9 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x9);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%10---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x10 = [0.5,0.75,1.0,1.25,1.5];
simg10= [38465,38465,44311,44311,45267];
opt10= [45329,45329,48283,48347,48375];
pre10= [35166,35166,36974,37015,37067];
preg10= [36294, 36294, 45988, 45988, 47250];
opre10= [42895,42895,47002,47257,47373];
mpdc5 = distinguishable_colors(5);
plot(x10, simg10, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, pre10, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x10, preg10, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, opre10, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x10, opt10, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%Ðý×ª
set( gca(), 'XTickLabel', x10 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x10);
%

xlabel('Dr', 'FontSize', 14);
ylabel('Matching Size', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR',  'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%11---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x11 = x10;
simg11= [16.787,16.709,9.932,9.899,8.861];
opt11= [63.046,62.341,69.3,72.28,83.415];
pre11= [0.12,0.138,0.116,0.142,0.115];
preg11= [4.6017, 4.6036, 6.2289, 6.2289, 8.6191];
opre11= [0.134,0.138,0.104,0.069,0.1];
mpdc5 = distinguishable_colors(5);
plot(x11, simg11, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, pre11, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x11, preg11, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, opre11, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x11, opt11, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x11 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x11);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR','POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%12---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x12 = x10;
simg12= [5.949219,5.628906,5.625,5.621094,5.628906];
opt12= [1038.464844,1038.269531,1554.25,1974.234375,2119.914063];
pre12= [4.90625,4.914063,4.914063,4.917969,4.921875
];
preg12= [26, 26, 53, 53, 89];
opre12= [9.242188,9.242188,9.414063,9.347656,9.4375];
mpdc5 = distinguishable_colors(5);
plot(x12, simg12, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, pre12, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%plot(x12, preg12, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, opre12, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x12, opt12, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set( gca(), 'XTickLabel', x12 )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x12);
%set(gca, 'XLim', [25, 125]);
xlabel('Dr', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('SimpleGreedy', 'POLAR', 'POLAR-OP', 'OPT','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

