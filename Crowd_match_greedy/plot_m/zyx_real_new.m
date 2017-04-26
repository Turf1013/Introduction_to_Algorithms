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
				

opt25 = [1566.869034, 1988.460853, 2070.333677, 2070.333677, 2070.333677];
simg25 = [1450.841427, 1889.682764, 2031.652938, 2031.652938, 2031.652938];
extended25 = [976.151711, 1230.726538, 1288.062089, 1288.062089, 1288.062089];
fgoa25 = [1445.787472, 1804.756782, 1918.483096, 1918.483096, 1918.533494];
fgoag25 = [1433.254461, 1651.911995, 1727.433597, 1726.387275, 1730.200870];
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
				
				
				

simg26 = [0.036761, 0.061281, 0.160149, 0.210436, 0.433263];
extended26 = [0.032492, 0.034727, 0.086885, 0.157863, 0.296134];
fgoa26 = [1.144141, 7.518603, 118.290316, 301.896022, 476.091881];
fgoag26 = [0.040466, 0.056093, 0.098808, 0.150996, 0.261936];
%%opt26 = [30.878685, 32.18615, 22.368069, 169.240193, 986.908792];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
				
			
			

%%opt27 = [17.69140625, 17.71484375, 17.8046875, 18.22265625, 19.1875];
simg27 = [17.08984375, 17.08984375, 17.23828125, 17.53125, 18.40625];
extended27 = [17.09375, 17.09375, 17.2421875, 17.640625, 18.41015625];
fgoa27 = [17.10546875, 17.109375, 17.2890625, 17.58984375, 18.42578125];
fgoag27 = [17.09765625, 17.1015625, 17.28125, 17.58203125, 18.41796875];
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
		
opt28 = [1878.431600, 2218.394300, 2273.744800];
simg28 = [1789.712200, 2153.104700, 2225.154400];
extended28 = [1257.328525, 1499.940375, 1547.951800];
fgoa28 = [1788.349200, 2046.228300, 2112.002200];
fgoag28 = [1776.439400, 1963.460900, 2022.518200];
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
				
				

simg29 = [0.007754, 0.011617, 0.021571];
extended29 = [0.009051, 0.009959, 0.018158];
fgoa29 = [0.15666, 0.456095, 0.562145];
fgoag29 = [0.007327, 0.01011, 0.012332];
%%opt29 = [0.425134, 1.058184, 2.923576];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
				

%%opt30 = [17.37890625, 17.55859375, 17.53515625];
simg30 = [16.796875, 16.796875, 16.87109375];
extended30 = [16.80078125, 16.80078125, 16.875];
fgoa30 = [16.8125, 16.8125, 16.88671875];
fgoag30 = [16.8046875, 16.96875, 16.87890625];
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
