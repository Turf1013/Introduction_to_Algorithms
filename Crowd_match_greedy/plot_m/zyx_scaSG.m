
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

extended22 = [4511.084500, 4577.620800, 4857.296000, 4661.583400, 5084.215600, 4780.111100];
fgoa22 = [8481.519100, 8999.909400, 9400.443900, 9935.846300, 9867.597100, 10071.706300];
fgoag22 = [15144.323100, 19880.213600, 21954.114800, 22113.846500, 23366.825300, 25190.758900];

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

extended23 = [0.177704, 0.298875, 0.433575, 0.552416, 0.671079, 1.177756];
fgoa23 = [0.352684, 0.655662, 0.833884, 0.967912, 1.182652, 2.030971];
fgoag23 = [0.838442, 1.532395, 1.738115, 2.546284, 3.010636, 5.885208];
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

extended24 = [18.40625, 19.5, 19.5, 22.125, 22.125, 27.375];
fgoa24 = [18.41015625, 19.71875, 19.71875, 22.34375, 22.34375, 27.59375];
fgoag24 = [18.84765625, 20.37890625, 20.15625, 23.65625, 22.78125, 28.03125];
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
