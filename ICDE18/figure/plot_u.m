clear;
fontsize = 10;
markersize = 10;
legendsize = 12;
linewidth = 1.5;

%% 3a---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x = [2,4,6,8,10,12,14,16,18,20,22,24,26,28,30];
xr005_1 = [2,4,6,8,10,12,14];xr005_2 = [14,16,18,20,22,24,26,28,30];
xr008_1=[2,4,6,8,10,12,14,16,18,20,22,24];xr008_2=[24,26,28,30];
xr010_1=[2,4,6,8,10,12,14,16,18,20,22,24,26,28,30];


r0_05_1=[0.970,0.930,0.920,0.940,0.890,0.910,0.770];r0_05_2=[0.770,0.845,0.870,0.805,0.815,0.730,          0.750,0.700,0.685];
r0_08_1=[0.930,0.955,0.970,0.870,0.900,0.890,0.885,          0.890,0.885,0.795,0.820,0.800];r0_08_2=[0.800,0.818,0.740,0.760];
r0_1=[   0.955,0.955,0.975,0.920,0.925,0.920,0.860,          0.900,0.900,0.830,0.905,0.895,          0.860,0.870,0.770];

mpdc3 = distinguishable_colors(3);
plot(xr005_1, r0_05_1, 'o-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

plot(xr008_1, r0_08_1, 's-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);


plot(x, r0_1, '^-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xr005_2, r0_05_2, 'o--', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xr008_2, r0_08_2, 's--', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%line([0,14],[0.770,0.770],'linestyle',':');
line([14,14],[0.65,0.770],'linestyle','--','LineWidth', linewidth,'Color', 'black');
line([24,24],[0.65,0.800],'linestyle','--','LineWidth', linewidth,'Color', 'black');
%plot(14,0.770,'o');
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Cardinality', 'FontSize', 14);
ylabel('Confidence', 'FontSize', 14);
h_legend = legend('cost=0.05','cost=0.08','cost=0.1', 'Location','SouthWest');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5a---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x = [2,4,6,8,10,12,14,16,18,20,22,24,26,28,30];
x1 = [2,4,6,8,10,12,14,16,18,20,22];
x2 = [22,24,26,28,30];
r0_05_1=[0.76,0.847,0.74,0.745,0.735,0.68,0.72,0.755,0.725,0.67,0.61];
r0_05_2=[0.61,0.55,0.545,0.51,0.525];
r0_05=[0.76,0.847,0.74,0.745,0.735,0.68,0.72,0.755,0.725,0.67,0.61,0.55,0.545,0.51,0.525];
r0_08=[0.83,0.82,0.775,0.785,0.76,0.765,0.74,0.71,0.745,0.68,0.65,0.66,0.62,0.55,0.57];
r0_1=[0.825,0.86,0.83,0.75,0.775,0.855,0.742,0.71,0.76,0.675,0.685,0.69,0.665,0.682,0.642];

mpdc3 = distinguishable_colors(3);
plot(x1, r0_05_1, 'o-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, r0_08, 's-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, r0_1, '^-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x2, r0_05_2, 'o--', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
line([22,22],[0.5,0.61],'linestyle','--','LineWidth', linewidth,'Color', 'black');
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Cardinality', 'FontSize', 14);
ylabel('Confidence', 'FontSize', 14);
h_legend = legend('cost=0.05','cost=0.1','cost=0.2', 'Location','SouthWest');
set(h_legend, 'FontSize', legendsize);

hold off;
%% 5b---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.87,0.9,0.92,0.95,0.97];
Greedy=[650,610,500,510,520];
OPQ=[590,550,420,430,460];
Baseline=[1150,990,950,1010,990];
Greedy=Greedy(end:-1:1);
OPQ=OPQ(end:-1:1);
Baseline=Baseline(end:-1:1);

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set(gca,'XDir','reverse')%对X方向反转
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Reliability Threshold t', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5c---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[0.87,0.9,0.92,0.95,0.97];
Greedy=[650,560,500,420,390];
OPQ=[600,550,440,410,390];
Baseline=[1290,990,940,1100,810];
Greedy=Greedy(end:-1:1);
OPQ=OPQ(end:-1:1);
Baseline=Baseline(end:-1:1);

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set(gca,'XDir','reverse')%对X方向反转
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Reliability Threshold t', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5d---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[0.87,0.9,0.92,0.95,0.97];
Greedy=[1.5,1.6,2.2,2.0,1.05];
OPQ=[0.4,0.5,0.5,0.5,0.3];
Baseline=[2.9,3.2,3.8,4.0,2.25];
Greedy=Greedy(end:-1:1);
OPQ=OPQ(end:-1:1);
Baseline=Baseline(end:-1:1);

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set(gca,'XDir','reverse')%对X方向反转
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Reliability Threshold t', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5e---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[0.87,0.9,0.92,0.95,0.97];
Greedy=[1.4,1.35,1.1,0.9,0.7];
OPQ=[0.4,0.4,0.35,0.4,0.2];
Baseline=[1.4,1.4,1.3,1.2,1];
Greedy=Greedy(end:-1:1);
OPQ=OPQ(end:-1:1);
Baseline=Baseline(end:-1:1);

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set(gca,'XDir','reverse')%对X方向反转
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Reliability Threshold t', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5f---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20];
Greedy=[3100,1500,1500,1500,1450,1000,1000,950,800,750,750,700,650,600,600,590,580,580,580,580];
OPQ=[2600,1300,1300,1300,1250,800,750,740,650,600,580,550,550,540,530,530,520,520,500,500];
Baseline=[5250,2600,2400,2500,2350,2450,2150,2100,2000,1800,1800,1700,1500,1400,1350,1200,1100,1000,1300,1250];

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5g---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20];
Greedy=[2500,1250,1250,1250,1200,800,800,750,700,650,600,590,580,580,500,480,470,460,450,440];
OPQ=[2500,1250,1250,1250,1200,800,800,750,700,650,600,590,580,580,500,480,470,460,450,440];
Baseline=[5000,2600,2600,2600,2300,2400,2000,1500,2000,1700,1400,1100,1300,1200,1100,1000,900,850,800,800,];

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5h---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20];
Greedy=[16,8.5,7.9,6.3,6.4,6.35,4,4,3.7,3.7,3.4,3.7,3.7,3.7,3.6,3.8,3.9,4,3.8,4];
OPQ=[1.6,1.5,1.5,1.4,1.3,1.35,1.2,1.2,1.1,1.2,1.2,1.1,1.35,1.1,1.1,1.2,1.2,1.2,1.2,1.2];
Baseline=[13,6,4.5,3.9,3.7,3.6,3.6,3,3.4,2.9,3.1,3.2,2.5,2.4,2.6,2.3,2.3,2.1,2.2,2.3];

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5i---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20];
Greedy=[14,6.9,6.8,6.5,3.5,2.9,2.2,2,1.9,1.8,1.7,1.7,1.6,1.6,1.7,1.7,1.6,1.6,1.5,1.5];
OPQ=[1.6,1.5,1.5,1.4,1.3,1.35,1.2,1.2,1.1,1.2,1.2,1.1,1.35,1.1,1.1,1.2,1.2,1.2,1.2,1.2];
Baseline=[10,4.1,4,3.9,1.9,1.8,1.8,1.8,1.8,1.75,1.65,1.65,1.55,1.55,1.65,1.65,1.55,1.55,1.45,1.45];

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Max. Cardinality', 'FontSize', 14);
ylabel('Time (seconds))', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5j---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.87,0.9,0.92,0.95,0.97];
Greedy=[600,550,510,490,400];
OPQ=[500,450,400,390,310];
Baseline=[1140,1040,980,970,900];
Greedy=Greedy(end:-1:1);
OPQ=OPQ(end:-1:1);
Baseline=Baseline(end:-1:1);

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set(gca,'XDir','reverse')%对X方向反转
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('\mu of Reliability Threshold t_i', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ-Extended','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5k---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.01,0.02,0.03,0.04,0.05];
Greedy=[400,350,450,400,440];
OPQ=[320,300,380,310,340];
Baseline=[1000,910,930,900,910];


mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('\sigma of Reliability Threshold t_i', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ-Extended','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 5l---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.87,0.9,0.92,0.95,0.97];
Greedy=[3.5,3.25,2.5,2.25,1];
OPQ=[0.5,0.5,0.45,0.5,0.2];
Baseline=[6,5.8,5.5,4.25,2.2];
Greedy=Greedy(end:-1:1);
OPQ=OPQ(end:-1:1);
Baseline=Baseline(end:-1:1);

mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
set(gca,'XDir','reverse')%对X方向反转
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('\mu of Reliability Threshold t_i', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ-Extended','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6a---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.01,0.02,0.03,0.04,0.05];
Greedy=[2.5,2.6,2.4,3.9,4];
OPQ=[0.2,0.3,0.4,0.5,1.9];
Baseline=[5,5.7,4.6,4.7,5.1];


mpdc3 = distinguishable_colors(3);
plot(x, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('\sigma of Reliability Threshold t_i', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ-Extended','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6b---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.1, 0.3, 0.5, 1, 1.5, 2, 3, 5, 7.5, 10];
xx=[0,0.11111,0.22222,0.33333,0.44444,0.55555,0.66666,0.77777,0.88888,0.99999];
Greedy=[50,80,105,220,510,1050,1300,2300,4000,5000];
OPQ=[40,70,100,210,500,1000,1100,2000,3000,4000];
Baseline=[60,200,500,1000,1900,2000,3000,3900,6800,8000];


mpdc3 = distinguishable_colors(3);
plot(xx, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
%set(gca,'xticklabel',[0,986,987,988,1023]);
set( gca(), 'xtick',xx,'XTickLabel', x);
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize);
%

%x,y轴的名字
xlabel('# of atomic tasks (×10^4)', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6c---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.1,0.3,0.5,1,1.5,2,3,5,7.5,10];
Greedy=[50,80,105,220,510,1050,1150,2100,3100,4200];
OPQ=[40,70,100,210,500,1000,1100,2000,3000,4000];
Baseline=[60,200,500,1000,1900,2000,3000,3900,6800,8000];


mpdc3 = distinguishable_colors(3);
plot(xx, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'xtick',xx,'XTickLabel', x);
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize);
%

