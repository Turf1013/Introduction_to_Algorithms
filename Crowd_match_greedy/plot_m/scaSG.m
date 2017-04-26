
fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;



figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x22 = [10000, 20000, 30000, 40000, 50000, 100000];
mpdc4 = distinguishable_colors(4);

extended22=[4506.260000,4574.610000,4856.970000,4661.580000,5082.890000,4780.11];
fgoa22 =[8480.280000,8999.910000,9398.480000,9938.270000,9859.650000,10055.6];

fgoag22=[15103.900000,19855.800000,21926.100000,22109.800000,23357.400000,25190.1];

plot(x22, extended22, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize',markersize);
plot(x22, fgoa22, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x22, fgoag22, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x22);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Utility', 'FontSize', 14);
h_legend = legend('|W|=0.5K', '|W|=1K', '|W|=2.5K', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%23---------------------scalability2------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x23 = [10000, 20000, 30000, 40000, 50000, 100000];
mpdc4 = distinguishable_colors(4);

extended23 = [0.086000,0.229000,0.319000,0.415000,0.497000,1.181000];
fgoag23 =[0.256000,0.743000,1.064000,1.358000,1.842000,3.826000];
fgoa23 =[0.181000,0.330000,0.503000,0.651000,0.930000,2.023000];
plot(x23, extended23, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, fgoa23, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x23, fgoag23, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x23);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Time(secs)', 'FontSize', 14);
h_legend = legend('|W|=0.5K', '|W|=1K', '|W|=2.5K', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;

%24----------------------scalability3-----------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x24 = [10000, 20000, 30000, 40000, 50000, 100000];
mpdc4 = distinguishable_colors(4);

 fgoag24=[4.957030,5.562500,6.042970,5.925780,7.421880,12.351600];
 extended24=[3.906250,4.863280,5.753910,5.613280,7.000000,11.640600];
 fgoa24=[4.601560,5.058590,6.078130,5.906250,7.359380,12.117200];
plot(x24, extended24, 'o-', 'Color', mpdc4(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, fgoa24, 'x-', 'Color', mpdc4(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x24, fgoag24, 'd-', 'Color', mpdc4(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


set(gca, 'FontSize', fontsize, 'Xtick', x24);
%set(gca, 'XLim', [25, 125]);
xlabel('|T|', 'FontSize', 14);
ylabel('Memory(MB)', 'FontSize', 14);
h_legend = legend('|W|=0.5K', '|W|=1K', '|W|=2.5K', 'Location', 'SouthEast');
set(h_legend, 'FontSize', legendsize);

hold off;