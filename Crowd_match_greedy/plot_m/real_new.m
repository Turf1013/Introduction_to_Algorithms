fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;
%25---------------------------real-data------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x25 = [1,2,5,10,20];
				

extended25 = [976.152,	1230.73	,1288.06,1288.06,1288.06];
				

fgoag25 = [1369.75,	1755.68,1941.51,1941.51,1941.51];
simg25=[1450.84,1889.68,2031.65,2031.65,2031.65];				

fgoa25 = [1445.83,	1850.64	,1994.87	,1994.87,1994.87];
opt25 =  [1566.869034,1988.460853,2070.333677,2070.333677,2070.333677];
mpdc5 = distinguishable_colors(5);
plot(x25, extended25, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, fgoa25, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, fgoag25, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, opt25, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x25, simg25, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x25);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%26---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x26 = [1,2,5,10,20];
				
				
				
simg26=[0.028,0.038,0.066,0.081,0.183];
extended26 = [3.261666667	,3.266	,3.262	,3.272	,3.311333333
];
fgoag26 = [3.281,	4.234,	8.181	,15.598	,27.859
];
fgoa26 = [3.732,	26.091,	147.123	,454.206	,1523.665
];
%%opt16 = [4.769516, 8.082016, 17.0977, 20.4961,
%%50.1211];%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mpdc4 = distinguishable_colors(4);
plot(x26, extended26, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, fgoa26, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, fgoag26, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x26, simg26, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x26);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%27---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x27 = [1,2,5,10,20];
				
			
			

extended27 = [3.627606667	3.627606667	,3.52995,	3.528646667,3.528646667
];
fgoag27 = [3.14,2.98,	3.3		,3.36	,3.88
];
fgoa27 = [3.39453	,	3.46484,	4	,4.1875	,4.76641
];
simg27=[3.43359,3.76563,3.52734,4.04297,4.28125];
mpdc4 = distinguishable_colors(4);
plot(x27, extended27, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, fgoa27, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, fgoag27, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x27, simg27, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x27);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%28---------------------------real-data gmission------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x28 = [1,2,3];
				

extended28 = [1257.33,1499.94,1547.95];
fgoag28 = [1789.71,2052.63,2174.4];
simg28=[1789.71,2153.1,2225.15];				
fgoa28 = [1789.71,2153.1,2172.79];
opt28 =  [1978.432,2218.394,2273.745];
mpdc5 = distinguishable_colors(5);
plot(x28, extended28, 'o-', 'Color', mpdc5(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, fgoa28, 'x-', 'Color', mpdc5(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, fgoag28, 'd-', 'Color', mpdc5(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, opt28, 's--', 'Color', mpdc5(5, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x28, simg28, '*-', 'Color', mpdc5(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x28);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','OPT-Offline', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%29---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x29 = [1,2,3];
				
				
				
simg29=[0.009,0.01,0.007];
extended29 = [0.01,0.021,0.026];
fgoa29 = [0.227,1.939,3.919];
fgoag29 = [0.105,0.209,0.33];
%%opt16 = [4.769516, 8.082016, 17.0977, 20.4961,
%%50.1211];%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mpdc4 = distinguishable_colors(4);
plot(x29, extended29, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, fgoa29, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, fgoag29, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x29, simg29, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x29);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;
%30---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x30 = [1,2,3];
				
			
			

extended30 = [5.0625,5.18359,5.11328];
fgoag30 = [3.33203,3.32813,3.39453];
fgoa30 = [4.91406,4.91797,4.95313];
simg30=[3.21484,3.16406,3.29297];
mpdc4 = distinguishable_colors(4);
plot(x30, extended30, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, fgoa30, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, fgoag30, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x30, simg30, '*-', 'Color', mpdc4(4, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

set(gca, 'FontSize', fontsize, 'Xtick', x30);
%set(gca, 'XLim', [25, 125]);
xlabel('c_w', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('Extended Greedy-RT', 'TGOA', 'TGOA-Greedy', 'SimpleGreedy','Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;