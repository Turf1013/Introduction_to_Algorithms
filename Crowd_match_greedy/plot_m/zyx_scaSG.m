
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

extended22 = [1167.144800, 1223.413900, 1397.435300, 1198.458300, 1228.814200, 1280.320800];
fgoa22 = [2217.534800, 2267.396000, 2447.939600, 2461.279200, 2680.582600, 2629.962600];
fgoag22 = [4669.914600, 5398.172700, 5953.347900, 5759.753800, 6224.866700, 6438.335600];

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

extended23 = [0.18282, 0.286087, 0.434034, 0.576006, 0.785585, 1.236594];
fgoa23 = [0.316077, 0.566512, 0.816208, 1.020574, 1.223554, 2.228855];
fgoag23 = [0.770557, 1.417196, 2.009837, 2.274495, 2.777762, 5.618526];

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