%x,y轴的名字
xlabel('# of atomic tasks (×10^4)', 'FontSize', 14);
ylabel('Cost (USD)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6d---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.1,0.3,0.5,1,1.5,2,3,5,7.5,10];
Greedy=[0.5,1,1,2,8,15,32,52,82,130];
OPQ=[0.5,0.5,0.5,0.5,0.5,0.5,0.5,1,1,2];
Baseline=[0.5,0.5,0.5,1,3,5,10,25,55,105];


mpdc3 = distinguishable_colors(3);
plot(xx, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'xtick',xx,'XTickLabel', x);
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize);
%

%x,y轴的名字
xlabel('# of atomic tasks (×10^4)', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6e---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.1,0.3,0.5,1,1.5,2,3,5,7.5,10];
Greedy=[0.5,0.5,0.5,2,3,6,15,35,65,105];
OPQ=[0.5,0.5,0.5,0.5,0.5,0.5,0.5,1,1,2];
Baseline=[0.5,0.5,0.5,1,2,5,8,22,48,80];


mpdc3 = distinguishable_colors(3);
plot(xx, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'xtick',xx,'XTickLabel', x);
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize);
%

%x,y轴的名字
xlabel('# of atomic tasks (×10^4)', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6f---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.1,0.3,0.5,1,1.5,2,3,5,7.5,10];
Greedy=[0.5,0.5,0.5,2,2,5,11,30,45,80];
OPQ=[0.5,0.5,0.5,0.5,0.5,2,4,19,26,31];
Baseline=[0.5,0.5,1,5,6,8,15,39,65,125];


mpdc3 = distinguishable_colors(3);
plot(xx, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'xtick',xx,'XTickLabel', x);
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize);
%

%x,y轴的名字
xlabel('# of atomic tasks (×10^4)', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ-Extended','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6g---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
%x = [0.97,0.95,0.92,0.9,0.87];
x=[0.1,0.3,0.5,1,1.5,2,3,5,7.5,10];
Greedy=[0.5,0.5,0.5,3,8,10,15,25,56,90];
OPQ=[0.5,0.5,0.5,1,2,5,10,21,30,42];
Baseline=[0.5,3,5,8,10,15,30,55,85,150];


mpdc3 = distinguishable_colors(3);
plot(xx, Greedy, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, OPQ, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(xx, Baseline, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

%旋转
set( gca(), 'xtick',xx,'XTickLabel', x);
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize);
%

%x,y轴的名字
xlabel('# of atomic tasks (×10^4)', 'FontSize', 14);
ylabel('Time (seconds)', 'FontSize', 14);
h_legend = legend('Greedy','OPQ-Extended','Baseline');
set(h_legend, 'FontSize', legendsize);

hold off;

%% 6h---------------------------------------------------------
figure;
hold on;

figuresize(5, 4, 'inches');

box on;
x=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20];
Diff2=[0.92,0.91,0.87,0.88,0.89,0.84,0.83,0.835,0.8,0.79,0.785,0.78,0.79,0.8,0.795,0.79,0.78,0.74,0.73,0.72];
Diff1=[0.99,0.98,0.97,0.96,0.97,0.98,0.965,0.94,0.935,0.93,0.92,0.91,0.89,0.86,0.88,0.91,0.91,0.91,0.87,0.83];
Diff3=[0.85,0.84,0.83,0.845,0.825,0.82,0.815,0.81,0.78,0.77,0.765,0.765,0.77,0.765,0.74,0.75,0.74,0.7,0.69,0.69];

mpdc3 = distinguishable_colors(3);
plot(x, Diff1, 's-', 'Color', mpdc3(2, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
plot(x, Diff2, '^-', 'Color', mpdc3(1, :), 'LineWidth', linewidth, 'MarkerSize', markersize);

plot(x, Diff3, 'p-', 'Color', mpdc3(3, :), 'LineWidth', linewidth, 'MarkerSize', markersize);
%旋转
set( gca(), 'XTickLabel', x )
rotateXLabels( gca(), 60 )
set(gca, 'FontSize', fontsize, 'Xtick', x);
%

%x,y轴的名字
xlabel('Cardinality', 'FontSize', 14);
ylabel('Confidece', 'FontSize', 14);
h_legend = legend('Diff. 1','Diff. 2','Diff. 3');
set(h_legend, 'FontSize', legendsize);

hold off;